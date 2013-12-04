#ifndef LLMATRIX_H
#define LLMATRIX_H

/* Node struct */
typedef struct node {
    int value;
    struct node *top;
    struct node *right;
    struct node *bottom;
    struct node *left;
} node;

/* Function prototypes */
node* create_node(int value);
node* create_matrix(int n);
node *get_element_by_position(node *start, int row, int col);
node* search(node *start, int to_find);

void shuffle(node *start, int dim);
void swap(node *n1, node *n2);
void display_matrix(node *start);
void play(node *start);

#endif /* LLMATRIX_H */