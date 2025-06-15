#include <bytes.h>
#include <types.h>
#include <string.h>


static inline ui16 *write_double_bytes(ui16 *to, SlibcWord word) {
  SlibcSize i;
  for (i = 0; i < (SLIBC_WORD_SIZE / 2); i++, to++) {
    ui16 double_byte = extract_short(word, i);
    if (!(*to = double_byte)) {
      break;
    }
  }
  return to;
}


static inline ui16 *aligned_wscopy(SlibcWord *to, const SlibcWord *from) {
  SlibcWord word;
  while (true) {
    word = *from++;
    if (has_double_null(word)) {
      break;
    }
    *to++ = word;
  }
  return write_double_bytes((ui16*)to, word);
}


static inline ui16 *unaligned_wscopy(SlibcWord *to, const SlibcWord *from, SlibcSize offset) {
  SlibcWord word = *from;
  i8 i = iofdzb(word);
  if ((((const ui16*)from) + i) < (((const ui16*)from) + (offset / 2))) {
    *to = shb(word, offset);
    while (true) {
      word = *(++from);
      if (has_double_null(word)) {
        break;
      }
      *to |= shbb(word, (SLIBC_WORD_SIZE - offset));
      *(++to) = shb(word, offset);
    }
    to = (SlibcWord*)((ui16*)to + ((SLIBC_WORD_SIZE - offset) / 2));
  } else {
    word = shb(word, offset);
  }
  return write_double_bytes((ui16*)to, word);
}


ui16 *wscopy(ui16 *to, const ui16 *from) {
  SlibcSize offset;
  for (offset = (-(SlibcWord)to & (SLIBC_WORD_SIZE - 1));
       offset != 0;
       offset -= 2, to++) {
    if (!(*to = *from++)) {
      return to;
    }
  }
  offset = ((SlibcWord)from) & (SLIBC_WORD_SIZE - 1);
  return (
    offset ?
    unaligned_wscopy(
      (SlibcWord*)to,
      (const SlibcWord*)(from - (offset / 2)),
      (offset)
    ) : aligned_wscopy((SlibcWord*)to, (const SlibcWord*)from)
  );
}
