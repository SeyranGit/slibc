#include <types.h>
#include <bytes.h>
#include <string.h>


ui16 *wsubc(const ui16 *string, ui16 symbol) {
  const SlibcWord *wp;
  SlibcWord word;
  while (*string && ((SlibcWord)string & (SLIBC_WORD_SIZE - 1))) {
    if (*string++ == symbol) {
      return (ui16*)(string - 1);
    }
  }
  for (wp = (SlibcWord*)string;; wp++) {
    SlibcSize i;
    word = *wp;
    for (i = 0;
         i < (has_double_null(word) ? (SlibcSize)iofdzb(word) + 1 : SLIBC_WORD_SIZE / 2);
         i++) {
      ui16 c = ((ui16*)&word)[i];
      if (!c) return SlibcNull;
      if (c == symbol) {
        return (ui16*)wp + i;
      }
    }
  }
}
