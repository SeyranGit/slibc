#include <string.h>
#include <types.h>
#include <mm.h>
#include <math.h>


i8 *sncat(i8 *s1, const i8 * const s2, SlibcSize n) {
  i8 *copy = s1;
  s1 += slength(s1);
  n = min(n, slength(s2));
  s1[n] = (i8)0;
  mcopy(s1, s2, n);
  return copy;
}
