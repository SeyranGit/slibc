// clang tests/test_mcmp.c src/string/slength.c src/mm/mcmp.c -Iinclude -Weverything -Wno-unsafe-buffer-usage -Wno-sign-conversion -Wno-cast-align

#include <stdio.h>
#include <mm.h>
#include <string.h>


#if SLIBC_ARCH_64BIT
  #define FORMAT "Result: %lld\n"
#else
  #define FORMAT "Result: %u\n"
#endif


static void t1(void) {
  i8 *s1 = "hello";
  i8 *s2 = "hello";
  printf(FORMAT, mcmp(s1, s2, 5));
}


static void t2(void) {
  i8 *s1 = "hello";
  i8 *s2 = "hellL";
  printf(FORMAT, mcmp(s1, s2, 5));
}


static void t3(void) {
  struct S { int a; };
  struct S s1 = { .a = 10 };
  struct S s2 = { .a = 10 };
  printf(FORMAT, mcmp(&s1, &s2, sizeof(struct S)));
  s2.a = 15;
  printf(FORMAT, mcmp(&s1, &s2, sizeof(struct S)));
}


static void t4(void) {
  i8 *s1 = "Hello, my name is Seyran!";
  i8 *s2 = "Hello, my name is Seyran!";
  printf(FORMAT, mcmp(s1, s2, slength(s1)));
  printf(FORMAT, mcmp(s1, s2 + 1, slength(s1) - 1));
}


int main(void) {
  t1();
  t2();
  t3();
  t4();
  return 0;
}
