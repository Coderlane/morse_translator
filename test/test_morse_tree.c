
#include <morse_tree_internal.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_create_and_delete();

void test_valid_insert_and_get();

void test_invalid_get();
void test_invalid_insert();

void test_dup_insert();

int 
main() 
{
	test_create_and_delete();
	test_valid_insert_and_get();
	test_invalid_get();
	test_invalid_insert();
	test_dup_insert();
	return 0;
}

void
test_create_and_delete()
{
	struct morse_tree_t *mt;
	mt = morse_tree_new();

	morse_tree_delete(&mt);
	assert(mt == NULL);
}

void 
test_valid_insert_and_get()
{
	struct morse_tree_t *mt;
	mt = morse_tree_new();

	morse_tree_insert(mt, 'a', "...");

	assert(morse_tree_get(mt, "...") == 'a');

	morse_tree_delete(&mt);
}

void
test_invalid_get()
{
	struct morse_tree_t *mt;
	mt = morse_tree_new();

	assert(morse_tree_get(mt, "-") < 0);
	assert(morse_tree_get(mt, "") < 0);
	assert(morse_tree_get(mt, "a") < 0);

	morse_tree_delete(&mt);
}

void 
test_invalid_insert()
{
	struct morse_tree_t *mt;
	mt = morse_tree_new();

	assert(morse_tree_insert(mt, 1, "a") != MTS_OK);

	morse_tree_delete(&mt);
}

void
test_dup_insert()
{
	struct morse_tree_t *mt;
	mt = morse_tree_new();

	assert(morse_tree_insert(mt, 'a', ".") == MTS_OK);
	assert(morse_tree_insert(mt, 'b', ".") == MTS_WARN);
	assert(morse_tree_get(mt, ".") == 'b');
	
	morse_tree_delete(&mt);
}
