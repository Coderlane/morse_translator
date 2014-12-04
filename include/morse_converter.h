

#ifndef MORSE_CONVERTER_H
#define MORSE_CONVERTER_H

#include <morse_tree.h>
#include <morse_array.h>

struct morse_converter_t {
	struct morse_tree_t* mt_tree;
	struct morse_array_t* mt_arr;
};

struct morse_converter_t* morse_converter_new();
void morse_converter_delete(struct morse_converter_t** mt_ptr);


#endif /* MORSE_CONVERTER_H */
