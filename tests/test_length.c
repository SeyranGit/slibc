/*

64-bit: clang tests/test_length.c slibc/string.c -Weverything -Wno-unsafe-buffer-usage
32-bit: clang tests/test_length.c slibc/string.c -Weverything -Wno-unsafe-buffer-usage -m32

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
  printf(FORMAT, length(slibc_null));
  printf(FORMAT, length("Hello"));
  return 0;
}
