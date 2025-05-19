#pragma once

#ifndef SLIBC_TYPES_H
#define SLIBC_TYPES_H


typedef char i8;
typedef unsigned char ui8;
typedef short int i16;
typedef unsigned short int ui16;
typedef int i32;
typedef unsigned int ui32;
typedef long long int i64;
typedef unsigned long long int ui64;


#if defined(_MSC_VER)
  #if defined(_WIN64)
    typedef ui64 Size;
  #else
    typedef ui32 Size;
  #endif
#elif defined(__SIZE_TYPE__)
  typedef __SIZE_TYPE__ Size;
#else
  typedef ui32 Size;
#endif

#endif
