#include <types.h>
#include <string.h>
#include <mm.h>


i8 *sncopy(i8 *to, const i8 *from, SlibcSize n) {
  SlibcSize len = slength(from);
  if (len < n) {
    mset(to + len, 0, n - len);
  }
  mcpy(to, from, n);
  return to;
}
