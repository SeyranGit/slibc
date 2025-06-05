#include <bytes.h>
#include <types.h>


static inline ui16 *write_double_bytes(ui16 *to, slibc_word_t word) {
  slibc_size_t i;
  for (i = 0; i < SLIBC_WORD_SIZE / 2; i++, to++) {
    ui16 double_byte = extract_short(word, i);
    if (!(*to = double_byte)) {
      break;
    }
  }
  return to;
}


static inline ui16 *aligned_wscopy(slibc_word_t *to, const slibc_word_t *from) {
  slibc_word_t word;
  while (true) {
    word = *from++;
    if (has_double_null(word)) {
      break;
    }
    *to++ = word;
  }
  return write_double_bytes((ui16*)to, word);
}


static inline ui16 *unaligned_scopy(slibc_word_t *to, const slibc_word_t *from, slibc_size_t offset) {
  return 0;
}


ui16 *wscopy(ui16 *to, const ui16 *from) {
  slibc_size_t offset;
  for (; ((slibc_word_t)to & (SLIBC_WORD_SIZE - 1)) != 0; to++) {
    if (!(*to = *from++)) {
      return to;
    }
  }
  return aligned_wscopy((slibc_word_t*)to, (const slibc_word_t*)from);
}
