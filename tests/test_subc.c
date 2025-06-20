// clang tests/test_subc.c src/string/subc.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude

#include <stdio.h>
#include <types.h>
#include <string.h>


i32 main(void) {
  i8 target = 'T';
  const i8 *str = "Try not. Do, or do not. There is no try.";
  const i8 *result = str;
  while ((result = subc(result, target)) != SlibcNull) {
    printf("Found '%c' starting at '%s'\n", target, result);
    ++result;
  }
}
