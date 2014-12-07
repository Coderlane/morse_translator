

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
morse_converter_get_ascii(struct morse_converter_t* mc, const char* morse)
{
	return morse_tree_get(mc->mc_tree, morse);
}

const char* 
morse_converter_get_morse(struct morse_converter_t* mc, char c)
{
	return morse_array_get(mc->mc_arr, c);
}

void 
morse_converter_to_morse(struct morse_converter_t* mc, 
		const char* input_filename, const char* output_filename)
{
	FILE *infile = NULL;
	FILE *outfile = NULL;

	infile = fopen(input_filename, "r");
	if(infile == NULL) {
		perror("Failed to open input file.");
		goto out;
	}

	outfile = fopen(output_filename, "wb");
	if(outfile == NULL) {
		perror("Failed to open output file.");
		goto out;
	}
	setbuf(outfile, NULL);

	while(!feof(infile)) {
		int ascii = fgetc(infile);
		if(ascii == EOF) {
			break;
		} else if(ascii == '\n') {
			fputs("\n", outfile);
		} else if(ascii != '\r'){
			const char *morse = morse_converter_get_morse(mc, ascii);
			fputs(morse, outfile);
			putc(' ', outfile);
		}
	}
	
out:
	if(infile != NULL) {
		fclose(infile);
	}
	if(outfile != NULL) {
		fclose(outfile);
	}
}

void morse_converter_to_ascii(struct morse_converter_t* mc, 
		const char* input_filename, const char* output_filename)
{
	FILE *in = NULL;
	FILE *out = NULL;
	char morse_arr[8];
	int morse_tail = 0;

	in = fopen(input_filename, "r");
	if(in == NULL) {
		perror("Failed to open input file.");
		goto out;
	}

	out = fopen(output_filename, "w");
	if(out == NULL) {
		perror("Failed to open output file.");
		goto out;
	}

	while(!feof(in)) {
		char morse = fgetc(in);
		if(morse == '\n' || morse == '\r') {
			fputc(morse, out);
		} else if(morse == ' ' && morse_tail != 0) {
			morse_arr[morse_tail] = '\0';
			char ascii = morse_converter_get_ascii(mc, morse_arr);
			fputc(ascii, out);
		} else {
			morse_arr[morse_tail] = morse;
			morse_tail++;
		}
	}

out:
	if(in != NULL) {
		fclose(in);
	}
	if(out != NULL) {
		fclose(out);
	}
}
