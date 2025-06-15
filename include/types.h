#pragma once

#ifndef SLIBC_TYPES_H
#define SLIBC_TYPES_H


#include <common.h>


typedef void *SlibcPointer;
typedef char i8;
typedef unsigned char ui8;
typedef short int i16;
typedef unsigned short int ui16;
typedef int i32;
typedef unsigned int ui32;

#if SLIBC_ARCH_64BIT
typedef long long int i64;
typedef unsigned long long int ui64;
#endif


#define SlibcNull (SlibcPointer)0


#if defined(__STDC_VERSION__) && __STDC_VERSION__ == 202311L
  typedef bool SlibcBool;
#else
  typedef ui8 SlibcBool;
  #define true (SlibcBool)1
  #define false (SlibcBool)0
#endif


#if SLIBC_ARCH_64BIT
  typedef ui64 SlibcWord;
  #define SLIBC_WORD_SIZE 8
#else
  typedef ui32 SlibcWord;
  #define SLIBC_WORD_SIZE 4
#endif


#if defined(__SIZE_TYPE__)
  typedef __SIZE_TYPE__ SlibcSize;
#elif defined(_MSC_VER)
  #if defined(_WIN64)
    typedef ui64 SlibcSize;
  #else
    typedef ui32 SlibcSize;
  #endif
#else
  typedef ui32 SlibcSize;
#endif

#endif
