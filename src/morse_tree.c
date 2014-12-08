



#include <morse_tree.h>

/**
 * @brief 
 *
 * @return 
 */
	struct morse_tree_t* 
morse_tree_new()
{
	struct morse_tree_t *mt = malloc(sizeof(struct morse_tree_t));
	mt->mt_dah = morse_tree_node_new();
	mt->mt_dit = morse_tree_node_new();
	return mt;
}

/**
 * @brief 
 *
 * @param mt_ptr
 */
	void 
morse_tree_delete(struct morse_tree_t** mt_ptr)
{
	struct morse_tree_t* mt;
	assert(mt_ptr != NULL);

	mt = *mt_ptr;
	if(mt == NULL)
		return;

	morse_tree_node_delete(&(mt->mt_dah));
	morse_tree_node_delete(&(mt->mt_dit));

	free(mt);
	*mt_ptr = NULL;
}

/**
 * @brief 
 *
 * @param mt
 * @param c
 * @param morse
 */
	void 
morse_tree_insert(struct morse_tree_t *mt, char c, const char* morse)
{
	struct morse_tree_node_t* mtn_cur;
	struct morse_tree_node_t* mtn_nxt;
	int len;

	len	= strlen(morse);
	printf("%d:%c:%s\n", len, c, morse);
	if(len == 1) {
		if(morse[0] == '.') {
			printf("insert: %c at root dit\n", c);
			morse_tree_node_set(mt->mt_dit, c);
			return;
		} else {
			printf("insert: %c at root dah\n", c);
			morse_tree_node_set(mt->mt_dah, c);
			return;
		}
	}


	if(morse[0] == '.') {
		mtn_cur = mt->mt_dit;	
	} else {
		mtn_cur = mt->mt_dah;
	}

	for(int i = 1; i <= len; i++) {
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
	morse_tree_node_set(mtn_cur, c);
}

/**
 * @brief 
 *
 * @param mt
 * @param morse
 *
 * @return 
 */
	char 
morse_tree_get(struct morse_tree_t* mt, const char* morse)
{
	struct morse_tree_node_t* mtn_cur;
	struct morse_tree_node_t* mtn_nxt;
	int len;

	len	= strlen(morse);
	if(len == 1) {
		if(morse[0] == '.') {
			return morse_tree_node_get(mt->mt_dit);
		} else {
			return morse_tree_node_get(mt->mt_dah);
		}
	}

	if(morse[0] == '.') {
		mtn_cur = mt->mt_dit;	
	} else {
		mtn_cur = mt->mt_dah;
	}

	for(int i = 1; i <= len; i++) {
		if(mtn_cur == NULL) {
			return '\0';
		}
		if(morse[i] == '.' ) {
			mtn_nxt = mtn_cur->mtn_dit;
		} else {
			mtn_nxt = mtn_cur->mtn_dah;
		}
		mtn_cur = mtn_nxt;
	}
	if(mtn_cur == NULL) {
		return '\0';
	}
	return morse_tree_node_get(mtn_cur);
}

/**
 * @brief 
 *
 * @return 
 */
	struct morse_tree_node_t* 
morse_tree_node_new()
{
	struct morse_tree_node_t *mtn = calloc(sizeof(struct morse_tree_node_t), 1);
	return mtn;			
}

/**
 * @brief 
 *
 * @param mtn_ptr
 */
	void
morse_tree_node_delete(struct morse_tree_node_t** mtn_ptr)
{
	struct morse_tree_node_t* mtn;
	assert(mtn_ptr != NULL);

	mtn = *mtn_ptr;
	if(mtn == NULL)
		return;

	// Recurse down dah.
	if(mtn->mtn_dah != NULL) {
		morse_tree_node_delete(&(mtn->mtn_dah));
	}

	// Recurse down dit.
	if(mtn->mtn_dit != NULL) {
		morse_tree_node_delete(&(mtn->mtn_dit));
	}

	free(mtn);
	*mtn_ptr = NULL;
}

	char 
morse_tree_node_get(struct morse_tree_node_t* mtn)
{
	assert(mtn != NULL);
	if(mtn->mtn_init == 1) {
		return mtn->mtn_char;
	} else {
		return '\0';
	}
}

	void
morse_tree_node_set(struct morse_tree_node_t* mtn, char c)
{
	assert(mtn != NULL);
	mtn->mtn_init = 1; 
	mtn->mtn_char = c;
}
