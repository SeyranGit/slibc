#include <types.h>
#include <string.h>
#include <mm.h>


ui16 *wsncopy(ui16 *to, const ui16 *from, slibc_size_t n) {
  slibc_size_t len = wslength(from);
  if (len < n) {
    mset((i8*)(to + len), 0, (n - len) * 2);
  }
  mcopy((i8*)to, (const i8*)from, n * 2);
  return to;
}
