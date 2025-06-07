// clang tests/test_mset.c src/mm/mset.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <stdio.h>
#include <types.h>
#include <mm.h>


#define SIZE 53


int main(void) {
  i8 array[SIZE + 50] = {0};
  mset((slibc_pointer)array, 0xFFFF, SIZE);
  for (slibc_size_t i = 0; i < SIZE + 50; i++) {
    printf("%llu: %x\n", i + 1, (ui32)array[i]);
  }
  return 0;
}
