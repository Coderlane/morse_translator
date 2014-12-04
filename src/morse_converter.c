

#include <morse_converter.h>

struct morse_converter_t* 
morse_converter_new()
{
	struct morse_converter_t* mc;
	mc = malloc(sizeof(struct morse_converter_t));
	assert(mc != NULL);
	mc->mc_arr = morse_array_new();
	mc->mc_tree = morse_tree_new();
	return mc;
}

void 
morse_converter_delete(struct morse_converter_t** mc_ptr)
{
	struct morse_converter_t* mc;
	assert(mc_ptr != NULL);
	
	mc = *mc_ptr;
	if(mc == NULL)
		return;

	morse_tree_delete(&(mc->mc_tree));
	morse_array_delete(&(mc->mc_arr));

	free(mc);
	*mc_ptr = NULL;
}

void 
morse_converter_load(struct morse_converter_t* mc, const char* filename)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *file;
	
	assert(filename != NULL);
	file = fopen(filename, "r");

	while((read = getline(&line, &len, file)) != -1) {
		line[read - 1] = '\0';
		morse_tree_insert(mc->mc_tree, line[0], &line[2]);
		morse_array_insert(mc->mc_arr, line[0], &line[2]);
	}
	if(line != NULL) 
		free(line);

	fclose(file);
}


char 
morse_converter_get_char(struct morse_converter_t* mc, const char* morse)
{
	return morse_tree_get(mc->mc_tree, morse);
}

const char* 
morse_converter_get_morse(struct morse_converter_t* mc, char c)
{
	return morse_array_get(mc->mc_arr, c);
}
