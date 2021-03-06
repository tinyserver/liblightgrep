/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
#include "container_out.h"
#include "pair_out.h"
#include <iostream>
*/

#include <algorithm>
#include <cctype>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "lightgrep/util.h"
#include "lightgrep/transforms.h"
#include "lightgrep/encodings.h"

#include "c_api_util.h"
#include "decoders/decoder.h"
#include "decoders/decoderfactory.h"
#include "decoders/utf8.h"

namespace {
  int find_trans_id(const LG_TRANS* beg, const LG_TRANS* end, const char* const name) {
    std::string ns(name);
    std::transform(ns.begin(), ns.end(), ns.begin(), ::tolower);

  // TODO: encodings are sorted by name, so do a binary search
    const LG_TRANS* ptr = std::find_if(
      beg,
      end,
      [&](const LG_TRANS& t) -> bool {
        std::string ts(t.name);
        std::transform(ts.begin(), ts.end(), ts.begin(), ::tolower);
        return ns == ts;
      }
    );

    return ptr == end ? -1 : ptr->idx;
  }
}

int lg_get_char_transform_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_CHAR_TRANSFORMS,
        LG_CHAR_TRANSFORMS +
          sizeof(LG_CHAR_TRANSFORMS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

int lg_get_encoding_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_ENCODINGS,
        LG_ENCODINGS +
          sizeof(LG_ENCODINGS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

int lg_get_byte_transform_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_BYTE_TRANSFORMS,
        LG_BYTE_TRANSFORMS +
          sizeof(LG_BYTE_TRANSFORMS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

namespace {
  unsigned int decode(
    const byte* bbeg,
    const byte* bend,
    const byte* hbeg,
    const byte* hend,
    size_t leading,
    size_t trailing,
    Decoder& dec,
    std::vector< std::pair<int32_t,const byte*> >& cps)
  {
    // precondition:
    //    bbeg <= hbeg <= hend <= bend

    unsigned int bad = 0;
    std::pair<int32_t,const byte*> cp;

    //
    // leading context
    //
    unsigned int max_adj_good = 0, max_inv_bad = 0;
    std::vector< std::pair<int32_t,const byte*> > lctx;

    // Decode leading sequences of increasing length until we hit the
    // beginning of the buffer or decode more values than we need for
    // leading context.
    for (const byte* l = hbeg-1; l >= bbeg && lctx.size() <= leading; --l) {
      dec.reset(l, hbeg);
      lctx.clear();
      bad = 0;

      // read the leading context
      while ((cp = dec.next()).first != LG_WINDOW_END) {
        lctx.push_back(cp);
        if (cp.first < 0) {
          ++bad;
        }
      }

      // find the start of the good sequence adjacent to the hit
      auto i = std::find_if(
        lctx.crbegin(), lctx.crend(),
        [](const std::pair<int32_t,const byte*>& p) {
          return p.first < 0;
        }
      );

      unsigned int adj_good = i - lctx.crbegin();
      unsigned int inv_bad = std::numeric_limits<unsigned int>::max() - bad;

      // leading sequences are lexicographically ordered by the length of
      // their hit-adjacent good sequence and their number of bad values
      if (std::tie(adj_good, inv_bad) >= std::tie(max_adj_good, max_inv_bad)) {
        // this leading context is not worse than the previous best, keep it
        max_adj_good = adj_good;
        max_inv_bad = inv_bad;
        cps.assign(
          lctx.size() > leading ? lctx.end() - leading : lctx.begin(),
          lctx.end()
        );
      }
    }

    bad = std::numeric_limits<unsigned int>::max() - max_inv_bad;

    //
    // hit
    //
    dec.reset(hbeg, bend);

    while ((cp = dec.next()).second < hend) {
      cps.push_back(cp);
      if (cp.first < 0) {
        ++bad;
      }
    }

    //
    // trailing context
    //
    do {
      if (cp.first == LG_WINDOW_END) {
        break;
      }

      cps.push_back(cp);

      if (cp.first < 0) {
        ++bad;
      }

      cp = dec.next();
    } while (--trailing > 0);

    //
    // termination
    //
    cp.first = LG_WINDOW_END;
    cps.push_back(cp);

    return bad;
  }
}

unsigned int lg_read_window(
  const char* bufStart,
  const char* bufEnd,
  uint64_t dataOffset,
  const LG_Window* inner,
  const char* encoding,
  size_t preContext,
  size_t postContext,
  int32_t** characters,
  size_t** offsets,
  size_t* clen)
{
// FIXME: it's stupid to recreate the factory each time
  DecoderFactory dfac;
  std::shared_ptr<Decoder> dec(dfac.get(encoding));

  const byte* bbeg = reinterpret_cast<const byte*>(bufStart);
  const byte* bend = reinterpret_cast<const byte*>(bufEnd);

  const byte* hbeg =
    reinterpret_cast<const byte*>(bufStart) + inner->begin - dataOffset;
  const byte* hend =
    reinterpret_cast<const byte*>(bufStart) + inner->end - dataOffset;

  std::vector< std::pair<int32_t,const byte*> > cps;

  unsigned int bad = decode(
    bbeg, bend, hbeg, hend, preContext, postContext, *dec, cps
  );

  *clen = cps.size();
  *characters = new int32_t[*clen];
  *offsets = new size_t[*clen];

  size_t i = 0;
  for (const std::pair<int32_t,const byte*>& p : cps) {
    (*characters)[i] = p.first;
    (*offsets)[i] = p.second - bbeg;
    ++i;
  }

  (*characters)[*clen-1] = LG_WINDOW_END;

  return bad;
}

unsigned int lg_hit_context(const char* bufStart,
                            const char* bufEnd,
                            uint64_t dataOffset,
                            const LG_Window* inner,
                            const char* encoding,
                            size_t windowSize,
                            uint32_t replacement,
                            const char** utf8,
                            LG_Window* outer)
{
  // decode the hit and its context using the deluxe decoder
  int32_t* characters = nullptr;
  size_t* offsets = nullptr;
  size_t clen = 0;

  const unsigned int bad = lg_read_window(bufStart, bufEnd, dataOffset, inner,
                                          encoding, windowSize, windowSize,
                                          &characters, &offsets, &clen);

  std::unique_ptr<int32_t[],void(*)(int32_t*)> pchars(
    characters, &lg_free_window_characters
  );

  std::unique_ptr<size_t[],void(*)(size_t*)> poff(
    offsets, &lg_free_window_offsets
  );

  outer->begin = dataOffset + offsets[0];
  outer->end = dataOffset + offsets[clen-1];

  // convert the code points to UTF-8
  std::vector<char> bytes;
  char buf[4];
  size_t produced;

  // encode to UTF-8, replacing bad or null elements with the replacement
  // code point, stopping one short since the last element of characters
  // is END
  for (const int32_t* i = characters; i < characters+clen-1; ++i) {
    produced = cp_to_utf8(*i <= 0 ? replacement : *i, buf);
    std::copy(buf, buf+produced, std::back_inserter(bytes));
  }

  // null-terminate the UTF-8 bytes
  bytes.push_back(0);

  char* str = new char[bytes.size()];
  std::copy(bytes.begin(), bytes.end(), str);

  *utf8 = str;

  return bad;
}

void lg_free_window_characters(int32_t* characters) {
  delete[] characters;
}

void lg_free_window_offsets(size_t* offsets) {
  delete[] offsets;
}

void lg_free_hit_context_string(const char* utf8) {
  delete[] utf8;
}
