

#ifndef MORSE_ARRAY_H
#define MORSE_ARRAY_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MORSE_ARRAY_LEN 256

struct morse_array_t {
	char **ma_arr;
};

struct morse_array_t* morse_array_new();
void morse_array_delete(struct morse_array_t** ma_ptr);

void morse_array_set(struct morse_array_t* ma, 
		const int c, const char *morse); 
const char* morse_array_get(struct morse_array_t* ma, const int c);

#endif
