// clang tests/test_sncat.c src/string/sncat.c src/string/slength.c src/mm/mcpy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <stdio.h>
#include <string.h>
#include <types.h>


static void t1(void) {
  i8 s1[15] = "Hello,";
  i8 *s2 = " world!";
  printf("%s\n", sncat(s1, s2, 6));
}


static void t2(void) {
  i8 s1[15] = "Hello,";
  i8 *s2 = " world!";
  printf("%s\n", sncat(s1, s2, 10));
}


static void t3(void) {
  i8 s1[15] = "Hello,";
  i8 *s2 = " world!";
  printf("%s\n", sncat(s1, s2, 0));
}


int main(void) {
  t1();
  t2();
  t3();
}
