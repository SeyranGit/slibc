#include <types.h>
#include <string.h>


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


#if 0
/*
 * Без оптимизации O3 данная версия работает на 0.8 секунды медленнее реализации выше.
 *
 * С оптимизацией O3 данная версия переворачивает
 * строку длиной в 1.95 гб (каждый символ 1 байт) за 0.337000 секунды,
 * что в 10 раз быстрее реализации выше без O3 (она выполняла ту же задачу за 3.1 секунды)
 * и в 4.6 раза с O3 (1.4 секунды).
 */


static inline void swap(i8 **start, i8 **end) {
  i8 tmp = **start;
  *((*start)++) = **end;
  *((*end)--) = tmp;
}


static inline SlibcWord rword(SlibcWord word) {
  i8 *start = (i8*)(&word);
  i8 *end = start + SLIBC_WORD_SIZE - 1;
  while (start < end) {
    swap(&start, &end);
  }
  return word;
}


#define diff(a, b) ((a + 1) - b)


i8 *srev(i8 * const string) {
  SlibcWord start = (SlibcWord)string;
  SlibcWord end = start + slength(string) - 1;
  while ((start % SLIBC_WORD_SIZE) && (start < end)) {
    swap((i8**)&start, (i8**)&end);
  }
  if (diff(end, start) >= (SLIBC_WORD_SIZE * 2)) {
    SlibcWord w0;
    SlibcWord w1;
    do {
      w0 = *(SlibcWord*)(start);
      w1 = *(SlibcWord*)(end - (SLIBC_WORD_SIZE - 1));

      *(SlibcWord*)(start) = rword(w1);
      *(SlibcWord*)(end - (SLIBC_WORD_SIZE - 1)) = rword(w0);

      start += SLIBC_WORD_SIZE;
      end -= SLIBC_WORD_SIZE;
    } while (diff(end, start) >= (SLIBC_WORD_SIZE * 2));
  }
  while (start < end) {
    swap((i8**)&start, (i8**)&end);
  }
  return string;
}

#endif
