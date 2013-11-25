/* bst.c
 * Binary Search Tree with insertion only (atm)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *lchild;
	struct node *rchild;
} node;

node* create(int value)
{
	node *new_node = malloc(sizeof(node));
	new_node->value = value;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

void insert(node *root, node *new_node)
{
	if (new_node->value < root->value) {
		if (root->lchild) {
			insert(root->lchild, new_node);
		} else {
			printf("Inserting %d left of %d\n", new_node->value, root->value);
			root->lchild = new_node;
			return;
		}
	} else {
		if (root->rchild) {
			insert(root->rchild, new_node);
		} else {
			printf("Inserting %d right of %d\n", new_node->value, root->value);
			root->rchild = new_node;
			return;
		}
	}
}


void display(node *root)
{
	printf("%d\n", root->value);
	if (root->lchild)
		display(root->lchild);
	if (root->rchild)
		display(root->rchild);
}

int main()
{
	int value;
	node *root = NULL;
	node *new_node = NULL;

	puts("Insert value of the starting node:");
	scanf("%d", &value);

	root = create(value);

	do {
		puts("Insert next value, or 0 to exit:");
		scanf("%d", &value);

		if (value) {
			new_node = create(value);
			insert(root, new_node);
		}

	} while (value);

	display(root);
	return 0;
}
