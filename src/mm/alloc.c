#include <types.h>
#include <mm.h>


#if defined(_WIN32)


SlibcPointer slibc_alloc(SlibcSize size) {
  SlibcPointer process_heap;
  if (size) {
    process_heap = GetProcessHeap();
    if (process_heap) {
      return HeapAlloc(process_heap, HEAP_ZERO_MEMORY, size);
    }
  }
  return SlibcNull;
}


#elif defined(linux) && linux == 1


#include <sys/mman.h>


SlibcPointer slibc_alloc(SlibcSize size) {
  SlibcPointer m = mmap(SlibcNull, size, (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
  if (m) {
    return m;
  }
  return SlibcNull;
}


#else


SlibcPointer slibc_alloc(SlibcSize size) {
  return SlibcNull;
}


#endif
