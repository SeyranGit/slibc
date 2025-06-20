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
SlibcSize slength(const i8 * const string);


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
SlibcSize wslength(const ui16 * const string);


i8 *scopy(i8 *to, const i8 *from);
i8 *sncopy(i8 *to, const i8 *from, SlibcSize n);
i8 *scat(i8 * const s1, const i8 * const s2);
i8 *sncat(i8 *s1, const i8 * const s2, SlibcSize n);
i8 *subc(const i8 *string, i8 c);
i8 *rsubc(const i8 *string, i8 symbol);

ui16 *wscopy(ui16 *to, const ui16 *from);
ui16 *wsncopy(ui16 *to, const ui16 *from, SlibcSize n);
ui16 *wscat(ui16 * const s1, const ui16 * const s2);
ui16 *wsncat(ui16 *s1, const ui16 * const s2, SlibcSize n);
ui16 *wsubc(const ui16 *string, ui16 symbol);


#endif
