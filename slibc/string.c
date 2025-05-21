#include "include/string.h"
#include "include/types.h"


Size length(const char * const string) {
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
      for (ui8 i = 0; i < 8; i++) {
        if (!cp[i]) {
          return (Size)((cp + i) - string);
        }
      }
    }
  }
}
