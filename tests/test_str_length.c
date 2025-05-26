/*

64-bit: clang tests/test_str_length.c slibc/string.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align
32-bit: clang tests/test_str_length.c slibc/string.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -m32

*/

#include <stdio.h>
#include "../slibc/include/common.h"
#include "../slibc/include/string.h"


#if SLIBC_ARCH_64BIT
  #define FORMAT "%llu\n"
#else
  #define FORMAT "%u\n"
#endif


int main(void) {
  char s[] = "Hello!";
  printf(FORMAT, str_length(slibc_null));
  printf(FORMAT, str_length(s + 1));
  return 0;
}
