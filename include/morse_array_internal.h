/**
 * @file morse_array_internal.h
 * @brief 
 * @author Travis Lane
 * @version 1.0
 * @date 2014-12-08
 */

#ifndef MORSE_ARRAY_INTERNAL_H
#define MORSE_ARRAY_INTERNAL_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string_manip.h>
#include <morse_array.h>

/**
 * @brief Number of elements in the morse array.
 */
#define MORSE_ARRAY_LEN 256

struct morse_array_t {
	char **ma_arr;
};

#endif
