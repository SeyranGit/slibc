#include <types.h>
#include <bytes.h>
#include <mm.h>


static inline void write_bytes(i8 *to, i8 *from, slibc_size_t size) {
  if (size > 0) {
    while (size--) {
      *to++ = *from++;
    }
  }
}


static inline void aligned_mcopy(slibc_word_t *to, slibc_word_t *from, slibc_size_t size) {
  slibc_size_t xsize = size / SLIBC_WORD_SIZE;
  while (xsize--) {
    *to++ = *from++;
  }
  write_bytes((i8*)to, (i8*)from, size % SLIBC_WORD_SIZE);
}


static inline void unaligned_mcopy(
  slibc_word_t *to,
  slibc_word_t *from,
  slibc_size_t size,
  slibc_size_t offset
) {
  slibc_word_t word = *from;
  slibc_size_t shift = SLIBC_WORD_SIZE - offset;
  slibc_size_t xsize;
  *to = shb(word, offset);
  xsize = size / SLIBC_WORD_SIZE;
  while (xsize--) {
    word = *(++from);
    *to++ |= shbb(word, shift);
    *to = shb(word, offset);
  }
  to = (slibc_word_t*)((i8*)to + shift);
  write_bytes((i8*)to, (i8*)from, (size - shift) % SLIBC_WORD_SIZE);
}


void mcopy(i8 *to, i8 *from, slibc_size_t size) {
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
        (slibc_word_t*)(from - offset),
        (size + offset),
        (offset)
      );
    } else {
      aligned_mcopy((slibc_word_t*)to, (slibc_word_t*)from, size);
    }
  } else {
    write_bytes(to, from, size);
  }
}
