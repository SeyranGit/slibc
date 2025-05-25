/*

64-bit: clang tests/test_str_copy.c slibc/string.c -Weverything -Wno-unsafe-buffer-usage
32-bit: clang tests/test_str_copy.c slibc/string.c -Weverything -Wno-unsafe-buffer-usage -m32

*/

#include <stdio.h>
#include "../slibc/include/string.h"


int main(void) {
  char s1[26];
  char s2[] = "Hello, my name is Seyran!";
  str_copy(s1, s2);
  printf("%s\n", s1);
  return 0;
}
