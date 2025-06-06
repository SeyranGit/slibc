#include <stdio.h>
#include <types.h>
#include <mm.h>


#define SIZE 111


int main(void) {
  i32 array[SIZE];
  mset((slibc_pointer)array, 0xFF, 4 * SIZE);
  for (slibc_size_t i = 0; i < SIZE; i++) {
    printf("%llu: %x\n", i + 1, array[i]);
  }
  return 0;
}
