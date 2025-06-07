#include <common.h>
#include <types.h>
#include <mm.h>


static inline slibc_pointer loop_unrolling(
  i8 *m,
  slibc_word_t word,
  slibc_size_t xsize
) {
  while (xsize-- > 0) {
    ((slibc_word_t*)m)[0] = word;
    ((slibc_word_t*)m)[1] = word;
    ((slibc_word_t*)m)[2] = word;
    ((slibc_word_t*)m)[3] = word;
    ((slibc_word_t*)m)[4] = word;
    ((slibc_word_t*)m)[5] = word;
    ((slibc_word_t*)m)[6] = word;
    ((slibc_word_t*)m)[7] = word;
    m += 8 * SLIBC_WORD_SIZE;
  }
  return m;
}


void mset(i8 *m, i32 c, slibc_size_t size) {
  slibc_word_t word = (slibc_word_t)c;
  slibc_size_t xsize;
  if (size > 8) {
    word |= word << 8;
    word |= word << 16;
    if (SLIBC_ARCH_64BIT) {
      word |= (word << 16) << 16;
    }
    while (((slibc_word_t)m & (SLIBC_WORD_SIZE - 1)) != 0) {
      (m++)[0] = (i8)c;
      size--;
    }
    m = loop_unrolling(m, word, size / (SLIBC_WORD_SIZE * 8));
    size %= SLIBC_WORD_SIZE * 8;
    xsize = size / SLIBC_WORD_SIZE;
    while (xsize-- > 0) {
      *((slibc_word_t*)m) = word;
      m += SLIBC_WORD_SIZE;
    }
    size %= SLIBC_WORD_SIZE;
  }
  while (size-- > 0) {
    *(m++) = (i8)c;
  }
}
