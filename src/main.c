

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
 
	assert(argc >= 2);
	
	mc = morse_converter_new();
	morse_converter_load(mc, argv[1]);

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
