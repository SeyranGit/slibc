#include <types.h>
#include <bytes.h>
#include <string.h>


SlibcSize wslength(const ui16 * const string) {
  const ui16 *wchar_p;
  const SlibcWord *longword_p;
  SlibcWord longword;
  if (string == SlibcNull) return (SlibcSize)0;
  for (wchar_p = string;
       ((SlibcWord)wchar_p & (SLIBC_WORD_SIZE - 1)) != 0;
       wchar_p++) {
    if (!(*wchar_p)) {
      return (SlibcSize)(wchar_p - string);
    }
  }
  longword_p = (const SlibcWord*)wchar_p;
  while (true) {
    longword = *longword_p++;
    if (has_double_null(longword)) {
      i8 i = iofdzb(longword);
      if (i != -1) {
        return (SlibcSize)(((const ui16*)(longword_p - 1) + i) - string);
      }
    }
  }
}
