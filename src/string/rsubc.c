#include <types.h>
#include <string.h>


i8 *rsubc(const i8 *string, i8 symbol) {
  const i8 *found = SlibcNull;
  const i8 *p;
  while ((p = subc(string, symbol)) != SlibcNull) {
    found = p;
    string = p + 1;
  }
  return (i8*)found;
}
