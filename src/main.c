

#include <morse_converter.h>

int main(int argc, char **argv) {
	struct morse_converter_t *mc = morse_converter_new();

	assert(argc >= 2);
	morse_converter_load(mc, argv[1]);

	//printf("%c", morse_converter_load_get(mc, ".-"));
	printf("%c\n", morse_converter_get_char(mc, "-.-."));
	printf("%s\n", morse_converter_get_morse(mc, 'c'));

	morse_converter_delete(&mc);
	return 0;
}
