#include <types.h>
#include <bytes.h>
#include <string.h>


i8 *subc(const i8 *string, i8 symbol) {
  const SlibcWord *wp;
  SlibcWord word;
  while (*string && ((SlibcWord)string & (SLIBC_WORD_SIZE - 1))) {
    if (*string++ == symbol) {
      return (i8*)(string - 1);
    }
  }
  for (wp = (SlibcWord*)string;; wp++) {
    SlibcSize i;
    word = *wp;
    for (i = 0;
         i < (has_null(word) ? (SlibcSize)iofzb(word) + 1 : SLIBC_WORD_SIZE);
         i++) {
      i8 c = ((i8*)&word)[i];
      if (!c) return SlibcNull;
      if (c == symbol) {
        return (i8*)wp + i;
      }
    }
  }
}
