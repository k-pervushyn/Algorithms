//
// Created by kyrylo on 02/01/25.
//

#include "avl.h"

node *avl_find(const int key_to_find, node *root)
{
	node *res = NULL;
	if (!root)
		return NULL;
	if (root->key == key_to_find)
		res = root;
	else if (root->key > key_to_find)
		res = avl_find(key_to_find, root->left);
	else if (root->key < key_to_find)
		res = avl_find(key_to_find, root->right);
	if (res == NULL)
		return root;
	return res;
}

node *avl_left_descendant(node *value)
{
	while (value->left)
		value = value->left;
	return value;
}

node *avl_right_descendant(node *value)
{
	while (value->right)
		value = value->right;
	return value;
}

node *avl_left_ancestor(const node *value)
{
	const int key = value->key;
	while (value->parent && value->parent->key > key)
		value = value->parent;
	if (value->parent)
		return value->parent;
	return NULL;
}

node *avl_right_ancestor(const node *value)
{
	const int key = value->key;
	while (value->parent && value->parent->key < key)
		value = value->parent;
	if (value->parent)
		return value->parent;
	return NULL;
}

node *avl_next(const node *value)
{
	if (value->right != NULL)
		return avl_left_descendant(value->right);
	return avl_right_ancestor(value);
}

node *avl_prev(const node *value)
{
	if (value->left != NULL)
		return avl_right_descendant(value->left);
	return avl_left_ancestor(value);
}

void avl_insert(int new_key, node **root)
{
	node *new_node;
	if (!*root) {
		*root = malloc(sizeof(node));
		(*root)->parent = (*root)->left = (*root)->right = NULL;
		(*root)->key = new_key;
		return;
	}
    node *parent = avl_find(new_key, *root);
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

void avl_delete(int key, node **root)
{
	node *current = avl_find(key, *root), *next_val;
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
		next_val = avl_next(current);
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

void avl_rotate_left(node *base, node **tree)
{
	if (base->right == NULL)
		return;
	if (base == *tree) {
		*tree = base->right;
		base->right->parent = NULL;
	} else {
		base->right->parent = base->parent;
		if (base->parent->key > base->key)
			base->parent->left = base->right;
		else
			base->parent->right = base->right;
	}
	base->parent = base->right;
	base->right = base->right->left;
	base->right->left = base;
	if (base->right->left != NULL)
		base->right->left->parent = base;
}

void avl_rotate_right(node *base, node **tree)
{
	if (base->left == NULL)
		return;
	if (base == *tree) {
		*tree = base->left;
		base->left->parent = NULL;
	} else {
		base->left->parent = base->parent;
		if (base->parent->key > base->key)
			base->parent->left = base->left;
		else
			base->parent->right = base->left;
	}
	base->parent = base->left;
	base->left = base->left->right;
	base->left->right = base;
	if (base->left->right != NULL)
		base->left->right->parent = base;
}
