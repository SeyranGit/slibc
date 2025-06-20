#include <types.h>
#include <string.h>


i8 *rsubc(const i8 *string, i8 symbol) {
  const i8 *found = SlibcNull;
  const i8 *next;
  while ((next = subc(string, symbol)) != SlibcNull) {
    found = next;
    string = next + 1;
  }
  return (i8*)found;
}
