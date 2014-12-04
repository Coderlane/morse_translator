

#include <morse_tree.h>

int main(int argc, char **argv) {
	struct morse_tree_t *mt = morse_tree_new();

	assert(argc >= 2);
	morse_tree_load(mt, argv[1]);

	printf("%c", morse_tree_get(mt, ".-"));
	return 0;
}
