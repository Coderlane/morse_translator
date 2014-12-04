


#ifndef MORSE_TREE_H
#define MORSE_TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct morse_tree_t {
	struct morse_tree_node_t* mt_dah;
	struct morse_tree_node_t* mt_dit;
};

struct morse_tree_node_t {
	int mtn_init;
	char mtn_char;
	struct morse_tree_node_t *mtn_dah;
	struct morse_tree_node_t *mtn_dit;
};

struct morse_tree_t* morse_tree_new();

void morse_tree_load(struct morse_tree_t* mt, char* filename);

void morse_tree_insert(struct morse_tree_t *mt, char c, char* morse);
char morse_tree_get(struct morse_tree_t *mt, char *morse);

struct morse_tree_node_t* morse_tree_node_new();

#endif
