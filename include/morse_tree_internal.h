
#ifndef MORSE_TREE_INTERNAL_H
#define MORSE_TREE_INTERNAL_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <string_manip.h>
#include <morse_tree.h>

struct morse_tree_t {
	struct morse_tree_node_t* mt_dah;
	struct morse_tree_node_t* mt_dit;
};

struct morse_tree_node_t {
	int mtn_init;
	char mtn_char;
	struct morse_tree_node_t*	mtn_dah;
	struct morse_tree_node_t*	mtn_dit;
};

struct morse_tree_node_t* morse_tree_node_new();
void morse_tree_node_delete(struct morse_tree_node_t** mtn_ptr);

int morse_tree_node_get(struct morse_tree_node_t *mtn);
int morse_tree_node_set(struct morse_tree_node_t *mtn, char c);

#endif /* MORSE_TREE_INTERNAL_H */
