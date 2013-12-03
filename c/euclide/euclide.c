/* Author: Roberto D'Auria
 * Implementation of the (Extended) Euclidean Algorithm
 *
 * euclide.c
 */

#include <stdio.h>

void shift_up(int mem_table[3][5])
{
    int i;
    int j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            mem_table[i][j] = mem_table[i+1][j];
        }
    }
}

void print_row(int n, int mem_table[3][5])
{
    int i;
    for (i = 0; i < 5; i++) {
        printf("%10d\t\t", mem_table[n][i]);
    }
    printf("\n");
}

int MCD(int n1, int n2, int mem_table[3][5], int *x, int *y)
{
    /* Fill the first two rows */
    mem_table[0][3] = 1;
    mem_table[1][0] = n1;
    mem_table[1][1] = n2;
    mem_table[1][2] = n1 / n2;
    mem_table[1][3] = 0;
    mem_table[1][4] = 1;

    /* Here we use pointers to alias specific positions in the table */
    int *s2 = &mem_table[0][3];
    int *t2 = &mem_table[0][4];

    int *a1 = &mem_table[1][0];
    int *b1 = &mem_table[1][1];
    int *q1 = &mem_table[1][2];
    int *s1 = &mem_table[1][3];
    int *t1 = &mem_table[1][4];

    int *a = &mem_table[2][0];
    int *b = &mem_table[2][1];
    int *s = &mem_table[2][3];
    int *t = &mem_table[2][4];

    *a = n1;
    *b = n2;

    while (*b != 0) {

        *q1 = *a / *b;
        *a = *b1;
        *b = *a1 % *b1;

        *s = *s2 - (*q1) * (*s1);
        *t = *t2 - (*q1) * (*t1);

        print_row(0, mem_table);
        print_row(1, mem_table);
        print_row(2, mem_table);
        printf("\n-----------------\n");

        shift_up(mem_table);
    }

    *x = *s2;
    *y = *t2;
    return *a;
}
