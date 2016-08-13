#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

struct avl_tree_node;
typedef struct avl_tree_node avl_tree_node_t;
typedef struct avl_tree_node *avl_tree_t;

int avl_tree_insert(avl_tree_t *t, int key);

int avl_tree_delete(avl_tree_t *t, int key);

int avl_print_tree(avl_tree_t t);


#endif
