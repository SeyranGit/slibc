#include <types.h>
#include <bytes.h>
#include <string.h>


slibc_size_t wslength(const ui16 * const string) {
  const ui16 *wchar_p;
  const slibc_word_t *longword_p;
  slibc_word_t longword;
  if (string == slibc_null) return (slibc_size_t)0;
  for (wchar_p = string;
       ((slibc_word_t)wchar_p & (SLIBC_WORD_SIZE - 1)) != 0;
       wchar_p++) {
    if (!(*wchar_p)) {
      return (slibc_size_t)(wchar_p - string);
    }
  }
  longword_p = (const slibc_word_t*)wchar_p;
  while (true) {
    longword = *longword_p++;
    if (has_double_null(longword)) {
      i8 i = iofdzb(longword);
      if (i != -1) {
        return (slibc_size_t)(((const ui16*)(longword_p - 1) + i) - string);
      }
    }
  }
}
