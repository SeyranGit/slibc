// clang tests/test_subs.c src/string/subs.c src/string/subc.c src/string/slength.c src/string/sncopy.c src/mm/mcmp.c src/mm/mset.c src/mm/mcopy.c src/mm/alloc.c src/mm/free.c -Iinclude -Weverything -Wno-cast-qual -Wno-unsafe-buffer-usage -Wno-cast-align -Wno-sign-conversion

#include <stdio.h>
#include <types.h>
#include <string.h>
#include <mm.h>


static void nprintf(const i8 *format, const i8 *string, SlibcSize n) {
  i8 *to = slibc_alloc(n + 1);
  to[n + 1] = 0;
  sncopy(to, string, n);
  printf(format, to);
  slibc_free((SlibcPointer)to);
}


static inline i8 *get_target(i32 argc, i8 **argv) {
  if (argc > 1) {
    return argv[1];
  }
  return SlibcNull;
}


i32 main(i32 argc, i8 **argv) {
  i8 *target = get_target(argc, argv);
  if (target) {
    i8 *result = subs("Hello, my name is Bob!", target);
    if (result) {
      nprintf("Found: %s\n", result, slength(target));
    }
    printf("Result: %p\n", result);
  }
  return 0;
}
