#pragma once

#ifndef SLIBC_MM_H
#define SLIBC_MM_H


#include <common.h>
#include <types.h>


#if defined(_WIN32)

#ifdef _WIN64
  #define SLIBC_WINAPI
#else
  #define SLIBC_WINAPI __stdcall
#endif


#define HEAP_ZERO_MEMORY  0x00000008
#define HEAP_NO_SERIALIZE 0x00000001


extern SLIBC_WINAPI i32 HeapFree(SlibcPointer, ui32, SlibcPointer);
extern SLIBC_WINAPI SlibcPointer HeapAlloc(SlibcPointer, ui32, SlibcSize);
extern SLIBC_WINAPI SlibcPointer GetProcessHeap(void);

#endif


#define SUCCESSFULLY (i8)0


SlibcPointer slibc_alloc(SlibcSize size);
i32          slibc_free(SlibcPointer *p);


void mset(i8 *m, i32 c, SlibcSize size);
void mcpy(i8 *to, const i8 *from, SlibcSize size);


#if SLIBC_ARCH_64BIT
i64
#else
i32
#endif
mcmp(SlibcConstPointer mp1, SlibcConstPointer mp2, SlibcSize length);


#endif
