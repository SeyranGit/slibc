#include <types.h>
#include <string.h>


ui16 *wrsubc(const ui16 *string, ui16 symbol) {
  const ui16 *found = SlibcNull;
  const ui16 *p;
  while ((p = wsubc(string, symbol)) != SlibcNull) {
    found = p;
    string = p + 1;
  }
  return (ui16*)found;
}
