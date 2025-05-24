/*

clang tests/test.c slibc/string.c
clang tests/test.c slibc/string.c -m32

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
  printf(FORMAT, length("Hello"));
  return 0;
}
