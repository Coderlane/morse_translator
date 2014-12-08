
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <morse_converter.h>

enum choice_e {
	EXIT_CHOICE = 0,
 	TO_MORSE_CHOICE = 1,
	TO_ASCII_CHOICE = 2
};

int menu();

int 
main(int argc, char **argv) 
{
	int choice;
	char input_filename[1024];
	char output_filename[1024];
	struct morse_converter_t *mc;
 
	assert(argc == 2 || argc == 5);
	
	mc = morse_converter_new();
	morse_converter_load(mc, argv[1]);
	
	if(argc == 2) {
	while((choice = menu()) != EXIT_CHOICE) 
	{

		printf("Input filename: ");
		scanf("%s", input_filename);

		printf("Output filename: ");
		scanf("%s", output_filename);

		if(choice == TO_MORSE_CHOICE) {
			morse_converter_to_morse(mc, input_filename, output_filename);
		} else {
			morse_converter_to_ascii(mc, input_filename, output_filename);
		}
	}
	} else {
		if(strcmp(argv[2], "m") == 0) {
			morse_converter_to_morse(mc, argv[3], argv[4]);
		} else if(strcmp(argv[2], "a") == 0) {
			morse_converter_to_ascii(mc, argv[3], argv[4]);
		} else {
			fprintf(stderr, "Please choose m or a.\n");
			exit(-1);
		}
	}
	morse_converter_delete(&mc);
	return 0;
}

int 
menu() 
{
	int choice;
	do {
		printf(	"0: Exit\n"
						"1: To morse.\n"
						"2: To ascii.\n");
		printf("Choice: ");
		scanf("%d", &choice);
		if(choice < 0 || choice > TO_ASCII_CHOICE) {
			printf("Invalid!\n");
		}
	} while(choice < 0 || choice > TO_ASCII_CHOICE);
	return choice;
}
