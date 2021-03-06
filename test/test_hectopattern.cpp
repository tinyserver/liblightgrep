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

#include <scope/test.h>

#include <algorithm>

#include "stest.h"

SCOPE_FIXTURE_CTOR(hundredPatternSearch, STest, STest({
  "a|a??.|.|a?",
  "a?|aa|a??a+?",
  "a*(a)|a*?|.+",
  "a??a+.+?(a)",
  "a+(.).*?a.",
  "a??|.|.|aa|aa",
  "a+?|.?aa|a*",
  "a|a|.|.|.+.+",
  "a?|.?|.??.|a",
  "a+a+?|.+|.*?",
  "a+?|.+..|.a",
  "a?a+|a?|.|.",
  "a|a|aa.*|a+?",
  "a*a?a??|.+",
  "a+|a|.|.|(a)",
  "aa|.?.+?|.+?",
  "aa+?a*(a)",
  "a?|a|.a|a.",
  "(a)|(.)a|.a*?",
  "a*?|a*?|a*?|.|a",
  "a|.+?|a|a.+",
  "a*.aa*?|.+",
  "a??|(.).*.+?",
  "a+?|.?|.?a*",
  "a?.*..|a?",
  "a*?|.+(.)",
  "a*|aa|aa|.a",
  "a+?...a|.+",
  "a|.(.)aa|.+?",
  "a+?|a|.|a|.a.",
  "a?.?|.|.|a*",
  R"(a|a.??(a.))",
  "a.|(a)|(.*?)",
  "a.aaa??a.",
  "a??.*.??a+?",
  "a.(.)(a|.)",
  "a+.?|.|.(.)",
  "a*?a??a*?|a?",
  "a*?a.|.?a?",
  "a+aa..|a+",
  "a?|a+?|a|.(.)",
  "a|a.+|a*?a|a",
  "a+?|a|aa??|(.)",
  "a|.??a*|.a",
  "a??|.??..|.*",
  "a+?|a?.?a.",
  "aa(a).|a|.",
  "a|.|.+a|.",
  "aa.*.a.+",
  "a*.+?|.*|.*",
  "a+?a?|a|a|.*?",
  "aaaa|a|.|a|.",
  "aaaa*.a",
  "a?|a+?|a|a|aa",
  "aa*|.*|.+?",
  "a*.+?(a)*",
  "a+?(a)|a.a?",
  "a.a?a+(a)",
  "a+|(a)..|.",
  "a+?|a*?a|.|a",
  "a+?|a|.|a|(a)",
  "(a)|(a)|.a*?",
  "a|aa?a|.|.*?",
  "a|a|(a).*a+?",
  "a?|..|a.*?",
  "a+a+?|.|.|a*?",
  "a?|.+|(.)+",
  "a+..|.*|a*?",
  "a*?|.|a|a+?|.|.",
  "a*?a*?..|.",
  "a??|a*|a.+?",
  "a?a+.|.(a)",
  "a+.+?|a*?aa",
  "a?.*aa(.)",
  "a*?|a*|a.|a|a",
  "a?|(.).?|a+?",
  "a|.|.*|.aa*?",
  "a|a|.*|.?a??",
  "a*?.*|aa|a",
  "a+a|a.|.|a|.",
  "a.a|..|(.)",
  "a|.aaa|.a+",
  "a*?|a?..|(a)",
  "a*a|.|a*?|.*?",
  "a*?.+?.?(a)",
  "a|.(.)..",
  "a|..+|.*.a",
  "a+|.|a*?|.|a",
  "a|a(a).a|.*?",
  "a*?|a*.|.|.+",
  "a?|.?.*?.",
  "a??a.|a?aa",
  "a|..|..|a|(a)",
  "a*?.|.|.?.|.",
  "a??a*|a+|a+",
  "a..a|..|a??",
  "a??|a.|.??|.|a",
  "a??a?a*.?",
  "a.|.*a*?|.|a",
  "a*|..|.|..*?"
})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::vector<SearchHit>& actual = fixture.Hits;
  SCOPE_ASSERT_EQUAL(661u, actual.size());

  std::vector<SearchHit> expected{
    {0, 1, 7},
    {0, 1, 10},
    {0, 1, 12},
    {0, 1, 18},
    {0, 1, 20},
    {0, 1, 28},
    {0, 1, 29},
    {0, 1, 31},
    {0, 1, 41},
    {0, 1, 42},
    {0, 1, 45},
    {0, 1, 47},
    {0, 1, 51},
    {0, 1, 59},
    {0, 1, 60},
    {0, 1, 61},
    {0, 1, 63},
    {0, 1, 81},
    {0, 1, 85},
    {0, 1, 86},
    {0, 1, 92},
    {0, 1, 93},
    {0, 2, 15},
    {0, 2, 56},
    {0, 2, 69},
    {0, 2, 91},
    {0, 3, 14},
    {0, 3, 16},
    {0, 3, 58},
    {0, 3, 79},
    {0, 3, 80},
    {0, 3, 84},
    {0, 4, 35},
    {0, 4, 36},
    {0, 4, 46},
    {0, 4, 71},
    {0, 4, 72},
    {0, 5, 3},
    {0, 5, 21},
    {0, 5, 27},
    {0, 5, 39},
    {0, 5, 52},
    {0, 6, 4},
    {0, 6, 55},
    {0, 7, 73},
    {0, 28, 34},
    {0, 28, 48},
    {1, 2, 7},
    {1, 2, 10},
    {1, 2, 12},
    {1, 2, 18},
    {1, 2, 20},
    {1, 2, 28},
    {1, 2, 29},
    {1, 2, 31},
    {1, 2, 41},
    {1, 2, 42},
    {1, 2, 45},
    {1, 2, 47},
    {1, 2, 51},
    {1, 2, 59},
    {1, 2, 60},
    {1, 2, 61},
    {1, 2, 63},
    {1, 2, 81},
    {1, 2, 85},
    {1, 2, 86},
    {1, 2, 92},
    {1, 2, 93},
    {2, 3, 7},
    {2, 3, 10},
    {2, 3, 12},
    {2, 3, 18},
    {2, 3, 20},
    {2, 3, 28},
    {2, 3, 29},
    {2, 3, 31},
    {2, 3, 41},
    {2, 3, 42},
    {2, 3, 45},
    {2, 3, 47},
    {2, 3, 51},
    {2, 3, 59},
    {2, 3, 60},
    {2, 3, 61},
    {2, 3, 63},
    {2, 3, 81},
    {2, 3, 85},
    {2, 3, 86},
    {2, 3, 92},
    {2, 3, 93},
    {2, 4, 15},
    {2, 4, 69},
    {2, 4, 91},
    {2, 5, 56},
    {2, 6, 57},
    {3, 4, 7},
    {3, 4, 14},
    {3, 4, 20},
    {3, 4, 28},
    {3, 4, 29},
    {3, 4, 42},
    {3, 4, 47},
    {3, 4, 51},
    {3, 4, 58},
    {3, 4, 59},
    {3, 4, 60},
    {3, 4, 61},
    {3, 4, 79},
    {3, 4, 93},
    {3, 5, 18},
    {3, 5, 80},
    {3, 5, 92},
    {3, 6, 45},
    {3, 6, 81},
    {3, 6, 84},
    {3, 7, 85},
    {3, 28, 10},
    {3, 28, 86},
    {4, 5, 7},
    {4, 5, 12},
    {4, 5, 20},
    {4, 5, 28},
    {4, 5, 29},
    {4, 5, 31},
    {4, 5, 41},
    {4, 5, 42},
    {4, 5, 46},
    {4, 5, 47},
    {4, 5, 51},
    {4, 5, 59},
    {4, 5, 60},
    {4, 5, 61},
    {4, 5, 63},
    {4, 5, 93},
    {4, 6, 14},
    {4, 6, 15},
    {4, 6, 58},
    {4, 6, 69},
    {4, 6, 79},
    {4, 6, 91},
    {4, 7, 36},
    {4, 7, 71},
    {4, 7, 72},
    {4, 8, 35},
    {5, 6, 7},
    {5, 6, 12},
    {5, 6, 18},
    {5, 6, 20},
    {5, 6, 28},
    {5, 6, 29},
    {5, 6, 31},
    {5, 6, 39},
    {5, 6, 41},
    {5, 6, 42},
    {5, 6, 46},
    {5, 6, 47},
    {5, 6, 51},
    {5, 6, 59},
    {5, 6, 60},
    {5, 6, 61},
    {5, 6, 63},
    {5, 6, 92},
    {5, 6, 93},
    {5, 8, 3},
    {5, 8, 21},
    {5, 8, 56},
    {5, 8, 80},
    {5, 28, 27},
    {6, 7, 7},
    {6, 7, 14},
    {6, 7, 20},
    {6, 7, 28},
    {6, 7, 29},
    {6, 7, 42},
    {6, 7, 46},
    {6, 7, 47},
    {6, 7, 51},
    {6, 7, 58},
    {6, 7, 59},
    {6, 7, 60},
    {6, 7, 61},
    {6, 7, 79},
    {6, 7, 93},
    {6, 8, 15},
    {6, 8, 18},
    {6, 8, 55},
    {6, 8, 69},
    {6, 8, 81},
    {6, 8, 84},
    {6, 8, 92},
    {6, 9, 45},
    {7, 8, 7},
    {7, 8, 12},
    {7, 8, 14},
    {7, 8, 20},
    {7, 8, 28},
    {7, 8, 29},
    {7, 8, 31},
    {7, 8, 39},
    {7, 8, 41},
    {7, 8, 42},
    {7, 8, 46},
    {7, 8, 47},
    {7, 8, 51},
    {7, 8, 58},
    {7, 8, 59},
    {7, 8, 60},
    {7, 8, 61},
    {7, 8, 63},
    {7, 8, 85},
    {7, 8, 93},
    {7, 9, 36},
    {7, 9, 71},
    {7, 9, 72},
    {7, 9, 79},
    {7, 9, 91},
    {7, 12, 4},
    {8, 9, 7},
    {8, 9, 14},
    {8, 9, 18},
    {8, 9, 20},
    {8, 9, 28},
    {8, 9, 29},
    {8, 9, 42},
    {8, 9, 46},
    {8, 9, 47},
    {8, 9, 51},
    {8, 9, 55},
    {8, 9, 58},
    {8, 9, 59},
    {8, 9, 60},
    {8, 9, 61},
    {8, 9, 93},
    {8, 10, 15},
    {8, 10, 69},
    {8, 10, 80},
    {8, 10, 92},
    {8, 11, 84},
    {8, 12, 85},
    {8, 28, 21},
    {9, 10, 7},
    {9, 10, 14},
    {9, 10, 20},
    {9, 10, 28},
    {9, 10, 29},
    {9, 10, 36},
    {9, 10, 42},
    {9, 10, 46},
    {9, 10, 47},
    {9, 10, 51},
    {9, 10, 58},
    {9, 10, 59},
    {9, 10, 60},
    {9, 10, 61},
    {9, 10, 79},
    {9, 10, 93},
    {9, 11, 18},
    {9, 11, 55},
    {9, 11, 71},
    {9, 11, 81},
    {9, 12, 45},
    {10, 11, 7},
    {10, 11, 12},
    {10, 11, 14},
    {10, 11, 20},
    {10, 11, 28},
    {10, 11, 29},
    {10, 11, 31},
    {10, 11, 39},
    {10, 11, 41},
    {10, 11, 42},
    {10, 11, 46},
    {10, 11, 47},
    {10, 11, 51},
    {10, 11, 58},
    {10, 11, 59},
    {10, 11, 60},
    {10, 11, 61},
    {10, 11, 63},
    {10, 11, 92},
    {10, 11, 93},
    {10, 12, 15},
    {10, 12, 36},
    {10, 12, 56},
    {10, 12, 69},
    {10, 12, 72},
    {10, 12, 79},
    {10, 12, 80},
    {10, 12, 91},
    {10, 14, 3},
    {10, 14, 35},
    {11, 12, 7},
    {11, 12, 14},
    {11, 12, 18},
    {11, 12, 20},
    {11, 12, 28},
    {11, 12, 29},
    {11, 12, 42},
    {11, 12, 46},
    {11, 12, 47},
    {11, 12, 51},
    {11, 12, 55},
    {11, 12, 58},
    {11, 12, 59},
    {11, 12, 60},
    {11, 12, 61},
    {11, 12, 93},
    {11, 13, 92},
    {11, 14, 84},
    {12, 13, 7},
    {12, 13, 14},
    {12, 13, 20},
    {12, 13, 28},
    {12, 13, 29},
    {12, 13, 36},
    {12, 13, 42},
    {12, 13, 46},
    {12, 13, 47},
    {12, 13, 51},
    {12, 13, 58},
    {12, 13, 59},
    {12, 13, 60},
    {12, 13, 61},
    {12, 13, 79},
    {12, 13, 93},
    {12, 14, 15},
    {12, 14, 18},
    {12, 14, 55},
    {12, 14, 69},
    {12, 14, 71},
    {12, 14, 80},
    {12, 14, 81},
    {12, 15, 45},
    {12, 16, 85},
    {13, 14, 7},
    {13, 14, 12},
    {13, 14, 14},
    {13, 14, 20},
    {13, 14, 28},
    {13, 14, 29},
    {13, 14, 31},
    {13, 14, 39},
    {13, 14, 41},
    {13, 14, 42},
    {13, 14, 46},
    {13, 14, 47},
    {13, 14, 51},
    {13, 14, 58},
    {13, 14, 59},
    {13, 14, 60},
    {13, 14, 61},
    {13, 14, 63},
    {13, 14, 92},
    {13, 14, 93},
    {13, 15, 36},
    {13, 15, 56},
    {13, 15, 72},
    {13, 15, 79},
    {13, 15, 91},
    {13, 18, 4},
    {14, 15, 7},
    {14, 15, 14},
    {14, 15, 18},
    {14, 15, 20},
    {14, 15, 28},
    {14, 15, 29},
    {14, 15, 42},
    {14, 15, 46},
    {14, 15, 47},
    {14, 15, 51},
    {14, 15, 55},
    {14, 15, 58},
    {14, 15, 59},
    {14, 15, 60},
    {14, 15, 61},
    {14, 15, 93},
    {14, 16, 15},
    {14, 16, 69},
    {14, 16, 80},
    {14, 16, 92},
    {14, 17, 84},
    {15, 16, 7},
    {15, 16, 14},
    {15, 16, 20},
    {15, 16, 28},
    {15, 16, 29},
    {15, 16, 36},
    {15, 16, 42},
    {15, 16, 46},
    {15, 16, 47},
    {15, 16, 51},
    {15, 16, 58},
    {15, 16, 59},
    {15, 16, 60},
    {15, 16, 61},
    {15, 16, 79},
    {15, 16, 93},
    {15, 17, 18},
    {15, 17, 55},
    {15, 17, 71},
    {15, 17, 81},
    {15, 18, 45},
    {16, 17, 7},
    {16, 17, 12},
    {16, 17, 14},
    {16, 17, 20},
    {16, 17, 28},
    {16, 17, 29},
    {16, 17, 31},
    {16, 17, 39},
    {16, 17, 41},
    {16, 17, 42},
    {16, 17, 46},
    {16, 17, 47},
    {16, 17, 51},
    {16, 17, 58},
    {16, 17, 59},
    {16, 17, 60},
    {16, 17, 61},
    {16, 17, 63},
    {16, 17, 85},
    {16, 17, 92},
    {16, 17, 93},
    {16, 18, 15},
    {16, 18, 36},
    {16, 18, 56},
    {16, 18, 69},
    {16, 18, 72},
    {16, 18, 79},
    {16, 18, 80},
    {16, 18, 91},
    {16, 20, 35},
    {16, 28, 3},
    {17, 18, 7},
    {17, 18, 14},
    {17, 18, 18},
    {17, 18, 20},
    {17, 18, 28},
    {17, 18, 29},
    {17, 18, 42},
    {17, 18, 46},
    {17, 18, 47},
    {17, 18, 51},
    {17, 18, 55},
    {17, 18, 58},
    {17, 18, 59},
    {17, 18, 60},
    {17, 18, 61},
    {17, 18, 93},
    {17, 19, 92},
    {17, 21, 85},
    {17, 28, 84},
    {18, 19, 7},
    {18, 19, 14},
    {18, 19, 18},
    {18, 19, 20},
    {18, 19, 28},
    {18, 19, 29},
    {18, 19, 36},
    {18, 19, 42},
    {18, 19, 46},
    {18, 19, 47},
    {18, 19, 51},
    {18, 19, 55},
    {18, 19, 58},
    {18, 19, 59},
    {18, 19, 60},
    {18, 19, 61},
    {18, 19, 79},
    {18, 19, 93},
    {18, 20, 15},
    {18, 20, 69},
    {18, 20, 80},
    {19, 20, 7},
    {19, 20, 14},
    {19, 20, 18},
    {19, 20, 20},
    {19, 20, 28},
    {19, 20, 29},
    {19, 20, 36},
    {19, 20, 42},
    {19, 20, 46},
    {19, 20, 47},
    {19, 20, 51},
    {19, 20, 55},
    {19, 20, 58},
    {19, 20, 59},
    {19, 20, 60},
    {19, 20, 61},
    {19, 20, 79},
    {19, 20, 93},
    {19, 21, 92},
    {20, 21, 7},
    {20, 21, 14},
    {20, 21, 18},
    {20, 21, 20},
    {20, 21, 28},
    {20, 21, 29},
    {20, 21, 36},
    {20, 21, 42},
    {20, 21, 46},
    {20, 21, 47},
    {20, 21, 51},
    {20, 21, 55},
    {20, 21, 58},
    {20, 21, 59},
    {20, 21, 60},
    {20, 21, 61},
    {20, 21, 79},
    {20, 21, 93},
    {20, 22, 15},
    {20, 22, 69},
    {20, 22, 80},
    {21, 22, 7},
    {21, 22, 14},
    {21, 22, 18},
    {21, 22, 20},
    {21, 22, 28},
    {21, 22, 29},
    {21, 22, 36},
    {21, 22, 42},
    {21, 22, 46},
    {21, 22, 47},
    {21, 22, 51},
    {21, 22, 55},
    {21, 22, 58},
    {21, 22, 59},
    {21, 22, 60},
    {21, 22, 61},
    {21, 22, 79},
    {21, 22, 93},
    {21, 23, 92},
    {21, 25, 85},
    {22, 23, 7},
    {22, 23, 14},
    {22, 23, 18},
    {22, 23, 20},
    {22, 23, 28},
    {22, 23, 29},
    {22, 23, 36},
    {22, 23, 42},
    {22, 23, 46},
    {22, 23, 47},
    {22, 23, 51},
    {22, 23, 55},
    {22, 23, 58},
    {22, 23, 59},
    {22, 23, 60},
    {22, 23, 61},
    {22, 23, 79},
    {22, 23, 93},
    {22, 24, 15},
    {22, 24, 69},
    {22, 24, 80},
    {23, 24, 7},
    {23, 24, 14},
    {23, 24, 18},
    {23, 24, 20},
    {23, 24, 28},
    {23, 24, 29},
    {23, 24, 36},
    {23, 24, 42},
    {23, 24, 46},
    {23, 24, 47},
    {23, 24, 51},
    {23, 24, 55},
    {23, 24, 58},
    {23, 24, 59},
    {23, 24, 60},
    {23, 24, 61},
    {23, 24, 79},
    {23, 24, 93},
    {23, 25, 92},
    {24, 25, 7},
    {24, 25, 14},
    {24, 25, 18},
    {24, 25, 20},
    {24, 25, 28},
    {24, 25, 29},
    {24, 25, 36},
    {24, 25, 42},
    {24, 25, 46},
    {24, 25, 47},
    {24, 25, 51},
    {24, 25, 55},
    {24, 25, 58},
    {24, 25, 59},
    {24, 25, 60},
    {24, 25, 61},
    {24, 25, 79},
    {24, 25, 93},
    {24, 26, 15},
    {24, 26, 69},
    {24, 26, 80},
    {25, 26, 7},
    {25, 26, 14},
    {25, 26, 18},
    {25, 26, 20},
    {25, 26, 28},
    {25, 26, 29},
    {25, 26, 36},
    {25, 26, 42},
    {25, 26, 46},
    {25, 26, 47},
    {25, 26, 51},
    {25, 26, 55},
    {25, 26, 58},
    {25, 26, 59},
    {25, 26, 60},
    {25, 26, 61},
    {25, 26, 79},
    {25, 26, 93},
    {25, 27, 92},
    {26, 27, 7},
    {26, 27, 14},
    {26, 27, 20},
    {26, 27, 28},
    {26, 27, 29},
    {26, 27, 36},
    {26, 27, 42},
    {26, 27, 46},
    {26, 27, 47},
    {26, 27, 51},
    {26, 27, 58},
    {26, 27, 59},
    {26, 27, 60},
    {26, 27, 61},
    {26, 27, 79},
    {26, 27, 93},
    {26, 28, 15},
    {26, 28, 18},
    {26, 28, 55},
    {26, 28, 69},
    {26, 28, 71},
    {26, 28, 80},
    {26, 28, 81},
    {27, 28, 7},
    {27, 28, 12},
    {27, 28, 14},
    {27, 28, 20},
    {27, 28, 28},
    {27, 28, 29},
    {27, 28, 31},
    {27, 28, 36},
    {27, 28, 39},
    {27, 28, 41},
    {27, 28, 42},
    {27, 28, 45},
    {27, 28, 46},
    {27, 28, 47},
    {27, 28, 51},
    {27, 28, 58},
    {27, 28, 59},
    {27, 28, 60},
    {27, 28, 61},
    {27, 28, 63},
    {27, 28, 79},
    {27, 28, 85},
    {27, 28, 92},
    {27, 28, 93}
  };

  std::sort(actual.begin(), actual.end());
  std::sort(expected.begin(), expected.begin());

  std::pair<std::vector<SearchHit>::iterator,
            std::vector<SearchHit>::iterator> mis(
    std::mismatch(expected.begin(), expected.end(), actual.begin())
  );

  if (mis.first != expected.end()) {
    SCOPE_ASSERT_EQUAL(*mis.first, *mis.second);
  }
}
