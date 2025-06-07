// clang tests/test_mcopy.c src/mm/mcopy.c src/mm/mset.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <types.h>
#include <stdio.h>
#include <mm.h>


static void t1(void) {
  i8 a[100];
  i8 *s = "Hello, my name is Seyran and to day i love your and but not";
  mcopy(a, s, 60);
  printf("%s\n", a);
}


static void t2(void) {
  i8 a[100];
  i8 s[] = "Hello, my name is Seyran and to day i love your and but not";
  mcopy(a + 1, s, 60);
  printf("%s\n", a + 1);
}


static void t4(void) {
  i8 a[100] = {0};
  i8 s[] = "Hello, my name is Seyran and to day i love your and but not";
  for (slibc_size_t i = 0; i < 60; i++) {
    mcopy(a + 1, s + i, 60 - i);
    printf("%s\n", a + 1);
    mset(a, 0, 100);
  }
}


i32 main(void) {
  t1();
  t2();
  t4();
  return 0;
}
