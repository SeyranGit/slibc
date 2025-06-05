#include <types.h>
#include <bytes.h>
#include <string.h>


slibc_size_t slength(const i8 * const string) {
  const i8 *char_p;
  const slibc_word_t *longword_p;
  // longword is intended to store the read multi-byte word
  slibc_word_t longword;

  if (string == slibc_null) return (slibc_size_t)0;   
  // char_p pointer alignment loop.
  // If during the alignment process a null byte is encountered,
  // indicating the end of the string, the length can be immediately
  // calculated and returned.
  for (char_p = string; ((slibc_word_t)char_p & (SLIBC_WORD_SIZE - 1)) != 0; char_p++) {
    if (!(*char_p)) {
      return (slibc_size_t)(char_p - string);
    }
  }
  // Preparing for reading by words
  longword_p = (const slibc_word_t*)char_p;
  while (true) {
    longword = *longword_p++;
    // At each iteration, the read word is checked for the presence of a null byte.
    if (has_zero(longword)) {
      i8 i = get_zero_index(longword);
      return (slibc_size_t)(((const i8*)(longword_p - 1) + i) - string);
    }
  }
}
