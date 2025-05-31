#pragma once

#ifndef SLIBC_MM_H
#define SLIBC_MM_H


#include <types.h>


#if defined(_WIN32)

#ifdef _WIN64
  #define SLIBC_WINAPI
#else
  #define SLIBC_WINAPI __stdcall
#endif

#define HEAP_ZERO_MEMORY  0x00000008
#define HEAP_NO_SERIALIZE 0x00000001


extern SLIBC_WINAPI i32 HeapFree(slibc_pointer, ui32, slibc_pointer);
extern SLIBC_WINAPI slibc_pointer HeapAlloc(slibc_pointer, ui32, slibc_size_t);
extern SLIBC_WINAPI slibc_pointer GetProcessHeap(void);

#endif


slibc_pointer slibc_alloc(slibc_size_t size);
i32           slibc_free(slibc_pointer *p);


#endif
