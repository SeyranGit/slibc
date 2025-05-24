#pragma once

#ifndef SLIBC_STRING_H
#define SLIBC_STRING_H

#include "types.h"


slibc_size_t str_length(const i8 * const string);
i8 *str_copy(i8* to, const i8* from);


#endif
