// clang tests/test_mcmp.c src/mm/mcmp.c -Iinclude -Weverything

#include <stdio.h>
#include <mm.h>


static void t1(void) {
  i8 *s1 = "hello";
  i8 *s2 = "hello";
  printf("Result: %d\n", mcmp(s1, s2, 5));
}


static void t2(void) {
  i8 *s1 = "hello";
  i8 *s2 = "hellL";
  printf("Result: %d\n", mcmp(s1, s2, 5));
}


static void t3(void) {
  struct S { int a; };
  struct S s1 = { .a = 10 };
  struct S s2 = { .a = 10 };
  printf("Result: %d\n", mcmp(&s1, &s2, sizeof(struct S)));
  s2.a = 15;
  printf("Result: %d\n", mcmp(&s1, &s2, sizeof(struct S)));
}


int main(void) {
  t1();
  t2();
  t3();
  return 0;
}
