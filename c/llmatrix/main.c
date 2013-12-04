#include <stdio.h>
#include <math.h>

#include "llmatrix.h"

int main()
{
    int n, dim;
    node *start;

    do {
        puts("Insert a number");
        scanf("%d", &n);
        dim = sqrt(n);
    } while (dim * dim != n);

    start = create_matrix(n);
    shuffle(start, dim);
    play(start);

    return 0;
}