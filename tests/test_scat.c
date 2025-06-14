// clang tests/test_scat.c src/string/scat.c src/string/slength.c src/string/scopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <stdio.h>
#include <string.h>
#include <types.h>


int main(void) {
  i8 s1[15] = "Hello,";
  i8 *s2 = " world!";
  printf("%s\n", scat(s1, s2));
}
