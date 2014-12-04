
#include <morse_array.h>



/**
 * @brief 
 *
 * @return 
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
 * @brief 
 *
 * @param ma_ptr
 */
void 
morse_array_delete(struct morse_array_t** ma_ptr)
{
	struct morse_array_t* ma;
	assert(ma_ptr != NULL);
	
	ma = *ma_ptr;
	if(ma == NULL)
		return;

	for(int i = 0; i < MORSE_ARRAY_LEN; i++) {
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
 * @brief 
 *
 * @param ma
 * @param c
 * @param morse
 */
void 
morse_array_insert(struct morse_array_t* ma, 
		const int c, const char *morse)
{
	assert(ma != NULL);
	assert(morse != NULL);
	assert(c >= 0 && c < MORSE_ARRAY_LEN);
	
	if(ma->ma_arr[c] != NULL) {
		// Should this be an error?
		free(ma->ma_arr[c]);
	}
	ma->ma_arr[c] = strdup(morse);
}

/**
 * @brief 
 *
 * @param ma
 * @param c
 *
 * @return 
 */
const char*
morse_array_get(struct morse_array_t* ma, const int c)
{
	assert(ma != NULL);
	assert(c >= 0 && c < MORSE_ARRAY_LEN);
	return ma->ma_arr[c];
}
