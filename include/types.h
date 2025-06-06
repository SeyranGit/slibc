#pragma once

#ifndef SLIBC_TYPES_H
#define SLIBC_TYPES_H


#include <common.h>


typedef char i8;
typedef unsigned char ui8;
typedef short int i16;
typedef unsigned short int ui16;
typedef int i32;
typedef unsigned int ui32;
typedef long long int i64;
typedef unsigned long long int ui64;


typedef void *slibc_pointer;


#define slibc_null (slibc_pointer)0


#if defined(__STDC_VERSION__) && __STDC_VERSION__ == 202311L
  typedef bool slibc_bool;
#else
  typedef ui8 slibc_bool;
  #define true (slibc_bool)1
  #define false (slibc_bool)0
#endif


#if SLIBC_ARCH_64BIT
  typedef ui64 slibc_word_t;
  #define SLIBC_WORD_SIZE 8
#else
  typedef ui32 slibc_word_t;
  #define SLIBC_WORD_SIZE 4
#endif


#if defined(__SIZE_TYPE__)
  typedef __SIZE_TYPE__ slibc_size_t;
#elif defined(_MSC_VER)
  #if defined(_WIN64)
    typedef ui64 slibc_size_t;
  #else
    typedef ui32 slibc_size_t;
  #endif
#else
  typedef ui32 slibc_size_t;
#endif

#endif
