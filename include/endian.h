#pragma once

#ifndef SLIBC_ENDIAN_H
#define SLIBC_ENDIAN_H

#include <types.h>


static inline ui8 slibc_is_little_endian(void) {
  const ui16 one = 0x0001;
  return *(const ui8*)&one;
}


static inline ui8 slibc_is_big_endian(void) {
  return !slibc_is_little_endian();
}


#endif
