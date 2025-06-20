// clang tests/test_wsubc.c src/string/wsubc.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Wno-cast-qual -Iinclude

#include <stdio.h>
#include <types.h>
#include <string.h>


i32 main(void) {
  ui16 target = L'T';
  const ui16 *str = L"Try not. Do, or do not. There is no try.";
  const ui16 *result = str;
  while ((result = wsubc(result, target)) != SlibcNull) {
    printf("Found '%lc' starting at '%ls'\n", target, result);
    ++result;
  }
}
