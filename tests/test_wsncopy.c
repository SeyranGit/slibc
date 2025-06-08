// clang -O3 tests/test_wsncopy.c src/string/wsncopy.c src/string/wslength.c src/mm/mset.c src/mm/mcopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <types.h>
#include <stdio.h>
#include <string.h>


int main(void) {
  ui16 s1[10] = { [5] = 'A', [6] = 'B', [7] = 'C', [8] = 'D', [9] = '\0' };
  ui16 *s2 = L"Hello";
  wsncopy(s1, s2, 5);
  printf("%ls\n", s1);
  wsncopy(s1, s2, 10);
  printf("%ls\n", s1);
  return 0;
}
