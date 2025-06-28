// clang tests/test_srev.c src/string/slength.c src/string/srev.c -Iinclude -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align

#include <stdio.h>
#include <types.h>
#include <string.h>


i32 main(void) {
  i8 s1[] = "abcd";
  i8 s2[] = "abc";
  printf("%s\n", srev(s1));
  printf("%s\n", srev(s2));
  return 0;
}
