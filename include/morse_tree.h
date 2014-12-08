/**
 * @file morse_tree.h
 * @brief 
 * @author Travis Lane
 * @version 1.0
 * @date 2014-12-08
 */

#ifndef MORSE_TREE_H
#define MORSE_TREE_H

/**
 * @brief Maps morse sequences to characters.
 */
struct morse_tree_t;

struct morse_tree_t* morse_tree_new();
void morse_tree_delete(struct morse_tree_t** mt_ptr);

void morse_tree_insert(struct morse_tree_t* mt, char c, const char* morse);
int morse_tree_get(struct morse_tree_t* mt, const char* morse);

#endif
