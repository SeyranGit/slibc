#pragma once

#ifndef SLIBC_MM_H
#define SLIBC_MM_H


#include <types.h>


slibc_pointer slibc_alloc(slibc_size_t size);
i32           slibc_free(slibc_pointer *p);


#endif
