#include <types.h>
#include <mm.h>


#if defined(_WIN32)


#include <Windows.h>


slibc_pointer slibc_alloc(slibc_size_t size) {
  HANDLE process_heap = GetProcessHeap();
  if (process_heap) {
    return HeapAlloc(process_heap, HEAP_ZERO_MEMORY, size);
  }
  return slibc_null;
}


#elif defined(linux) && linux == 1


slibc_pointer slibc_alloc(slibc_size_t size) {
  return slibc_null;
}

#else


slibc_pointer slibc_alloc(slibc_size_t size) {
  return slibc_null;
}


#endif
