//
// Created by kyrylo on 02/01/25.
//

#include "bst.h"

node *find(int key_to_find, node *root)
{
	node *res;
	if (!root)
		return NULL;
	if (root->key == key_to_find)
		res = root;
	else if (root->key > key_to_find)
		res = find(key_to_find, root->left);
	else if (root->key < key_to_find)
		res = find(key_to_find, root->right);
	if (res == NULL)
		return root;
	return res;
}

node *left_descendant(node *value)
{
	while (value->left)
		value = value->left;
	return value;
}

node *right_descendant(node *value)
{
	while (value->right)
		value = value->right;
	return value;
}

node *left_ancestor(node *value)
{
	int key = value->key;
	while (value->parent && value->parent->key > key)
		value = value->parent;
	if (value->parent)
		return value->parent;
	return NULL;
}

node *right_ancestor(node *value)
{
	int key = value->key;
	while (value->parent && value->parent->key < key)
		value = value->parent;
	if (value->parent)
		return value->parent;
	return NULL;
}

node *next(node *value)
{
	if (value->right != NULL)
		return left_descendant(value->right);
	return right_ancestor(value);
}

node *prev(node *value)
{
	if (value->left != NULL)
		return right_descendant(value->left);
	return left_ancestor(value);
}

void insert(int new_key, node **root)
{
	node *parent, *new_node;
	if (!*root) {
		*root = malloc(sizeof(node));
		(*root)->parent = (*root)->left = (*root)->right = NULL;
		(*root)->key = new_key;
		return;
	}
    parent = find(new_key, *root);
	if (parent->key == new_key)
		return;
	if (parent->key < new_key) {
		parent->right = malloc(sizeof(node));
		new_node = parent->right;
	} else {
		parent->left = malloc(sizeof(node));
		new_node = parent->left;
	}
	new_node->key = new_key;
	new_node->parent = parent;
	new_node->left = new_node->right = NULL;
}

void delete(int key, node **root)
{
	node *current = find(key, *root);
	if (current->key != key)
		return;
	if (current->right == NULL) {
		if (!current->parent) {
			*root = current->left;
			if (current->left)
				current->left->parent = NULL;
			free(current);
			return;
		}
		if (current->left != NULL)
			current->left->parent = current->parent;
		if (current->parent->key > key)
			current->parent->left = current->left;
		else
			current->parent->right = current->left;
		free(current);
	} else {
		node *next_val = next(current);
		current->key = next_val->key;
		if (next_val->right != NULL) {
			next_val->right->parent = next_val->parent;
			if (next_val->parent->key > next_val->key)
				next_val->parent->left = next_val->right;
			else
				next_val->parent->right = next_val->right;
		} else {
			if (next_val->parent->key > next_val->key)
				next_val->parent->left = NULL;
			else
				next_val->parent->right = NULL;
		}
		free(next_val);
	}
}
