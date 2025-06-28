#include <types.h>
#include <string.h>


ui16 *wsrev(ui16 * const string) {
  SlibcSize start = 0;
  SlibcSize end = wslength(string) - 1;
  while (start < end) {
    ui16 tmp = string[start];
    string[start++] = string[end];
    string[end--] = tmp;
  }
  return string;
}
