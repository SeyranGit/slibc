#include "include/types.h"
#include "include/string.h"


#if SLIBC_ARCH_64BIT
  #define H_MASK (slibc_word_t)0x8080808080808080
  #define L_MASK (slibc_word_t)0x0101010101010101
#else
  #define H_MASK (slibc_word_t)0x80808080
  #define L_MASK (slibc_word_t)0x01010101
#endif


slibc_size_t length(const i8 * const string) {
  const i8 *char_p;
  const slibc_word_t *longword_p;

  slibc_word_t longword;

  for (char_p = string; ((slibc_word_t)char_p & (SLIBC_WORD_SIZE - 1)) != 0; char_p++) {
    if (*char_p == '\x00') {
      return (slibc_size_t)(char_p - string);
    }
  }

  longword_p = (const slibc_word_t*)char_p;

  for (;;) {
    longword = *longword_p++;
    if (((longword - L_MASK) & ~longword & H_MASK) != 0) {
      const i8 *cp = (const i8*)(longword_p - 1);
      for (ui8 i = 0; i < 8; i++) {
        if (!cp[i]) {
          return (slibc_size_t)((cp + i) - string);
        }
      }
    }
  }
}
