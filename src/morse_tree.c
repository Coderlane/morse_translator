



#include <morse_tree.h>

struct morse_tree_t* 
morse_tree_new()
{
	struct morse_tree_t *mt = malloc(sizeof(struct morse_tree_t));
	mt->mt_dah = morse_tree_node_new();
	mt->mt_dit = morse_tree_node_new();
	return mt;
}

void 
morse_tree_load(struct morse_tree_t* mt, char* filename)
{
	char *line = NULL;
	int len = 0, read;
	FILE *file;
	
	assert(filename != NULL);
	file = fopen(filename, "r");

	while((read = getline(&line, &len, file)) != -1) {
		line[read - 1] = '\0';
		morse_tree_insert(mt, line[0], &line[2]);
	}
	if(line != NULL) 
		free(line);
	fclose(file);
}

void 
morse_tree_insert(struct morse_tree_t *mt, char c, char* morse)
{
	int len = strlen(morse);
	printf("%c:%s\n", c, morse);
	if(len == 1) {
		if(morse[0] == '.') {
			mt->mt_dit->mtn_char = c;
			mt->mt_dit->mtn_init = 1;
		} else {
			mt->mt_dah->mtn_char = c;
			mt->mt_dah->mtn_init = 1;
		}
	} else {
		struct morse_tree_node_t* mtn_cur;
		struct morse_tree_node_t* mtn_nxt;

		if(morse[0] == '.') {
			mtn_cur = mt->mt_dit;	
		} else {
			mtn_cur = mt->mt_dah;
		}

		for(int i = 1; i < len; i++) {
			if(morse[i] == '.' ) {
				mtn_nxt = mtn_cur->mtn_dit;
				if(mtn_nxt == NULL) {
					mtn_nxt = morse_tree_node_new();
					mtn_cur->mtn_dit = mtn_nxt;
				}
			} else {
				mtn_nxt = mtn_cur->mtn_dah;
				if(mtn_nxt == NULL) {
					mtn_nxt = morse_tree_node_new();
					mtn_cur->mtn_dah = mtn_nxt;
				}
			}
			mtn_cur = mtn_nxt;
		}
		mtn_cur->mtn_init = 1;
		mtn_cur->mtn_char = c;
	}
}

char 
morse_tree_get(struct morse_tree_t *mt, char *morse)
{
	int len = strlen(morse);

	if(len == 1) {
		if(morse[0] == '.') {
			assert(mt->mt_dit->mtn_init == 1);
			return mt->mt_dit->mtn_char;
		} else {
			assert(mt->mt_dit->mtn_init == 1);
			return mt->mt_dah->mtn_char;
		}
	} else {
		struct morse_tree_node_t* mtn_cur;
		struct morse_tree_node_t* mtn_nxt;

		if(morse[0] == '.') {
			mtn_cur = mt->mt_dit;	
		} else {
			mtn_cur = mt->mt_dah;
		}

		for(int i = 1; i <= len; i++) {
			if(morse[i] == '.' ) {
				mtn_nxt = mtn_cur->mtn_dit;
				assert(mtn_nxt != NULL);
			} else {
				mtn_nxt = mtn_cur->mtn_dah;
				assert(mtn_nxt != NULL);
			}
			mtn_cur = mtn_nxt;
		}
		assert(mtn_cur->mtn_init == 1);
		return mtn_cur->mtn_char;
	}
}

struct morse_tree_node_t* 
morse_tree_node_new()
{
	struct morse_tree_node_t *mtn = calloc(sizeof(struct morse_tree_node_t), 1);
	return mtn;			
}


