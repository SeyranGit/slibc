#include <types.h>
#include <bytes.h>
#include <string.h>


static inline i8 *write_bytes(i8 *to, SlibcWord word) {
  SlibcSize i;
  for (i = 0; i < SLIBC_WORD_SIZE; i++, to++) {
    i8 byte = (i8)extract_byte(word, i);
    if (!(*to = byte)) {
      break;
    }
  }
  return to;
}


static inline i8 *aligned_scopy(SlibcWord *to, const SlibcWord *from) {
  SlibcWord word;
  while (true) {
    word = *from++;
    if (has_null(word)) {
      break;
    }
    *to++ = word;
  }
  return write_bytes((i8*)to, word);
}


static inline i8 *unaligned_scopy(SlibcWord *to, const SlibcWord *from, SlibcSize offset) {
  SlibcWord word = *from;
  i8 i = iofzb(word);
  if ((((const i8*)from) + i) < (((const i8*)from) + offset)) {
    /*
     * We shift to the place from which we have not
     * yet started reading and write it in "to".
     * "to" will have "(SLIBC_WORD_SIZE - offset)" bytes written to it,
     * and the remaining "offset" bytes will not be written yet.
     */
    *to = shb(word, offset);
    while (true) {
      word = *(++from);
      if (has_null(word)) {
        break;
      }
      /*
       * We shift the next word by "(SLIBC_WORD_SIZE - offset)"
       * to get the first "offset" bytes and write them to "to".
       */
      *to |= shbb(word, (SLIBC_WORD_SIZE - offset));
      /*
       * We shift the word by "offset" in the opposite direction
       * in order to get the remaining part of the word and write
       * it to the beginning of the next word at the address (++to).
       */
      *(++to) = shb(word, offset);
    }
    to = (SlibcWord*)((i8*)to + (SLIBC_WORD_SIZE - offset));
  } else {
    /*
     * We leave everything that has not been read,
     * and throw away everything that has been read earlier.
     */
    word = shb(word, offset);
  }
  return write_bytes((i8*)to, word);
}


i8 *scopy(i8 *to, const i8 *from) {
  SlibcSize offset;
  for (offset = (-(SlibcWord)to) & (SLIBC_WORD_SIZE - 1);
       offset != 0;
       offset--, to++) {
    if (!(*to = *from++)) {
      return to;
    }
  }
  offset = ((SlibcWord)from) & (SLIBC_WORD_SIZE - 1);
  return (
    offset ?
    unaligned_scopy(
      (SlibcWord*)to,
      (const SlibcWord*)(from - offset),
      (offset)
    ) : aligned_scopy((SlibcWord*)to, (const SlibcWord*)from)
  );
}
