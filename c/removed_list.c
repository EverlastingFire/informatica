
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *prev;
	struct node *next;
} node;

typedef struct deleted_node {
	int value;
	struct deleted_node *next;
} deleted_node;

node* create_node(int n)
{
	node *i = malloc(sizeof(node));
	i->value = n;
	i->prev = NULL;
	i->next = NULL;
	return i;
}

deleted_node* create_deleted_node(int n)
{
	deleted_node *i = malloc(sizeof(deleted_node));
	i->value = n;
	i->next = NULL;
	return i;
}

void display(node *start)
{
	node *i = start;
	for (; i; i = i->next ) {
		printf("%d\n", i->value);
	}
}

void display_deleted(deleted_node *start)
{
	deleted_node *i = start;
	for (; i; i = i->next ) {
		printf("%d\n", i->value);
	}
}

node* delete(node *first_node, int to_delete)
{
	printf("delete :v\n");
	node *i = first_node;
	node *tmp = NULL; /* puntatore temporaneo */

	if (!i->prev && !i->next) { /* caso speciale in cui ci sia un solo nodo */
		printf("unico nodo\n");
		if (i->value == to_delete)
		{
			free(i);
			return NULL;
		} else {
			return i;
		}
	}

	printf("while\n");
	while(i) {
		if (i->value == to_delete) {
			printf("Trovato!\n");
			if(i->prev && i->next) { /* nodo intermedio */
				printf("intermedio\n");
				i->prev->next = i->next; /* collega il precedente col successivo */
				i->next->prev = i->prev; /* collega il successivo col precedente */
				tmp = i->next;
				free(i);
				i = tmp;
			}

			if (!i->prev) { /* primo nodo */
				printf("primo\n");
				i->next->prev = NULL;

				tmp = i->next;
				free(i);
				i = tmp;

				first_node = i;
			}

			if(!i->next) { /* ultimo nodo */
				printf("ultimo\n");
				i->prev->next = NULL;
				free(i);
			}
		} else {
			i = i->next;
		}
	}

	return first_node;
}

int main()
{
	node *first = NULL; /* puntatore al primo nodo della lista */
	node *prev = NULL;  /* puntatore al nodo precedente */
	node *new = NULL;   /* puntatore al nuovo nodo creato */

	deleted_node *first_deleted = NULL;
	deleted_node *prev_deleted = NULL;
	deleted_node *new_deleted = NULL;

	int n;

	do{
		puts("inserisci numero o inserisci 0 per terminare: ");
		scanf("%d" , &n);
		if (n) {
			new = create_node(n);

			if (first) {    /* se non è la prima iterazione */
				prev->next = new;
				new->prev = prev;
			} else {
				first = new;    /* first punta al primo elemento della lista */
			}

			prev = new;
		}

	}while (n);

	prev = NULL;

	do{
		puts("inserisci il numero che vuoi eliminare o inserisci 0 per terminare: ");
		scanf("%d" , &n);
		if (n) {
			first = delete(first, n);

			new_deleted = create_deleted_node(n);

			if (prev_deleted) {
				prev_deleted->next = new_deleted;
			} else {
				first_deleted = new_deleted;
			}

			prev_deleted = new_deleted;
		}

	}while (n);

	puts("\nla prima lista e': ");
	display(first);

	puts("\nla lista degli eliminati e': ");
	display_deleted(first_deleted);

	return 0;
}