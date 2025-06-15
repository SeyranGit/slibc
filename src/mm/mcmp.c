#include <types.h>
#include <mm.h>


i32 mcmp(SlibcPointer mp1, SlibcPointer mp2, SlibcSize length) {  
  SlibcWord cmp1 = (SlibcWord)mp1;
  SlibcWord cmp2 = (SlibcWord)mp2;
  i8 result;
  i8 b1;
  i8 b2;
  while (length-- != 0) {
    b1 = *(i8*)cmp1++;
    b2 = *(i8*)cmp2++;
    result = b1 - b2;
    if (result) {
      return result;
    }
  }
  return 0;
}
