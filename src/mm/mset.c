#include <common.h>
#include <types.h>
#include <mm.h>


static inline SlibcPointer loop_unrolling(i8 *m, SlibcWord word, SlibcSize xsize) {
  while (xsize-- > 0) {
    ((SlibcWord*)m)[0] = word;
    ((SlibcWord*)m)[1] = word;
    ((SlibcWord*)m)[2] = word;
    ((SlibcWord*)m)[3] = word;
    ((SlibcWord*)m)[4] = word;
    ((SlibcWord*)m)[5] = word;
    ((SlibcWord*)m)[6] = word;
    ((SlibcWord*)m)[7] = word;
    m += 8 * SLIBC_WORD_SIZE;
  }
  return m;
}


void mset(i8 *m, i32 c, SlibcSize size) {
  SlibcWord word = (SlibcWord)c;
  SlibcSize xsize;
  if (size > 8) {
    word |= word << 8;
    word |= word << 16;
    if (SLIBC_ARCH_64BIT) {
      word |= (word << 16) << 16;
    }
    while (((SlibcWord)m & (SLIBC_WORD_SIZE - 1)) != 0) {
      (m++)[0] = (i8)c;
      size--;
    }
    m = loop_unrolling(m, word, size / (SLIBC_WORD_SIZE * 8));
    size %= SLIBC_WORD_SIZE * 8;
    xsize = size / SLIBC_WORD_SIZE;
    while (xsize-- > 0) {
      *((SlibcWord*)m) = word;
      m += SLIBC_WORD_SIZE;
    }
    size %= SLIBC_WORD_SIZE;
  }
  while (size-- > 0) {
    *(m++) = (i8)c;
  }
}
