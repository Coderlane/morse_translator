
#include <string_manip.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CASES 6 

char *test_strings[TEST_CASES] = {"", ".", ".-", ".- ", " -.", " -. "};
int test_results[TEST_CASES] = 	{1, 	1, 		1, 		0, 		0, 			0};

int main() {
	int i;
	for(i = 0; i < TEST_CASES; i++) {
		int result;	
		result = ismorsestr(test_strings[i]);

		// Compare results
		if(result != test_results[i]) {
			fprintf(stderr, "ismorsestr failed! "
					"Got [%d] Expected [%d] Input: [%s].\n",
				 	result, test_results[i], test_strings[i]); 
			return -1;
		}
	}
	return 0;
}

