#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"


int main(int argc, char *argv[])
{
	avl_tree_t t = NULL;
	int input[] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
	int i;

	for (i = 0; i < 10; i++) {
		avl_tree_insert(&t, input[i]);
	}
	avl_print_tree(t);
	printf("\n");

	avl_tree_delete(&t, 5);
	avl_tree_delete(&t, 8);
	avl_tree_delete(&t, 10);
	avl_print_tree(t);
	printf("\n");

	return 0;
}
