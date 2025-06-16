#include <common.h>
#include <types.h>
#include <mm.h>
#include <bytes.h>


static inline SlibcWord aligned_mcmp(SlibcWord mp1, SlibcWord mp2, SlibcSize length) {
  SlibcWord w1;
  SlibcWord w2;
  SlibcWord result;
  while (length-- != 0) {
    w1 = *(SlibcWord*)mp1;
    w2 = *(SlibcWord*)mp2;
    result = w1 - w2;
    if (result) {
      return result;
    }
    mp1 += SLIBC_WORD_SIZE;
    mp2 += SLIBC_WORD_SIZE;
  }
  return 0;
}


static inline SlibcWord unaligned_mcmp(SlibcWord mp1, SlibcWord mp2, SlibcSize length) {
  SlibcWord w0;
  SlibcWord w1;
  SlibcWord tmp0;
  SlibcWord tmp1;
  SlibcWord result;

  i8 sh1 = mp2 % SLIBC_WORD_SIZE;
  i8 sh2 = SLIBC_WORD_SIZE - sh1;

  while (length-- != 0) {
    tmp0 = *(SlibcWord*)(mp2 - sh1);
    tmp1 = *(SlibcWord*)(mp2 + sh2);
    w0 = *(SlibcWord*)(mp1);
    w1 = shb(tmp0, sh1) | shbb(tmp1, sh2);
    for (SlibcSize i = 0; i < SLIBC_WORD_SIZE; i++) {
      result = ((ui8*)(&w0))[i] - ((ui8*)(&w1))[i];
      if (result) {
        return result;
      }
    }
    mp1 += SLIBC_WORD_SIZE;
    mp2 += SLIBC_WORD_SIZE;
  }
  return 0;
}


static inline SlibcWord cmp(SlibcWord *cmp1p, SlibcWord *cmp2p) {
  i8 b1 = *(i8*)(*cmp1p)++;
  i8 b2 = *(i8*)(*cmp2p)++;
  return b1 - b2;
}


#if SLIBC_ARCH_64BIT
i64
#else
i32
#endif
mcmp(SlibcConstPointer mp1, SlibcConstPointer mp2, SlibcSize length) {
  SlibcWord cmp1 = (SlibcWord)mp1;
  SlibcWord cmp2 = (SlibcWord)mp2;
  SlibcWord result;
  if (length >= 16) {
    while (cmp1 % SLIBC_WORD_SIZE != 0) {
      result = cmp(&cmp1, &cmp2);
      if (result) {
        return result;
      }
      length--;
    }
    if (cmp2 % SLIBC_WORD_SIZE == 0)
      result = aligned_mcmp(cmp1, cmp2, length / SLIBC_WORD_SIZE);
    else
      result = unaligned_mcmp(cmp1, cmp2, length / SLIBC_WORD_SIZE);

    if (result) return result;
    cmp1 += length - (length % SLIBC_WORD_SIZE);
    cmp2 += length - (length % SLIBC_WORD_SIZE);
    length %= SLIBC_WORD_SIZE;
  }
  while (length-- != 0) {
    result = cmp(&cmp1, &cmp2);
    if (result) {
      return result;
    }
  }
  return 0;
}
