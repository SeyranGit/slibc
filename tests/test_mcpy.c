// clang tests/test_mcpy.c src/mm/mcpy.c src/mm/mset.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <types.h>
#include <stdio.h>
#include <mm.h>


#define STR_SIZE 56


static void t1(void) {
  i8 a[100];
  i8 *s = "Hello, world! Hello, world! Hello, world! Hello, world!";
  mcpy(a, s, STR_SIZE);
  printf("%s\n", a);
}


static void t2(void) {
  i8 a[100];
  i8 s[] = "Hello, world! Hello, world! Hello, world! Hello, world!";
  mcpy(a + 1, s, STR_SIZE);
  printf("%s\n", a + 1);
}


static void t3(void) {
  i8 a[100] = {0};
  i8 s[] = "Hello, world! Hello, world! Hello, world! Hello, world!";
  for (SlibcSize i = 0; i < STR_SIZE; i++) {
    mcpy(a + 1, s + i, STR_SIZE - i);
    printf("%s\n", a + 1);
    mset(a, 0, 100);
  }
}


i32 main(void) {
  t1();
  t2();
  t3();
  return 0;
}
