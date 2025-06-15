#include <types.h>
#include <stdio.h>
#include <stack.h>
#include <mm.h>


#define SIZE 3


int main(void) {
  Stack stack = slibc_new_stack();
  stack.array = slibc_alloc(SIZE);
  stack.size = SIZE;

  slibc_push_stack(&stack, 10);
  slibc_push_stack(&stack, 20);
  slibc_push_stack(&stack, 30);

  printf("%d\n", slibc_pop_stack(&stack));
  printf("%d\n", slibc_pop_stack(&stack));
  printf("%d\n", slibc_pop_stack(&stack));

  slibc_free((SlibcPointer)stack.array);
  return 0;
}
