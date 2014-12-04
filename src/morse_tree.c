



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
	int len = strlen(morse);
//	printf("%c:%s\n", c, morse);
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
