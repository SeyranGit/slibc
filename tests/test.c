/*

clang tests/test.c slibc/string.c

*/

#include "../slibc/include/string.h"


extern int printf(char const* const _Format, ...);


int main(void) {
  printf("%llu\n", length("Hello"));
  return 0;
}
