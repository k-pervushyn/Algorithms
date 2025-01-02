#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

static char is_insert_query(char *string)
{
	return string[0] == 'i' && string[1] == 'n'
		&& string[2] == 's';
}

static char is_delete_query(char *string)
{
	return string[0] == 'd' && string[1] == 'e'
		&& string[2] == 'l';
}

static char is_find_query(char *string)
{
	return string[0] == 'f' && string[1] == 'i'
		&& string[2] == 'n' && string[3] == 'd';
}

static char is_next_query(char *string)
{
	return string[0] == 'n' && string[1] == 'e'
		&& string[2] == 'x' && string[3] == 't';
}

static char is_prev_query(char *string)
{
	return string[0] == 'p' && string[1] == 'r'
		&& string[2] == 'e' && string[3] == 'v';
}

/*static char is_find_query(char *string)
{
	return string[0] == 'f' && string[1] == 'i'
		&& string[2] == 'n' && string[3] == 'd';
}*/

void inorder(node *tree)
{
	if (!tree) return;
	inorder(tree->left);
	printf("%d ", tree->key);
	inorder(tree->right);
}

int main()
{
	int number, next_num, cnt;
	char next_query[5];
	node *tree = NULL, *hlp;
	scanf("%d", &number);

	for (cnt = 0; cnt < number; cnt++) {
		scanf("%4s", next_query);
		if (is_insert_query(next_query)) {
			scanf("%d", &next_num);
			insert(next_num, &tree);
		} else if (is_delete_query(next_query)) {
			scanf("%d", &next_num);
			delete(next_num, &tree);
		} else if (is_find_query(next_query)) {
			scanf("%d", &next_num);
			hlp = find(next_num, tree);
			if (hlp->key == next_num)
				printf("present\n");
			else
				printf("absent, found parent %d\n", hlp->key);
		} else if (is_next_query(next_query)) {
			scanf("%d", &next_num);
			hlp = find(next_num, tree);
			if (hlp->key != next_num)
				printf("no this element\n");
			else {
				hlp = next(hlp);
				if (!hlp)
					printf("no next element\n");
				else
					printf("next element is %d\n", hlp->key);
			}
		} else if (is_prev_query(next_query)) {
			scanf("%d", &next_num);
			hlp = find(next_num, tree);
			if (hlp->key != next_num)
				printf("no this element\n");
			else {
				hlp = prev(hlp);
				if (!hlp)
					printf("no prev element\n");
				else
					printf("prev element is %d\n", hlp->key);
			}
		} else continue;
		if (tree)
			inorder(tree);
		putchar('\n');
	}
	return 0;
}
