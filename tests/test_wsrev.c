// clang tests/test_wsrev.c src/string/wslength.c src/string/wsrev.c -Iinclude -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align

#include <stdio.h>
#include <types.h>
#include <string.h>


i32 main(void) {
  ui16 s1[] = L"abcd";
  ui16 s2[] = L"abc";
  printf("%ls\n", wsrev(s1));
  printf("%ls\n", wsrev(s2));
  return 0;
}
