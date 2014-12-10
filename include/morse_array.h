/**
 * @file morse_array.h
 * @brief 
 * @author Travis Lane
 * @version 1.0
 * @date 2014-12-08
 */

#ifndef MORSE_ARRAY_H
#define MORSE_ARRAY_H

enum morse_array_status_e {
	MAS_EPTR = -4,
	MAS_EMEM = -3,
	MAS_ENON_MORSE = -2,
	MAS_EBOUNDS = -1,
	MAS_OK = 0,
	MAS_WARN = 1
};

struct morse_array_t* morse_array_new();
void morse_array_delete(struct morse_array_t** ma_ptr);

int morse_array_insert(struct morse_array_t* ma, 
		const int c, const char *morse); 
const char* morse_array_get(struct morse_array_t* ma, const int c);

#endif
