#pragma once

#ifndef SLIBC_COMMON_H
#define SLIBC_COMMON_H


#if defined(__x86_64__) || defined(_M_X64) || defined(__LP64__)
  #define SLIBC_ARCH_64BIT 1
#else
  #define SLIBC_ARCH_64BIT 0
#endif


#endif
