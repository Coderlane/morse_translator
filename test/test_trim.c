
#include <string_manip.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_STRS 6 

char *test_strs_initial[TEST_STRS] = {"", "   ", " a", "a ", " a ", " a a "};
char *test_strs_correct[TEST_STRS] = {"", "", "a", "a", "a", "a a"};

int main() {
	int i, result = 0;
	for(i = 0; i < TEST_STRS && result == 0; i++) {
		char *dup, *correct, *initial;
		
		initial = test_strs_initial[i];
		correct = test_strs_correct[i];

		// Duplicate for modification
		dup	= strdup(test_strs_initial[i]);

		trim(dup);
		
		// Compare results
		result = strcmp(dup, correct);
		if(result != 0) {
			fprintf(stderr, "Trim failed! "
					"Got [%s] Expected [%s] Initial [%s].\n", dup, correct, initial); 
		}

		free(dup);
	}
	return result;
}
