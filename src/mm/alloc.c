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


#include <sys/mman.h>


slibc_pointer slibc_alloc(slibc_size_t size) {
  slibc_pointer m = mmap(
    slibc_null,
    size,
    (PROT_READ | PROT_WRITE), 
    (MAP_PRIVATE | MAP_ANONYMOUS), 
    -1, 0
  );
  if (m) {
    return m;
  }
  return slibc_null;
}


#else


slibc_pointer slibc_alloc(slibc_size_t size) {
  return slibc_null;
}


#endif
