#pragma once

#ifndef SLIBC_STACK_H
#define SLIBC_STACK_H


#include <types.h>


typedef struct {
  SlibcSize size;

  /* TODO: Will not work stably on 32-bit system. You can create MaxIntTyp */
  i64 top;

  i32 *array;
} Stack;


SlibcBool slibc_is_empty_stack(Stack *stack);
SlibcBool slibc_is_full_stack(Stack *stack);
SlibcBool slibc_push_stack(Stack *stack, i32 item);
i32       slibc_pop_stack(Stack *stack);
Stack     slibc_new_stack(void);


#endif
