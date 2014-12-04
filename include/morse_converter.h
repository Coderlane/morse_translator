

#ifndef MORSE_CONVERTER_H
#define MORSE_CONVERTER_H

#include <morse_tree.h>
#include <morse_array.h>

struct morse_converter_t {
	struct morse_tree_t* mc_tree;
	struct morse_array_t* mc_arr;
};

struct morse_converter_t* morse_converter_new();
void morse_converter_delete(struct morse_converter_t** mc_ptr);

void morse_converter_load(struct morse_converter_t* mc, const char* filename);

char morse_converter_get_char(struct morse_converter_t* mc, const char* morse);
const char* morse_converter_get_morse(struct morse_converter_t* mc, char c);
#endif /* MORSE_CONVERTER_H */
