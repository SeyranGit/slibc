/*

64-bit: clang tests/test_slength.c src/string/slength.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude
32-bit: clang tests/test_slength.c slibc/slength.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude -m32

*/

#include <stdio.h>
#include <common.h>
#include <string.h>


#if SLIBC_ARCH_64BIT
  #define FORMAT "%llu\n"
#else
  #define FORMAT "%u\n"
#endif


int main(void) {
  char s[] = "Hello!";
  printf(FORMAT, slength(slibc_null));
  printf(FORMAT, slength(s + 1));
  return 0;
}
