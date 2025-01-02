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

node *left_descendant(node *value);
node *right_descendant(node *value);
node *left_ancestor(node *value);
node *right_ancestor(node *value);

node *find(int key_to_find, node *root);

node *next(node *value);
node *prev(node *value);

void insert(int new_key, node **root);
void delete(int key, node **root);

void rotate_left(node *base, node **tree);
void rotate_right(node *base, node **tree);

#endif //AVL_H
