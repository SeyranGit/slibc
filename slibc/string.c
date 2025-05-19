#include "include/string.h"
#include "include/types.h"


Size length(const char *string) {
  Size len = 0;
  while (string[len++] != '\0');
  return len - 1;
}
