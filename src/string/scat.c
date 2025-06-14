#include <string.h>
#include <types.h>


i8 *scat(i8 * const s1, const i8 * const s2) {
  scopy(s1 + slength(s1), s2);
  return s1;
}
