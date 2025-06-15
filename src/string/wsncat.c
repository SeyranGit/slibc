#include <string.h>
#include <types.h>
#include <mm.h>
#include <math.h>


ui16 *wsncat(ui16 *s1, const ui16 * const s2, SlibcSize n) {
  ui16 *copy = s1;
  s1 += wslength(s1);
  n = min(n, wslength(s2));
  s1[n] = (ui16)0;
  mcopy((i8*)s1, (const i8*)s2, n * 2);
  return copy;
}
