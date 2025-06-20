#include <types.h>
#include <string.h>


i8 *subc(const i8 *string, i8 c) {
  while (*string) {
    if (*string++ == c) {
      return (i8*)(string - 1);
    }
  }
  return SlibcNull;
}
