#include "include/types.h"
#include "include/string.h"


#if SLIBC_ARCH_64BIT
  #define H_MASK (slibc_word_t)0x8080808080808080
  #define L_MASK (slibc_word_t)0x0101010101010101
#else
  #define H_MASK (slibc_word_t)0x80808080
  #define L_MASK (slibc_word_t)0x01010101
#endif


#define has_zero(word) ((word - L_MASK) & ~word & H_MASK) != 0
#define extract_byte(word, i) ((const i8*)&word)[i]


slibc_size_t str_length(const i8 * const string) {
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

  for (;;) {
    longword = *longword_p++;
    if (has_zero(longword)) {
      for (ui8 i = 0; i < 8; i++) {
        if (!extract_byte(longword, i)) {
          return (slibc_size_t)(((const i8*)(longword_p - 1) + i) - string);
        }
      }
    }
  }
}


static inline i8 *write_bytes(slibc_word_t *to, slibc_word_t word) {
  i8 *to_p = (i8*)to;
  for (slibc_size_t i = 0; i < SLIBC_WORD_SIZE; i++, to_p++) {
    i8 byte = extract_byte(word, i);
    if (!(*to_p = byte)) {
      break;
    }
  }
  return to_p;
}


static inline i8 *str_aligned_copy(slibc_word_t *to, const slibc_word_t *from) {
  slibc_word_t word;
  while (1) {
    word = *from++;
    if (has_zero(word)) {
      break;
    }
    *to++ = word;
  }
  return write_bytes(to, word);
}


static inline i8 *str_unaligned_copy(slibc_word_t *to, const i8 *from, slibc_size_t shifts) {
  /*
  for (ui8 i = 0; i < shifts; i++) {
    i8 c = *from++;
    ((i8*)to)[i] = c;
    if (!c) {
      return ((i8*)to) + i;
    }
  }
  */

  return 0;
}


i8 *str_copy(i8* to, const i8* from) {
  slibc_size_t shifts;
  for (shifts = (-(slibc_word_t)to) & (SLIBC_WORD_SIZE - 1); shifts != 0; shifts--, to++) {
    if (!(*to = *from++)) {
      return to;
    }
  }
  shifts = 0; // (-(slibc_word_t)from) & (SLIBC_WORD_SIZE - 1);
  return (
    shifts ?
    str_unaligned_copy((slibc_word_t*)to, from, shifts) :
    str_aligned_copy((slibc_word_t*)to, (const slibc_word_t*)from)
  );
}
