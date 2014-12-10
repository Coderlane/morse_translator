
#include <morse_array.h>
#include <morse_array_internal.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_create_and_delete();

void test_valid_insert_and_get();
void test_large_valid_insert_and_get();

void test_invalid_get();
void test_invalid_insert();

void test_dup_insert();

int 
main() 
{
	test_create_and_delete();
	test_valid_insert_and_get();
	test_invalid_get();
	test_large_valid_insert_and_get();
	return 0;
}

void
test_create_and_delete()
{
	struct morse_array_t *ma;
	ma = morse_array_new();

	morse_array_delete(&ma);
	assert(ma == NULL);
}

void 
test_valid_insert_and_get()
{
	struct morse_array_t *ma;
	ma = morse_array_new();

	morse_array_insert(ma, 'a', "...");

	assert(strcmp(morse_array_get(ma, 'a'), "...") == 0);

	morse_array_delete(&ma);
}

void
test_large_valid_insert_and_get()
{
	struct morse_array_t *ma;
	int i;
	ma = morse_array_new();

	for(i = 0; i < MORSE_ARRAY_LEN; i++) {
		morse_array_insert(ma, i, "-.-");
	}

	for(i = 0; i < MORSE_ARRAY_LEN; i++) {
		assert(strcmp(morse_array_get(ma, i), "-.-") == 0);
	}

	morse_array_delete(&ma);
}

void
test_invalid_get()
{
	struct morse_array_t *ma;
	ma = morse_array_new();

	assert(morse_array_get(ma, 'b') == NULL);
	assert(morse_array_get(ma, -1) == NULL);
	assert(morse_array_get(ma, MORSE_ARRAY_LEN + 1) == NULL);

	morse_array_delete(&ma);
}

void 
test_invalid_insert()
{
	struct morse_array_t *ma;
	ma = morse_array_new();

	assert(morse_array_insert(ma, -1, ".") != MAS_OK);
	assert(morse_array_insert(ma, MORSE_ARRAY_LEN + 1, ".") != MAS_OK);
	assert(morse_array_insert(ma, 1, "a") != MAS_OK);

	morse_array_delete(&ma);
}

void
test_dup_insert()
{
	struct morse_array_t *ma;
	ma = morse_array_new();

	assert(morse_array_insert(ma, 1, ".") == MAS_OK);
	assert(morse_array_insert(ma, 1, "-") == MAS_WARN);
	assert(strcmp(morse_array_get(ma, 1), "-") == 0);
	
	morse_array_delete(&ma);
}
