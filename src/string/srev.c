#include <types.h>
#include <string.h>
#include <bytes.h>



#if 0
i8 *srev(i8 * const string) {
  SlibcSize start = 0;
  SlibcSize end = slength(string) - 1;
  while (start < end) {
    i8 tmp = string[start];
    string[start++] = string[end];
    string[end--] = tmp;
  }
  return string;
}
#endif


#if 1

/*
 * Без оптимизации O3 данная версия работает на 0.8 секунды медленнее реализации выше.
 *
 * С оптимизацией O3 данная версия переворачивает
 * строку длиной в 1.95 гб (каждый символ 1 байт) за 0.337000 секунды,
 * что в 10 раз быстрее реализации выше без O3 (она выполняла ту же задачу за 3.1 секунды)
 * и в 4.6 раза с O3 (1.4 секунды).
 *
 * Примечание: текст выше относиться к коду, использующий rword без ассемблерной вставки!
 */


#define diff(a, b) (((a) - (b)) + 1)
#define LI (SLIBC_WORD_SIZE - 1)


static inline void swap(i8 **start, i8 **end) {
  i8 tmp = **start;
  *(*start)++ = **end;
  *(*end)-- = tmp;
}


#if 0

static inline SlibcWord rword(SlibcWord word) {
  i8 *start = (i8*)&word;
  i8 *end = start + LI;
  while (start < end)
    swap(&start, &end);
  return word;
}

#endif


/*
 * Эта версия rword ломает код при компиляции с -Ox
 */
static inline SlibcWord rword(SlibcWord word) {
  __asm__(
    "bswap %0" : "+r" (word)
  );
  return word;
}


i8 *srev(i8 * const string) {
  SlibcWord start = (SlibcWord)string;
  SlibcWord end = start + slength(string) - 1;
  while ((start % SLIBC_WORD_SIZE) && (start < end)) {
    swap((i8**)&start, (i8**)&end);
  }
  if (diff(end, start) >= (SLIBC_WORD_SIZE * 2)) {
    SlibcWord w0;
    SlibcWord w1;
    SlibcSize offset0;
    SlibcSize offset1;

    offset0 = (end - LI) % SLIBC_WORD_SIZE;
    offset1 = (offset0) ? (SLIBC_WORD_SIZE - offset0) : 0;

    do {
      w0 = *(SlibcWord*)(start);
      w1 = shb(*(SlibcWord*)(end - LI - offset0), offset0) | shbb(*(SlibcWord*)(end - LI + offset1), offset1);

      *(SlibcWord*)(start) = rword(w1);
      *(SlibcWord*)(end - LI) = rword(w0);

      start += SLIBC_WORD_SIZE;
      end -= SLIBC_WORD_SIZE;
    } while (diff(end, start) >= (SLIBC_WORD_SIZE * 2));
  }
  if (start) {
    while (start < end) {
      swap((i8**)&start, (i8**)&end);
    }
  }
  return string;
}

#endif
