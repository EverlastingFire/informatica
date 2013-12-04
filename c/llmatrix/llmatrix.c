#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "llmatrix.h"

#define DEBUG 0

/* Function definitions */

node* create_node(int value)
{
    node *new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->top = NULL;
    new_node->right = NULL;
    new_node->bottom = NULL;
    new_node->left = NULL;
    return new_node;
}

node* create_matrix(int n)
{
    int i;
    int dim;
    int row;
    int column;
    node *first;
    node *new_node;
    node *to_link;


    dim = sqrt(n);
    first = NULL;

    for (i = 0; i < n; i++)
    {
        /* Calculate row and column with a bit of modular arithmetic
         * I don't like O(n^2) sort of things. */
        row = i / dim;
        column = i % dim;

        new_node = create_node(i);

        if (!first)
            first = new_node;

        if (row != 0) {
            /* Set the top/bottom links */
            to_link = get_element_by_position(first, row - 1, column);
            new_node->top = to_link;
            to_link->bottom = new_node;

            /* A bit of debugging... */
            if (DEBUG)
                printf("Linking %d with %d and vice-versa\n", new_node->value,
                        to_link->value);
        }

        if (column != 0) {
            /* Set the left/right links */
            to_link = get_element_by_position(first, row, column - 1);
            new_node->left = to_link;
            to_link->right = new_node;
            if (DEBUG)
                printf("Linking %d with %d and vice-versa\n", new_node->value,
                       to_link->value);
        }
    }

    return first;
}

node *get_element_by_position(node *start, int row, int col)
{
    int i;
    node *current = start;

    for (i = 0; i < row; i++) {
        current = current->bottom;
    }

    for (i = 0; i < col; i++) {
        current = current->right;
    }

    return current;
}

node* search(node *start, int to_find)
{
    node *row_start = start;
    node *current = start;

    while (current->value != to_find) {
        if (current->right) {
            current = current->right;
        } else {
            if (row_start->bottom) {
                current = row_start->bottom;
                row_start = current;
            }
        }
    }

    return current;
}

void shuffle(node *start, int dim)
{
    node *empty = start; /* empty is the node with value 0 */
    node *dest = NULL;
    int i, n;

    n = dim * dim;

    /* Init the PRNG */
    srand(time(NULL));

    /* Randomly choose how many times to swap values
     * (between n*5 times and n*9 times) */
    int n_swaps = n * (rand() % 5 + 5);
    if (DEBUG)
        printf("Number of swaps: %d\n", n_swaps);

    for (i = 0; i < n_swaps; i++) {
        /* Find a node which value is between 1 and n-1 */
        dest = search(start, rand() % (n - 1) + 1);

        swap(empty, dest);
        empty = dest; /* update the ptr to the node with value 0 */
    }
}

void swap(node *n1, node *n2)
{
    if (DEBUG)
        printf("Swapping %d and %d\n", n1->value, n2->value);
    int temp = n1->value;
    n1->value = n2->value;
    n2->value = temp;
}

void display_matrix(node *start)
{
    node *line_start = start;
    node *current = start;
    printf("Matrix:\n");
    do {
        printf("%-5d", current->value);
        if (current->right) {
            current = current->right;
        } else if (line_start->bottom) {
            printf("\n");
            current = line_start->bottom;
            line_start = current;
        } else {
            current = NULL;
        }
    } while (current);
    printf("\n");
}

void play(node *start)
{
    node *position = search(start, 0);
    char n[2];
    do {
        display_matrix(start);
        printf("Select where to move (wasd): ");
        scanf("%s", n);

        switch (n[0]) {
        case 'w':
            if (position->top != NULL) {
                swap(position, position->top);
                position = position->top;
            }
            break;
        case 'a':
            if (position->left) {
                swap(position, position->left);
                position = position->left;
            }
            break;
        case 's':
            if (position->bottom) {
                swap(position, position->bottom);
                position = position->bottom;
            }
            break;
        case 'd':
            if (position->right) {
                swap(position, position->right);
                position = position->right;
            }
            break;
        }
    } while (1); /* TODO: condition? */
}