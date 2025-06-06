#include <types.h>
#include <string.h>


i8 *sncopy(i8 *to, const i8 *from, slibc_size_t n) {
  i8 c;
  while (n-- && (c = *from++)) {
    *to++ = c;
  }
  n++;
  if (n) {
    while (n--) {
      *to++ = (i8)0;
    }
  }
  return --to;
}
