/*
 *
 * 64-bit: clang tests/test_wscopy.c src/string/wscopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude
 * 32-bit: clang tests/test_wscopy.c src/string/wscopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude -m32
 *
 */

#include <stdio.h>
#include <types.h>
#include <string.h>


static void t1(void) {
  ui16 s1[10];
  ui16 s2[] = L"Hello";
  wscopy(s1, s2);
  printf("%ls\n", s1);
}


static void t2(void) {
  ui16 s1[6];
  wscopy(s1, L"Hello");
  printf("%ls\n", s1);
}


static void t3(void) {
  ui16 *s2 = L"Hello, my name is Seyran!";
  ui16 s1[26] = {[0] = 'A'};
  wscopy(s1 + 1, s2 + 5);
  printf("%ls\n", s1);
}


int main(void) {
  t1();
  t2();
  t3();
  t3();
  t2();
  t1();
  return 0;
}
