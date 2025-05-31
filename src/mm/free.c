#include <types.h>
#include <mm.h>


#if defined(_WIN32)


#include <Windows.h>


i32 slibc_free(slibc_pointer *p) {
  HANDLE process_heap = GetProcessHeap();
  if (process_heap) {
    return HeapFree(process_heap, HEAP_NO_SERIALIZE, p);
  }
  return 0;
}


#elif defined(linux) && linux == 1


#include <sys/mman.h>


i32 slibc_free(slibc_pointer *p) {
  return slibc_null;
}


#else


slibc_pointer slibc_alloc(slibc_size_t size) {
  return slibc_null;
}


#endif
