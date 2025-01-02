//
// Created by kyrylo on 02/01/25.
//

#ifndef BST_H
#define BST_H

#include <stdlib.h>

typedef struct str_node {
	int key;
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

#endif BST_H //BST_H
