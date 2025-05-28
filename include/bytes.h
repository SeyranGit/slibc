#pragma once

#ifndef SLIBC_BYTES_H
#define SLIBC_BYTES_H


#include <common.h>
#include <types.h>


#if SLIBC_ARCH_64BIT
  #define H_MASK (slibc_word_t)0x8080808080808080
  #define L_MASK (slibc_word_t)0x0101010101010101
#else
  #define H_MASK (slibc_word_t)0x80808080
  #define L_MASK (slibc_word_t)0x01010101
#endif


#define has_zero(word) (((word - L_MASK) & ~word & H_MASK) != 0)
#define extract_byte(word, i) ((const i8*)&word)[i]


static inline i8 get_zero_index(slibc_word_t word) {
  slibc_size_t i;
  for (i = 0; i < SLIBC_WORD_SIZE; i++) {
    if (!extract_byte(word, i)) {
      return (i8)i;
    }
  }
  return -1;
}


#endif
