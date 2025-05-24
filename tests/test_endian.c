/*

64-bit: clang tests/test_endian.c -Weverything -Wno-unsafe-buffer-usage
32-bit: clang tests/test_endian.c -Weverything -Wno-unsafe-buffer-usage -m32

*/

#include <stdio.h>
#include "../slibc/include/endian.h"


int main(void) {
  printf("Is little: %d\n", slibc_is_little_endian());
  printf("Is big: %d\n", slibc_is_big_endian());
  return 0;
}
