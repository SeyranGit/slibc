// clang tests/test_srev.c src/string/slength.c src/string/srev.c src/mm/free.c src/mm/alloc.c -Iinclude -Weverything -Wno-unsafe-buffer-usage -Wno-cast-align

#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

#include <types.h>
#include <string.h>
#include <mm.h>


static i8 *sff(void) {
  struct _stat64i32 finfo;
  i8 *buffer;
  i8 *name = "a.txt";
  FILE *file;
  fopen_s(&file, name, "r");
  if (!_stat(name, &finfo) && file) {
    buffer = (i8*)slibc_alloc((SlibcSize)finfo.st_size);
    if (!buffer) {
      return SlibcNull;
    }
    fread(buffer, sizeof(i8), (SlibcSize)finfo.st_size, file);
    fclose(file);
    return buffer;
  }
  return SlibcNull;
}


i32 main(void) {
  clock_t start_time, end_time;
  i8 s1[] = "abcd";
  i8 s2[] = "abc";
  i8 s3[] = "Hello, my name is Dambul! Hello!Hello, my name is Dambul! Hello!";
  i8 s4[] = "Hello, my name is Dambul! Hello!";
  i8 s5[] = "Hello, my name is Dambul!";
  i8 s6[] = "HelloHelloHello!";
  i8 *s7;

  printf("%s\n", srev(s1));
  printf("%s\n", srev(s2));
  printf("%s\n", srev(s3));
  printf("%s\n", srev(s4));
  printf("%s\n", srev(s5));
  printf("%s\n", srev(s6));
  // printf("%s\n", srev(SlibcNull)); // TODO: fix

  s7 = sff();
  start_time = clock();
  srev(s7);
  end_time = clock();
  printf("srev execution time: %f seconds\n", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
  slibc_free((SlibcPointer)s7);
  return 0;
}
