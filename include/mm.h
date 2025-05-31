#pragma once

#ifndef SLIBC_MM_H
#define SLIBC_MM_H


#include <types.h>


#if defined(_WIN32)

#define HEAP_ZERO_MEMORY  0x00000008
#define HEAP_NO_SERIALIZE 0x00000001


extern __stdcall i32 HeapFree(slibc_pointer, ui32, slibc_pointer);
extern __stdcall slibc_pointer HeapAlloc(slibc_pointer, ui32, slibc_size_t);
extern __stdcall slibc_pointer GetProcessHeap(void);

#endif


slibc_pointer slibc_alloc(slibc_size_t size);
i32           slibc_free(slibc_pointer *p);


#endif
