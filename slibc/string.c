#include "include/string.h"
#include "include/types.h"


Size length(const char *string) {
  const i64 *longword_p = (i64*)string;

  i64 longword;
  i64 h_mask;
  i64 l_mask;

  h_mask = 0x8080808080808080;
  l_mask = 0x0101010101010101;

  for (;;) {
    longword = *longword_p++;
    if (((longword - l_mask) & ~longword & h_mask) != 0) {
      const i8 *cp = (const i8*)(longword_p - 1);
      if (cp[0] == 0) return cp - string;
      if (cp[1] == 0) return cp - string + 1;
      if (cp[2] == 0) return cp - string + 2;
      if (cp[3] == 0) return cp - string + 3;
      if (cp[4] == 0) return cp - string + 4;
      if (cp[5] == 0) return cp - string + 5;
      if (cp[6] == 0) return cp - string + 6;
      if (cp[7] == 0) return cp - string + 7;
    }
  }
}
