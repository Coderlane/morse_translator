/**
 * @file morse_tree.c
 * @brief 
 * @author Travis Lane
 * @version 1.0
 * @date 2014-12-08
 */

#include <morse_tree_internal.h>

/**
 * @brief Creates a new morse tree. 
 *
 * @return A new morse tree.
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
 * @brief Deletes a morse tree. 
 *
 * @param mt_ptr The morse tree to delete.
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
 * @brief Insert a character representing a morse sequence into the tree.
 *
 * @param mt The morse tree to insert into.
 * @param c The character to insert.
 * @param morse The morse sequence to map to. (only - or .)
 */
int
morse_tree_insert(struct morse_tree_t *mt, char c, const char* morse)
{
	int len, result = MTS_OK;

	if(!ismorsestr(morse)) {
		return MTS_ENON_MORSE;
	}

	len	= strlen(morse);
	if(len == 1) {
		// Check root case.
		if(morse[0] == '.') {
			result = morse_tree_node_set(mt->mt_dit, c);
		} else {
			result = morse_tree_node_set(mt->mt_dah, c);
		}
	} else {
		struct morse_tree_node_t* mtn_cur;
		struct morse_tree_node_t* mtn_nxt;
		int i;
		// Check longer than root case.

		// Set cur to correct root.
		if(morse[0] == '.') {
			mtn_cur = mt->mt_dit;	
		} else {
			mtn_cur = mt->mt_dah;
		}

		// Find location in tree.
		// Make nodes along the way if necessary.
		for(i = 1; i <= len; i++) {
			if(morse[i] == '.' ) {
				mtn_nxt = mtn_cur->mtn_dit;
				if(mtn_nxt == NULL) {
					// Add a new, uninitialized node.
					mtn_nxt = morse_tree_node_new();
					mtn_cur->mtn_dit = mtn_nxt;
				}
			} else {
				mtn_nxt = mtn_cur->mtn_dah;
				if(mtn_nxt == NULL) {
					// Add a new, uninitialized node.
					mtn_nxt = morse_tree_node_new();
					mtn_cur->mtn_dah = mtn_nxt;
				}
			}
			mtn_cur = mtn_nxt;
		}
		// Found our spot, set the node.
		result = morse_tree_node_set(mtn_cur, c);
	}
	return result;
}

/**
 * @brief Get the character mapped to a morse sequence. 
 *
 * @param mt The morse tree.
 * @param morse The morse sequence.
 *
 * @return The character mapped to a morse sequence, or -1 if not found.
 */
int 
morse_tree_get(struct morse_tree_t* mt, const char* morse)
{
	struct morse_tree_node_t* mtn_cur;
	struct morse_tree_node_t* mtn_nxt;
	int len, i;

	if(!ismorsestr(morse)) {
		return MTS_ENON_MORSE;
	}

	len	= strlen(morse);
	if(len == 1) {
		// Get root case.
		if(morse[0] == '.') {
			return morse_tree_node_get(mt->mt_dit);
		} else {
			return morse_tree_node_get(mt->mt_dah);
		}
	}

	// Cases beyond the root.
	// Set cur to correct root.
	if(morse[0] == '.') {
		mtn_cur = mt->mt_dit;	
	} else {
		mtn_cur = mt->mt_dah;
	}

	for(i = 1; i <= len; i++) {
		if(mtn_cur == NULL) {
			// Node couldn't have been created yet!
			return MTS_ENOT_INIT;
		}
		// Keep looking.
		if(morse[i] == '.' ) {
			mtn_nxt = mtn_cur->mtn_dit;
		} else {
			mtn_nxt = mtn_cur->mtn_dah;
		}
		mtn_cur = mtn_nxt;
	}

	if(mtn_cur == NULL) {
		// Target node not created yet.
		return MTS_ENOT_INIT;
	}
	return morse_tree_node_get(mtn_cur);
}

/**
 * @brief Create a new morse tree node.
 *
 * @return A new morse tree node.
 */
struct morse_tree_node_t* 
morse_tree_node_new()
{
	struct morse_tree_node_t *mtn = calloc(sizeof(struct morse_tree_node_t), 1);
	return mtn;			
}

/**
 * @brief Delete a morse tree node. 
 *
 * @param mtn_ptr The morse tree node to delete.
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

/**
 * @brief Get the value of a node.
 *
 * @param mtn The node to get.
 *
 * @return A character if set, else -1.
 */
int 
morse_tree_node_get(struct morse_tree_node_t* mtn)
{
	assert(mtn != NULL);
	if(mtn->mtn_init == 1) {
		return mtn->mtn_char;
	} else {
		return MTS_ENOT_INIT;
	}
}

/**
 * @brief Set the value of a node to a character.
 *
 * @param mtn The node to set.
 * @param c The character to set.
 */
int
morse_tree_node_set(struct morse_tree_node_t* mtn, char c)
{
	int result = MTS_OK;
	assert(mtn != NULL);
	
	if(mtn->mtn_init) {
		result = MTS_WARN;
	}

	mtn->mtn_init = 1; 
	mtn->mtn_char = c;

	return result;
}
