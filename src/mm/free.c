#include <types.h>
#include <mm.h>


#if defined(_WIN32)


i32 slibc_free(SlibcPointer *p) {
  SlibcPointer process_heap = GetProcessHeap();
  if (process_heap) {
    return HeapFree(process_heap, HEAP_NO_SERIALIZE, p);
  }
  return 0;
}


#elif defined(linux) && linux == 1


#include <sys/mman.h>


i32 slibc_free(SlibcPointer *p) {
  return 0;
}


#else


i32 slibc_free(SlibcPointer *p) {
  return 0;
}


#endif
