#include <common.h>
#include <types.h>
#include <mm.h>


static inline slibc_pointer loop_unrolling(
  i8 *m,
  slibc_word_t word,
  slibc_size_t xcount
) {
  while (xcount-- > 0) {
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


void mset(i8 *m, i32 c, slibc_size_t count) {
  slibc_word_t word = (slibc_word_t)c;
  slibc_size_t xcount;
  if (count > 8) {
    word |= word << 8;
    word |= word << 16;
    if (SLIBC_ARCH_64BIT) {
      word |= (word << 16) << 16;
    }
    while (((slibc_word_t)m & (SLIBC_WORD_SIZE - 1)) != 0) {
      (m++)[0] = (i8)c;
      count--;
    }
    m = loop_unrolling(m, word, count / (SLIBC_WORD_SIZE * 8));
    count %= SLIBC_WORD_SIZE * 8;
    xcount = count / SLIBC_WORD_SIZE;
    while (xcount-- > 0) {
      *((slibc_word_t*)m) = word;
      m += SLIBC_WORD_SIZE;
    }
    count %= SLIBC_WORD_SIZE;
  }
  while (count-- > 0) {
    *(m++) = (i8)c;
  }
}
