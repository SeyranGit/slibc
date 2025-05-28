#include "include/types.h"
#include "include/string.h"


#if SLIBC_ARCH_64BIT
  #define H_MASK (slibc_word_t)0x8080808080808080
  #define L_MASK (slibc_word_t)0x0101010101010101
#else
  #define H_MASK (slibc_word_t)0x80808080
  #define L_MASK (slibc_word_t)0x01010101
#endif


#define has_zero(word) (((word - L_MASK) & ~word & H_MASK) != 0)
#define extract_byte(word, i) ((const i8*)&word)[i]


static inline i8 get_zero_index(slibc_word_t word) {
  slibc_size_t i;
  for (i = 0; i < SLIBC_WORD_SIZE; i++) {
    if (!extract_byte(word, i)) {
      return (i8)i;
    }
  }
  return -1;
}


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
  while (true) {
    longword = *longword_p++;
    if (has_zero(longword)) {
      i8 i = get_zero_index(longword);
      return (slibc_size_t)(((const i8*)(longword_p - 1) + i) - string);
    }
  }
}


static inline i8 *write_bytes(i8 *to, slibc_word_t word) {
  slibc_size_t i;
  for (i = 0; i < SLIBC_WORD_SIZE; i++, to++) {
    i8 byte = extract_byte(word, i);
    if (!(*to = byte)) {
      break;
    }
  }
  return to;
}


static inline i8 *str_aligned_copy(slibc_word_t *to, const slibc_word_t *from) {
  slibc_word_t word;
  while (true) {
    word = *from++;
    if (has_zero(word)) {
      break;
    }
    *to++ = word;
  }
  return write_bytes((i8*)to, word);
}


/*
 * bit shift and bit shift back depending on byte order of the system (little-endian/big-endian)
 */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  #define shb(word, nbytes) (word >> (nbytes * 8))
  #define shbb(word, nbytes) (word << (nbytes * 8))
#else
  #define shb(word, nbytes) (word << (nbytes * 8))
  #define shbb(word, nbytes) (word >> (nbytes * 8))
#endif


static inline i8 *str_unaligned_copy(slibc_word_t *to, const slibc_word_t *from, slibc_size_t offset) {
  slibc_word_t word = *from;
  i8 i = get_zero_index(word);
  if ((((const i8*)from) + i) < (((const i8*)from) + offset)) {
    *to = shb(word, offset);
    while (true) {
      word = *(++from);
      if (has_zero(word)) {
        break;
      }
      *to |= shbb(word, (SLIBC_WORD_SIZE - offset));
      *(++to) = shb(word, offset);
    }
    to = (slibc_word_t*)((i8*)to + (SLIBC_WORD_SIZE - offset));
  } else {
    word = shb(word, offset);
  }
  return write_bytes((i8*)to, word);
}


i8 *str_copy(i8* to, const i8* from) {
  slibc_size_t offset;
  for (offset = (-(slibc_word_t)to) & (SLIBC_WORD_SIZE - 1); offset != 0; offset--, to++) {
    if (!(*to = *from++)) {
      return to;
    }
  }
  offset = ((slibc_word_t)from) & (SLIBC_WORD_SIZE - 1);
  return (
    offset ?
    str_unaligned_copy(
      (slibc_word_t*)to,
      (const slibc_word_t*)(from - offset),
      offset
    ) :
    str_aligned_copy((slibc_word_t*)to, (const slibc_word_t*)from)
  );
}
