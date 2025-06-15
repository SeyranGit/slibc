#pragma once

#ifndef SLIBC_BYTES_H
#define SLIBC_BYTES_H


#include <common.h>
#include <types.h>


#if SLIBC_ARCH_64BIT
  #define HMASK  (SlibcWord)0x8080808080808080
  #define LMASK  (SlibcWord)0x0101010101010101
  #define WHMASK (SlibcWord)0x8000800080008000
  #define WLMASK (SlibcWord)0x0001000100010001
#else
  #define HMASK  (SlibcWord)0x80808080
  #define LMASK  (SlibcWord)0x01010101
  #define WHMASK (SlibcWord)0x80008000
  #define WLMASK (SlibcWord)0x00010001
#endif


/*
 * bit shift and bit shift back depending on byte order of the system (little-endian/big-endian)
 */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  #define shb(word, nbytes) (word >> (nbytes * 8))
  #define shbb(word, nbytes) (word << (nbytes * 8))
#else
  #define shb(word, nbytes) (word << (nbytes * 8))
  #define shbb(word, nbytes) (word >> (nbytes * 8))
#endif


#define has_null(word)         (((word - LMASK) & ~word & HMASK) != 0)
#define has_double_null(word)  (((word - WLMASK) & ~word & WHMASK) != 0)
#define extract_byte(word, i)  ((const ui8*)&word)[i]
#define extract_short(word, i) ((const ui16*)&word)[i]


#define eloop(word, word_size, extractor) for (SlibcSize i = 0; i < word_size; i++) { if (!extractor(word, i)) return (i8)i; } return -1


/* index of the first null byte */
static inline i8 iofzb(SlibcWord word) {
  eloop(word, SLIBC_WORD_SIZE, extract_byte);
}


/* index of the first double null byte */
static inline i8 iofdzb(SlibcWord word) {
  eloop(word, SLIBC_WORD_SIZE / 2, extract_short);
}


#endif
