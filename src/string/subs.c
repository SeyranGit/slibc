#include <types.h>
#include <mm.h>
#include <string.h>


i8 *subs(const i8 *string, const i8 *sub) {
  SlibcSize string_len;
  SlibcSize sub_len;
  if (sub[0] == 0) {
    return (i8*)string;
  }
  string = subc(string, sub[0]);
  if (string == SlibcNull || sub[1] == 0) {
    return (i8*)string;
  }
  string_len = slength(string);
  sub_len = slength(sub);
  if (string_len < sub_len) {
    return SlibcNull;
  }
  if (!mcmp(string, sub, sub_len)) {
    return (i8*)string;
  }
  while ((string = subc(++string, sub[0]))) {
    if (!mcmp(string, sub, sub_len)) {
      return (i8*)string;
    }
  }
  return SlibcNull;
}
