#include <types.h>
#include <bytes.h>
#include <string.h>


slibc_size_t slength(const i8 * const string) {
  const i8 *char_p;
  const slibc_word_t *longword_p;
  slibc_word_t longword;
  if (string == slibc_null) return (slibc_size_t)0;
  for (char_p = string; ((slibc_word_t)char_p & (SLIBC_WORD_SIZE - 1)) != 0; char_p++) {
    if (!(*char_p)) {
      return (slibc_size_t)(char_p - string);
    }
  }
  longword_p = (const slibc_word_t*)char_p;
  while (true) {
    longword = *longword_p++;
    if (has_zero(longword)) {
      i8 i = get_zero_index(longword);
      return (slibc_size_t)(((const i8*)(longword_p - 1) + i) - string);
    }
  }
}
