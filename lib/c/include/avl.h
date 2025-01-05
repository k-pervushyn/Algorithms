//
// Created by kyrylo on 02/01/25.
//

#ifndef AVL_H
#define AVL_H

#include <stdlib.h>

typedef struct str_node {
	int key;
	int height;
	struct str_node *parent;
	struct str_node *left;
	struct str_node *right;
} node;

node *avl_left_descendant(node *value);
node *avl_right_descendant(node *value);
node *avl_left_ancestor(const node *value);
node *avl_right_ancestor(const node *value);

node *avl_find(int key_to_find, node *root);

node *avl_next(const node *value);
node *avl_prev(const node *value);

void avl_insert(int new_key, node **root);
void avl_delete(int key, node **root);

void avl_rotate_left(node *base, node **tree);
void avl_rotate_right(node *base, node **tree);

#endif //AVL_H
