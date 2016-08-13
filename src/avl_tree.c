#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"


struct avl_tree_node {
	int key;
	int height;
	struct avl_tree_node *left, *right;
};

#define TRUE	1
#define FALSE	0

#define HEIGHT(t) ((t == NULL) ? 0 : (((avl_tree_node_t *)(t))->height))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static void left_left_rotation(avl_tree_t *t);

static void left_right_rotation(avl_tree_t *t);

static void right_right_rotation(avl_tree_t *t);

static void right_left_rotation(avl_tree_t *t);

static avl_tree_node_t *avl_tree_maxinum(avl_tree_t t);

static avl_tree_node_t *avl_tree_mininum(avl_tree_t t);

int avl_tree_insert(avl_tree_t *t, int key) 
{

	if (*t == NULL) {

		*t = (avl_tree_t)malloc(sizeof(avl_tree_node_t));
		if (*t == NULL)
			return FALSE;
		(*t)->left = (*t)->right = NULL;
		(*t)->key = key;
	
	} else {

		if (key < (*t)->key) {
			
			if (!avl_tree_insert(&(*t)->left, key))
				return FALSE;
			if (HEIGHT((*t)->left) - HEIGHT((*t)->right) == 2) {
				if (key < (*t)->left->key)
					left_left_rotation(t);
				else
					left_right_rotation(t);
			}

		} else if (key > (*t)->key) {

			if (!avl_tree_insert(&(*t)->right, key))
				return FALSE;
			if (HEIGHT((*t)->right) - HEIGHT((*t)->left) == 2) {
				if (key > (*t)->right->key)
					right_right_rotation(t);
				else
					right_left_rotation(t);
			}
			
		} else {
			// key = (*t)->key
			return FALSE;
		}
	}

	(*t)->height = MAX(HEIGHT((*t)->left), HEIGHT((*t)->right)) + 1; 
	
	return TRUE;
}

int avl_tree_delete(avl_tree_t *t, int key)
{
	if (*t == NULL)
		return FALSE;

	if (key < (*t)->key) {
		
		if (!avl_tree_delete(&(*t)->left, key))
			return FALSE;

		if (HEIGHT((*t)->right) - HEIGHT((*t)->left) == 2) {
		
			avl_tree_node_t *r;
			
			r = (*t)->right;
			
			if (HEIGHT(r->left) > HEIGHT(r->right))
				right_left_rotation(t);
			else
				right_right_rotation(t);
		}

		(*t)->height = MAX(HEIGHT((*t)->left), HEIGHT((*t)->right)) + 1; 

	} else if (key > (*t)->key) {
		
		if (!avl_tree_delete(&(*t)->right, key))
			return FALSE;

		if (HEIGHT((*t)->left) - HEIGHT((*t)->right) == 2) {
			
			avl_tree_node_t *l;

			l = (*t)->left;

			if (HEIGHT(l->right) > HEIGHT(l->left))
				left_right_rotation(t);
			else
				left_left_rotation(t);
		}
		
		(*t)->height = MAX(HEIGHT((*t)->left), HEIGHT((*t)->right)) + 1; 
	} else {
		
		if ((*t)->left && (*t)->right) {
			
			if (HEIGHT((*t)->left) > HEIGHT((*t)->right)) {
				
				avl_tree_node_t *max;

				if ((max = avl_tree_maxinum((*t)->left)) != NULL) {
					(*t)->key = max->key;
					avl_tree_delete(&(*t)->left, max->key);
				}
			} else {
				
				avl_tree_node_t *min;

				if ((min = avl_tree_mininum((*t)->right)) != NULL) {
					(*t)->key = min->key;
					avl_tree_delete(&(*t)->right, min->key);
				}
			}
		} else {
			avl_tree_t tmp = *t;
			*t = (*t)->left ? (*t)->left : (*t)->right;
			free(tmp);
		}
	}
	
	return TRUE;
}

int avl_print_tree(avl_tree_t t)
{
	if (t == NULL)
		return FALSE;
	printf("%d(%d) ", t->key, t->height);
	avl_print_tree(t->left);
	avl_print_tree(t->right);
	return TRUE;
}

/*
 *        (k1)*
 *	     / \
 *      (k2)*   *A       =>  (k2)*
 *         / \                  / \
 *        *B  *C               *B  *(k1)
 *       /                    /   / \
 *      *D                   *D  *C  *A
 *
 *	LL rotation
 */
static void left_left_rotation(avl_tree_t *t) 
{
	
	avl_tree_node_t *k1, *k2;

	k1 = *t;
	k2 = k1->left;
	k1->left = k2->right;
	k2->right = k1;
	
	k1->height = MAX(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
	k2->height = MAX(HEIGHT(k2->left), k1->height) + 1;

	*t = k2;
}

/*
 *           (k1)*                    (k1)*                      
 *              / \                      / \
 *         (k2)*   *A      RR       (k3)*   *A     LL          (k3)*
 *            / \          =>          / \         =>            /  \
 *           *B  *(k3)            (k2)*  *D                 (k2)*    *(k1)
 *              / \                  / \                       / \   / \
 *             *C  *D              B*   *C                   B*  C* *D  *A
 *
 *      LR rotation
 */
static void left_right_rotation(avl_tree_t *t) 
{
	right_right_rotation(&(*t)->left);
	left_left_rotation(t);
}

/*
 *              *(k1)
 *             / \
 *           A*   *(k2)                    *(k2)
 *               / \          =>          / \
 *             B*   *C               (k1)*   *C
 *                   \                  / \   \
 *                    *D               A*  *B  *D
 *
 *        RR rotation
 */
static void right_right_rotation(avl_tree_t *t) 
{
	
	avl_tree_node_t *k1, *k2;

	k1 = *t;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = MAX(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
	k2->height = MAX(HEIGHT(k2->right), k1->height) + 1;

	*t = k2;
}

/*
 *               *(k1)                      *(k1)
 *              / \                        / \
 *            A*   *(k2)       LL        A*   *(k3)         RR               *(k3)
 *                / \          =>            / \            =>             /   \
 *           (k3)*   *B                    C*   *(k2)                 (k1)*     *(k2)
 *              / \                            / \                       / \   / \
 *             *C  *D                        D*   *B                    *A C* *D  *B
 *
 *       RL rotation
 */
static void right_left_rotation(avl_tree_t *t) 
{
	left_left_rotation(&(*t)->right);
	right_right_rotation(t);
}


static avl_tree_node_t *avl_tree_maxinum(avl_tree_t t)
{
	if (t == NULL)
		return NULL;
	while (t->right != NULL)
		t = t->right;
	return t;
}


static avl_tree_node_t *avl_tree_mininum(avl_tree_t t)
{
	if (t == NULL)
		return NULL;

	while (t->left != NULL)
		t = t->left;
	return t;
}
