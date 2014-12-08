

#include <morse_converter.h>

/**
 * @brief Creates a new morse converter.
 *
 * @return A new morse converter.
 */
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

/**
 * @brief Deletes a morse converter.
 *
 * @param mc_ptr A pointer to a pointer to a morse converter.
 */
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

/**
 * @brief Loads a key file into the morse converter.
 *
 * @param mc The morse converter to load into.
 * @param filename The file to load.
 */
void 
morse_converter_load(struct morse_converter_t* mc, const char* filename)
{
	FILE* keyfile = NULL;

	assert(filename != NULL);
	keyfile = fopen(filename, "r");
	if(keyfile == NULL) {
		perror("Failed to open keyfile.");
		goto out;
	}

	while(!feof(keyfile)) {
		char line[MC_LINE_LEN];
		char *result;
		result = fgets(line, sizeof(line), keyfile);
		if(result != NULL) {
			trim(line);
			morse_tree_insert(mc->mc_tree, line[0], &line[2]);
			morse_array_insert(mc->mc_arr, line[0], &line[2]);
		}
	}

out:
	if(keyfile != NULL)
		fclose(keyfile);
}

/**
 * @brief Gets an ascii character from the morse tree.
 *
 * @param mc The morse converter.
 * @param morse The morse sequence.
 *
 * @return A character or the null character.
 */
char 
morse_converter_get_ascii(struct morse_converter_t* mc, const char* morse)
{
	return morse_tree_get(mc->mc_tree, morse);
}

/**
 * @brief Gets a segement of morse from an array.
 *
 * @param mc The morse converter.
 * @param c The character to convert.
 *
 * @return The morse sequence, or NULL.
 */
const char* 
morse_converter_get_morse(struct morse_converter_t* mc, char c)
{
	return morse_array_get(mc->mc_arr, c);
}

/**
 * @brief Read a file and write the morse output to another file.
 *
 * @param mc The morse converter. 
 * @param input_filename The input filename.
 * @param output_filename The output filename.
 */
void 
morse_converter_to_morse(struct morse_converter_t* mc, 
		const char* input_filename, const char* output_filename)
{
	int ascii;
	FILE *infile = NULL;
	FILE *outfile = NULL;

	infile = fopen(input_filename, "r");
	if(infile == NULL) {
		perror("Failed to open input file.");
		goto out;
	}

	outfile = fopen(output_filename, "w");
	if(outfile == NULL) {
		perror("Failed to open output file.");
		goto out;
	}

	// Read to the end.
	while((ascii = fgetc(infile)) != EOF) {
		if(ascii == '\n') {
			fprintf(outfile, "\n");
		} else if(ascii == ' ') {
			fprintf(outfile, " ");
		} else {
			const char *morse = morse_converter_get_morse(mc, ascii);
			if(morse == '\0') {
				fprintf(stderr, "Warning: Unmapped "
						"character: %c:%d\n", ascii, ascii);
			} else {
				fprintf(outfile, "%s ", morse);
			}
		}
	}

	// Cleanup 
out:
	if(infile != NULL) {
		fclose(infile);
	}
	if(outfile != NULL) {
		fclose(outfile);
	}
}

/**
 * @brief Converts a morse file to ascii.
 *
 * @param mc The morse converter.
 * @param input_filename The input morse file name.
 * @param output_filename The output ascii file name.
 */
void 
morse_converter_to_ascii(struct morse_converter_t* mc, 
		const char* input_filename, const char* output_filename)
{
	FILE *infile = NULL;
	FILE *outfile = NULL;
	char morse_arr[8];
	int morse_tail = 0;

	infile = fopen(input_filename, "r");
	if(infile == NULL) {
		perror("Failed to open input file.");
		goto out;
	}

	outfile = fopen(output_filename, "w");
	if(outfile == NULL) {
		perror("Failed to open output file.");
		goto out;
	}

	while(!feof(infile)) {
		char morse = fgetc(infile);
		if(morse != ' ' && isspace(morse)) {
			// Just write whitespace characters.
			fputc(morse, outfile);
		} else if(morse == ' ') {
			if(morse_tail != 0) {
					char ascii;	
					morse_arr[morse_tail] = '\0';
					ascii = morse_converter_get_ascii(mc, morse_arr);
					if (ascii == '\0') {
						fprintf(stderr, "Warning unmapped "
								"morse sequence: %s\n", morse_arr);
					} else {
						fputc(ascii, outfile);
					}
					morse_tail = 0;
				} else {
					fputc(' ', outfile);
				}
			} else {
			morse_arr[morse_tail] = morse;
			morse_tail++;
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
