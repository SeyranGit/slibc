#include <types.h>
#include <string.h>
#include <mm.h>


i8 *sncopy(i8 *to, const i8 *from, slibc_size_t n) {
  slibc_size_t len = slength(from);
  if (len < n) {
    mset(to + len, 0, n - len);
  }
  mcopy(to, from, n);
  return to;
}
