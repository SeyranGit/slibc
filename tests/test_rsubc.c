// clang tests/test_rsubc.c src/string/rsubc.c src/string/subc.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Wno-cast-qual -Iinclude

#include <stdio.h>
#include <types.h>
#include <string.h>


i32 main(void) {
  const i8 *name = "gugo";
  printf("%s\n", rsubc(name, 'g'));
  return 0;
}
