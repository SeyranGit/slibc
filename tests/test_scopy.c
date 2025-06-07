/*
 *
 * 64-bit: gcc   tests/test_scopy.c src/string/scopy.c -Wall -Iinclude
 * 64-bit: clang tests/test_scopy.c src/string/scopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude
 * 32-bit: clang tests/test_scopy.c src/string/scopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude -m32
 *
 */

#include <types.h>
#include <stdio.h>
#include <string.h>


static void t1(void) {
  char s1[10];
  char s2[] = "Hello";
  scopy(s1, s2);
  printf("%s\n", s1);
}


static void t2(void) {
  char s1[6];
  scopy(s1, "Hello");
  printf("%s\n", s1);
}


static void t3(void) {
  char *s2 = "Hello, my name is Seyran!";
  char s1[26] = {[0] = 'A'};
  scopy(s1 + 1, s2 + 5);
  printf("%s\n", s1);
}


static void t4(void) {
  char *s2 = "Hello, my name is Seyran!";
  char s1[26]; // = {[0] = 'A'};
  for (slibc_size_t i = 0; i < 26; i++) {
    scopy(s1, s2 + i);
    printf("%s\n", s1);
  }
}


int main(void) {
  t1();
  t2();
  t3();
  t3();
  t2();
  t1();
  t4();
  return 0;
}


/*
void mainCRTStartup(void) {
  // clang tests/test_scopy.c src/string/scopy.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude -nostdlib -lucrt.lib
  main();
}
*/
