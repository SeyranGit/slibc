#include <types.h>
#include <string.h>


i8 *srev(i8 * const string) {
  SlibcSize start = 0;
  SlibcSize end = slength(string) - 1;
  while (start < end) {
    i8 tmp = string[start];
    string[start++] = string[end];
    string[end--] = tmp;
  }
  return string;
}
