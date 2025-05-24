#pragma once

#ifndef SLIBC_TYPES_H
#define SLIBC_TYPES_H


#include "common.h"


#define slibc_null (void*)0


typedef char i8;
typedef unsigned char ui8;
typedef short int i16;
typedef unsigned short int ui16;
typedef int i32;
typedef unsigned int ui32;
typedef long long int i64;
typedef unsigned long long int ui64;


#if SLIBC_ARCH_64BIT
  typedef ui64 slibc_word_t;
  #define SLIBC_WORD_SIZE 8
#else
  typedef ui32 slibc_word_t;
  #define SLIBC_WORD_SIZE 4
#endif


#if defined(_MSC_VER)
  #if defined(_WIN64)
    typedef ui64 slibc_size_t;
  #else
    typedef ui32 slibc_size_t;
  #endif
#elif defined(__SIZE_TYPE__)
  typedef __SIZE_TYPE__ slibc_size_t;
#else
  typedef ui32 slibc_size_t;
#endif

#endif
