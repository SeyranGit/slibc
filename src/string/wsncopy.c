#include <types.h>
#include <string.h>


ui16 *wsncopy(ui16 *to, const ui16 *from, slibc_size_t n) {
  ui16 c;
  while (n-- && (c = *from++)) {
    *to++ = c;
  }
  n++;
  if (n) {
    while (n--) {
      *to++ = (ui16)0;
    }
  }
  return --to;
}
