#pragma once

#ifndef SLIBC_STRING_H
#define SLIBC_STRING_H

#include <types.h>


slibc_size_t slength(const i8 * const string);
slibc_size_t wslength(const ui16 * const string);

i8 *scopy(i8* to, const i8* from);


#endif
