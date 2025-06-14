#include <string.h>
#include <types.h>


ui16 *wscat(ui16 * const s1, const ui16 * const s2) {
  wscopy(s1 + wslength(s1), s2);
  return s1;
}
