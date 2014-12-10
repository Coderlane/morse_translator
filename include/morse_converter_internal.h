/**
 * @file morse_converter_internal.h
 * @brief 
 * @author Travis Lane
 * @version 1.0
 * @date 2014-12-08
 */

#ifndef MORSE_CONVERTER_INTERNAL_H
#define MORSE_CONVERTER_INTERNAL_H

/**
 * @brief The maximum length of a chunk of the map being read.
 */
#define MC_MAP_CHUNK_LEN 512

/**
 * @brief The maximum length of a morse sequence.
 */
#define MC_MORSE_CHUNK_LEN 16

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <morse_array.h>
#include <morse_tree.h>
#include <morse_converter.h>

#include <string_manip.h>

struct morse_converter_t {
	struct morse_tree_t* mc_tree;
	struct morse_array_t* mc_arr;
};

#endif /* MORSE_CONVERTER_INTERNAL_H */
