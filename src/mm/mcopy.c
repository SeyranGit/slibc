#include <types.h>
#include <bytes.h>
#include <mm.h>
#include <stdio.h>


static inline void write_bytes(i8 *to, const i8 *from, slibc_size_t size) {
  if (size <= 0) return;
  while (size--) {
    *to++ = *from++;
  }
}


static inline void aligned_mcopy(slibc_word_t *to, const slibc_word_t *from, slibc_size_t size) {
  slibc_size_t xsize = size / SLIBC_WORD_SIZE;
  while (xsize--) {
    *to++ = *from++;
  }
  write_bytes((i8*)to, (const i8*)from, size % SLIBC_WORD_SIZE);
}


static inline void unaligned_mcopy(slibc_word_t *to, const slibc_word_t *from, slibc_size_t size, slibc_size_t offset) {
  slibc_word_t word = *from;
  slibc_size_t xsize;
  xsize = size / SLIBC_WORD_SIZE;
  while (xsize--) {
    *to = shb(word, offset);
    word = *(++from);
    *to++ |= shbb(word, (SLIBC_WORD_SIZE - offset));
  }
  from = (const slibc_word_t*)((const i8*)from + offset);
  write_bytes((i8*)to, (const i8*)from, 2);
}


void mcopy(i8 *to, const i8 *from, slibc_size_t size) {
  slibc_size_t offset;
  if (size > SLIBC_WORD_SIZE) {
    for ((offset) = (-(slibc_word_t)to & (SLIBC_WORD_SIZE - 1)); 
         (offset != 0) && size;
         (offset)--, size--, to++, from++) {
      *to = *from;
    }
    offset = (slibc_word_t)from & (SLIBC_WORD_SIZE - 1);
    if (offset) {
      unaligned_mcopy(
        (slibc_word_t*)to,
        (const slibc_word_t*)(from - offset),
        (size + offset),
        (offset)
      );
    } else {
      aligned_mcopy((slibc_word_t*)to, (const slibc_word_t*)from, size);
    }
  } else {
    write_bytes(to, from, size);
  }
}
