#include <common.h>
#include <types.h>
#include <string.h>
#include <bytes.h>


#define diff(a, b) (SlibcWord)(((a) - (b)) + 1)
#define WLI (SLIBC_WORD_SIZE - 1)


static inline void swap(i8 *start, i8 *end) {
  i8 tmp = *start;
  *start = *end;
  *end = tmp;
}


#if 0

static inline SlibcWord rword(SlibcWord word) {
  i8 *start = (i8*)&word;
  i8 *end = start + WLI;
  while (start < end)
    swap(&start, &end);
  return word;
}


static inline SlibcWord rword(SlibcWord word) {
  __asm__("bswap %0" : "+r" (word));
  return word;
}

#endif


#if SLIBC_ARCH_64BIT
  #define bswap __builtin_bswap64
#else
  #define bswap __builtin_bswap32
#endif


i8 *srev(i8 * const string) {
  i8 *start = string;
  i8 *end = start + slength(start) - 1;
  while (((SlibcWord)start % SLIBC_WORD_SIZE) && (start < end)) {
    swap(start++, end--);
  }
  if (diff(end, start) >= (SLIBC_WORD_SIZE * 2)) {
    SlibcWord w0;
    SlibcWord w1;
    SlibcSize offset0;
    SlibcSize offset1;

    offset0 = (SlibcWord)(end - WLI) % SLIBC_WORD_SIZE;
    offset1 = (offset0) ? (SLIBC_WORD_SIZE - offset0) : 0;

    do {
      w0 = *(SlibcWord*)(start);
      w1 = shb(*(SlibcWord*)(end - WLI - offset0), offset0) | shbb(*(SlibcWord*)(end - WLI + offset1), offset1);

      *(SlibcWord*)(start) = bswap(w1);
      *(SlibcWord*)(end - WLI) = bswap(w0);

      start += SLIBC_WORD_SIZE; end -= SLIBC_WORD_SIZE;
    } while (diff(end, start) >= (SLIBC_WORD_SIZE * 2));
  }
  if (start) {
    while (start < end) {
      swap(start++, end--);
    }
  }
  return string;
}
