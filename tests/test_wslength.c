/*
 * 64-bit: clang tests/test_wslength.c src/string/wslength.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude
 * 32-bit: clang tests/test_wslength.c src/string/wslength.c -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align -Iinclude -m32
 */

#include <stdio.h>
#include <common.h>
#include <string.h>


#if SLIBC_ARCH_64BIT
  #define FORMAT "%llu\n"
#else
  #define FORMAT "%u\n"
#endif


int main(void) {
  ui16 s[] = L"Привет, Hello!";
  printf(FORMAT, wslength(slibc_null));
  printf(FORMAT, wslength(s));
  printf(FORMAT, wslength(s + 1));
  return 0;
}
