/* 
 *
 * clang tests/test_alloc.c src/mm/alloc.c src/mm/free.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude
 * clang tests/test_alloc.c src/mm/alloc.c src/mm/free.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude -m32
 * clang tests/test_alloc.c src/mm/alloc.c src/mm/free.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude -nostdlib -lkernel32.lib -lucrt.lib
 *
 */


#include <stdio.h>
#include <types.h>
#include <mm.h>


int main(void) {
  char *array = slibc_alloc(10);
  if (!array) {
    printf("array = NULL.\n");
    return 1;
  }
  array[0] = 101;
  array[1] = 99;
  array[9] = 127;
  for (slibc_size_t i = 0; i < 10; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
  printf("%d\n", slibc_free((slibc_pointer)array));
  return 0;
}


void mainCRTStartup(void) {
  main();
}
