// clang tests/test_wsncat.c src/string/wsncat.c src/string/wslength.c src/mm/mcpy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <stdio.h>
#include <string.h>
#include <types.h>


static void t1(void) {
  ui16 s1[15] = L"Hello,";
  ui16 *s2 = L" world!";
  printf("%ls\n", wsncat(s1, s2, 6));
}


static void t2(void) {
  ui16 s1[15] = L"Hello,";
  ui16 *s2 = L" world!";
  printf("%ls\n", wsncat(s1, s2, 10));
}


static void t3(void) {
  ui16 s1[15] = L"Hello,";
  ui16 *s2 = L" world!";
  printf("%ls\n", wsncat(s1, s2, 0));
}


int main(void) {
  t1();
  t2();
  t3();
}
