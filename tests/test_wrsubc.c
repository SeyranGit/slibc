// clang tests/test_wrsubc.c src/string/wrsubc.c src/string/wsubc.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Wno-cast-qual -Iinclude

#include <stdio.h>
#include <types.h>
#include <string.h>


i32 main(void) {
  const ui16 *name = L"gugo";
  printf("%ls\n", wrsubc(name, 'g'));
  return 0;
}
