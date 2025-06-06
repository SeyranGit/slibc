#pragma once

#ifndef SLIBC_STRING_H
#define SLIBC_STRING_H

#include <types.h>


/*
 * Calculates the number of characters in a regular string,
 * where each character takes up 1 byte.
 * The function walks the string until the character
 * with code 0 (the null terminator) and returns the
 * number of characters (bytes) up to it, not counting
 * the terminating null itself.
 *
 * string: Pointer to a NUL-terminated character string of type i8 (char).
 *         Should point to a memory area containing a sequence of bytes
 *         and a terminating byte with value 0.
 *
 * Returns the number of characters (bytes) in the string, not including
 * the terminating null byte.
 */
slibc_size_t slength(const i8 * const string);


/*
 * Calculates the number of characters in a wide string,
 * where each character is 2 bytes.
 * The function iterates through a wide string array of type
 * ui16 (wchar_t, unsigned short) until the element with
 * value 0 (the wide null terminator) and returns the
 * number of characters up to it, not including the terminating null itself.
 *
 * string:  Pointer to a NUL-terminated wide string of type ui16 (wchar_t, unsigned short).
 *          Each element is 2 bytes (16 bits), and the string is terminated by an element with value 0.
 *
 * Returns the number of wide characters (ui16 elements) in the string,
 * not including the terminating null.
 */
slibc_size_t wslength(const ui16 * const string);


i8 *scopy(i8 *to, const i8 *from);
i8 *sncopy(i8 *to, const i8 *from, slibc_size_t n);
ui16 *wscopy(ui16 *to, const ui16 *from);


#endif
