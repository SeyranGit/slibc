/*
 * TODO: create your own unique exit interface for Windows and Linux to avoid using stdlib.
 */

#include <stdlib.h>


#include <types.h>
#include <stack.h>


SlibcBool slibc_is_empty_stack(Stack *stack) {
  return stack->top == (-1);
}


SlibcBool slibc_is_full_stack(Stack *stack) {
  return stack->top == (stack->size - 1);
}


SlibcBool slibc_push_stack(Stack *stack, i32 item) {
  if (slibc_is_full_stack(stack)) {
    return false;
  }
  stack->array[++(stack->top)] = item;
  return true;
}


i32 slibc_pop_stack(Stack *stack) {
  if (slibc_is_empty_stack(stack)) {
    exit(EXIT_FAILURE);
  }
  return stack->array[(stack->top)--];
}


Stack slibc_new_stack(void) {
  Stack stack;
  stack.size = 0;
  stack.top = -1;
  stack.array = SlibcNull;
  return stack;
}
