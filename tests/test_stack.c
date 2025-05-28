#include <stdio.h>
#include <stack.h>


#define ARRAY_SIZE 3


int main(void) {
  i32 array[ARRAY_SIZE];

  Stack stack = slibc_new_stack();
  stack.array = array;
  stack.size = ARRAY_SIZE;

  slibc_push_stack(&stack, 10);
  slibc_push_stack(&stack, 20);
  slibc_push_stack(&stack, 30);

  printf("%d\n", slibc_pop_stack(&stack));
  printf("%d\n", slibc_pop_stack(&stack));
  printf("%d\n", slibc_pop_stack(&stack));
  return 0;
}
