#include <types.h>
#include <bytes.h>
#include <string.h>


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


static inline i8 *aligned_scopy(slibc_word_t *to, const slibc_word_t *from) {
  slibc_word_t word;
  while (true) {
    word = *from++;
    if (has_null(word)) {
      break;
    }
    *to++ = word;
  }
  return write_bytes((i8*)to, word);
}


static inline i8 *unaligned_scopy(slibc_word_t *to, const slibc_word_t *from, slibc_size_t offset) {
  slibc_word_t word = *from;
  i8 i = iofzb(word);
  if ((((const i8*)from) + i) < (((const i8*)from) + offset)) {
    *to = shb(word, offset);
    while (true) {
      word = *(++from);
      if (has_null(word)) {
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


i8 *scopy(i8 *to, const i8 *from) {
  slibc_size_t offset;
  for (offset = ((slibc_word_t)to) & (SLIBC_WORD_SIZE - 1); offset != 0; offset--, to++) {
    if (!(*to = *from++)) {
      return to;
    }
  }
  offset = ((slibc_word_t)from) & (SLIBC_WORD_SIZE - 1);
  return (
    offset ?
    unaligned_scopy(
      (slibc_word_t*)to,
      (const slibc_word_t*)(from - offset),
      offset
    ) :
    aligned_scopy((slibc_word_t*)to, (const slibc_word_t*)from)
  );
}
