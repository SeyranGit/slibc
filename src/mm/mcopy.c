#include "common.h"
#include <types.h>
#include <bytes.h>
#include <mm.h>


static inline void write_bytes(i8 *to, const i8 *from, SlibcSize size) {
  if (size <= 0) return;
  while (size--) {
    *to++ = *from++;
  }
}


static inline void aligned_mcopy(SlibcWord *to, const SlibcWord *from, SlibcSize size) {
  SlibcSize xsize = size / SLIBC_WORD_SIZE;
  while (xsize--) {
    *to++ = *from++;
  }
  write_bytes((i8*)to, (const i8*)from, size % SLIBC_WORD_SIZE);
}


static inline void unaligned_mcopy(SlibcWord *to, const SlibcWord *from, SlibcSize size, SlibcSize offset) {
  SlibcWord word = *from;
  SlibcSize xsize;
  xsize = size / SLIBC_WORD_SIZE;
  while (xsize--) {
    *to = shb(word, offset);
    word = *(++from);
    *to++ |= shbb(word, (SLIBC_WORD_SIZE - offset));
  }
  from = (const SlibcWord*)((const i8*)from + offset);
  write_bytes((i8*)to, (const i8*)from, SLIBC_ARCH_64BIT ? 2 : 1);
}


void mcopy(i8 *to, const i8 *from, SlibcSize size) {
  SlibcSize offset;
  if (size > SLIBC_WORD_SIZE) {
    for ((offset) = (-(SlibcWord)to & (SLIBC_WORD_SIZE - 1)); 
         (offset != 0) && size;
         (offset)--, size--, to++, from++) {
      *to = *from;
    }
    offset = (SlibcWord)from & (SLIBC_WORD_SIZE - 1);
    if (offset) {
      unaligned_mcopy(
        (SlibcWord*)to,
        (const SlibcWord*)(from - offset),
        (size + offset),
        (offset)
      );
    } else {
      aligned_mcopy((SlibcWord*)to, (const SlibcWord*)from, size);
    }
  } else {
    write_bytes(to, from, size);
  }
}
