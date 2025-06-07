// clang -O3 tests/test_sncopy.c src/string/sncopy.c src/string/slength.c src/mm/mset.c src/mm/mcopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <stdio.h>
#include <string.h>


int main(void) {
  char s1[10] = { [5] = 'A', [6] = 'A', [7] = 'A', [8] = 'A', [9] = '\0' };
  char *s2 = "Hello";
  sncopy(s1, s2, 5);
  printf("%s\n", s1);
  sncopy(s1, s2, 10);
  printf("%s\n", s1);
  return 0;
}
