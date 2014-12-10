/**
 * @file morse_array.c
 * @brief 
 * @author Travis Lane
 * @version 1.0
 * @date 2014-12-08
 */

#include <morse_array_internal.h>

/**
 * @brief Creates a new morse array. 
 *
 * @return The new morse array.
 */
struct morse_array_t*
morse_array_new()
{
	struct morse_array_t *ma = malloc(sizeof(struct morse_array_t));
	assert(ma != NULL);
	ma->ma_arr = calloc(sizeof(char*), MORSE_ARRAY_LEN);
	assert(ma->ma_arr != NULL);
	return ma;
}

/**
 * @brief Destroys the morse array. 
 *
 * @param ma_ptr The morse array to destroy.
 */
void 
morse_array_delete(struct morse_array_t** ma_ptr)
{
	struct morse_array_t* ma;
	int i;

	assert(ma_ptr != NULL);
	
	ma = *ma_ptr;
	if(ma == NULL)
		return;
	
	// Free memory from each index.
	for(i = 0; i < MORSE_ARRAY_LEN; i++) {
		if(ma->ma_arr[i] != NULL) {
			free(ma->ma_arr[i]);
			ma->ma_arr[i] = NULL;
		}
	}
	
	free(ma->ma_arr);
	free(ma);

	*ma_ptr = NULL;
}

/**
 * @brief Inserts a morse sequence mapping to a character into the array.
 *
 * @param ma The morse array.
 * @param c The character to map the sequence to.
 * @param morse The morse sequence.
 */
int 
morse_array_insert(struct morse_array_t* ma, 
		const int c, const char *morse)
{
	int status = MAS_OK;
	assert(ma != NULL);
	assert(morse != NULL);

	if(c < 0 || c > MORSE_ARRAY_LEN) {
		// Out of bounds, should this be an error?
		fprintf(stderr, "Error, inserting character "
				"out of bounds: Character %c:%d\n", c, c);
		return MAS_EBOUNDS;
	}

	if(!ismorsestr(morse)) {
		fprintf(stderr, "Attempted to insert a non-morse "
				"string to the morse array. String: %s\n", morse);
		return MAS_ENON_MORSE;
	}
	
	if(ma->ma_arr[c] != NULL) {
		// Should this be an error?
		free(ma->ma_arr[c]);
		status = MAS_WARN;
	}

	ma->ma_arr[c] = strdup(morse);
	assert(ma->ma_arr[c] != NULL);

	return status;
}

/**
 * @brief Get the morse sequence mapped to a character.
 *
 * @param ma The morse array.
 * @param c The character to get a sequence for.
 *
 * @return The sequence found, or NULL.
 */
const char*
morse_array_get(struct morse_array_t* ma, const int c)
{
	assert(ma != NULL);
	if(c < 0 || c > MORSE_ARRAY_LEN) {
		// Out of bounds, should this be an error?
		return NULL;
	}
	return ma->ma_arr[c]; // COULD BE NULL.
}
