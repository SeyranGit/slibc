/*

64-bit: clang tests/test_endian.c -Weverything -Wno-unsafe-buffer-usage -Iinclude
32-bit: clang tests/test_endian.c -Weverything -Wno-unsafe-buffer-usage -Iinclude -m32

*/

#include <stdio.h>
#include <endian.h>


int main(void) {
  printf("Is little: %d\n", slibc_is_le());
  printf("Is big: %d\n", slibc_is_be());
  return 0;
}
