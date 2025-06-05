#pragma once

#ifndef SLIBC_BYTES_H
#define SLIBC_BYTES_H


#include <common.h>
#include <types.h>


#if SLIBC_ARCH_64BIT
  #define HMASK  (slibc_word_t)0x8080808080808080
  #define LMASK  (slibc_word_t)0x0101010101010101
  #define WHMASK (slibc_word_t)0x8000800080008000
  #define WLMASK (slibc_word_t)0x0001000100010001
#else
  #define HMASK  (slibc_word_t)0x80808080
  #define LMASK  (slibc_word_t)0x01010101
  #define WHMASK (slibc_word_t)0x80008000
  #define WLMASK (slibc_word_t)0x00010001
#endif


#define has_null(word)         (((word - LMASK) & ~word & HMASK) != 0)
#define has_double_null(word)  (((word - WLMASK) & ~word & WHMASK) != 0)
#define extract_byte(word, i)  ((const i8*)&word)[i]
#define extract_short(word, i) ((const i16*)&word)[i]


#define eloop(word, word_size, extractor) for (slibc_size_t i = 0; i < word_size; i++) { if (!extractor(word, i)) return (i8)i; } return -1


/* index of the first zero byte */
static inline i8 iofzb(slibc_word_t word) {
  eloop(word, SLIBC_WORD_SIZE, extract_byte);
}


/* index of the first double zero byte */
static inline i8 iofdzb(slibc_word_t word) {
  eloop(word, SLIBC_WORD_SIZE / 2, extract_short);
}

#endif
