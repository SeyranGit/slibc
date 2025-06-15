#include <types.h>
#include <bytes.h>
#include <string.h>


SlibcSize slength(const i8 * const string) {
  const i8 *char_p;
  const SlibcWord *longword_p;
  // longword is intended to store the read multi-byte word
  SlibcWord longword;

  if (string == SlibcNull) return (SlibcSize)0;   
  // char_p pointer alignment loop.
  // If during the alignment process a null byte is encountered,
  // indicating the end of the string, the length can be immediately
  // calculated and returned.
  for (char_p = string; ((SlibcWord)char_p & (SLIBC_WORD_SIZE - 1)) != 0; char_p++) {
    if (!(*char_p)) {
      return (SlibcSize)(char_p - string);
    }
  }
  // Preparing for reading by words
  longword_p = (const SlibcWord*)char_p;
  while (true) {
    longword = *longword_p++;
    // At each iteration, the read word is checked for the presence of a null byte.
    if (has_null(longword)) {
      i8 i = iofzb(longword);
      return (SlibcSize)(((const i8*)(longword_p - 1) + i) - string);
    }
  }
}
