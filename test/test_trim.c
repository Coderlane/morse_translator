
#include <string_manip.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_STRS 4 

char *test_strs_initial[TEST_STRS] = {"   ", " a", "a ", " a "};
char *test_strs_correct[TEST_STRS] = {"", "a", "a", "a"};

int main() {
	int i;
	for(i = 0; i < TEST_STRS; i++) {
		char *dup, *correct, *initial;
		int result;
		
		initial = test_strs_initial[i];
		correct = test_strs_correct[i];
		dup	= strdup(test_strs_initial[i]);

		trim(dup);
		
		result = strcmp(dup, correct);
		if(result != 0) {
			fprintf(stderr, "Trim failed! "
					"Got [%s] Expected [%s] Initial [%s].\n", dup, correct, initial); 
			free(dup);
			return result;
		}
		free(dup);
	}
	return 0;
}
