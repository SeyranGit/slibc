// clang tests/test_wscat.c src/string/wscat.c src/string/wslength.c src/string/wscopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <stdio.h>
#include <string.h>
#include <types.h>


int main(void) {
  ui16 s1[15] = L"Hello,";
  ui16 *s2 = L" world!";
  printf("%ls\n", wscat(s1, s2));
}
