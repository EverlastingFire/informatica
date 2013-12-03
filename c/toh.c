/* toh.c
 *
 * Author: Roberto D'Auria
 * Implementation of the Tower of Hanoi using a recursive function.
 * To make it "interactive", remove the comments in the code.
 */

#include <stdio.h>

int TOH(int n, char x, char y, char z);

int main(){
    int n;
    printf("Number of plates: ");
    scanf("%d", &n);

    TOH(n, 'A', 'B', 'C');

    return 0;
}

int TOH(int n, char x, char y, char z)
{
    if (n > 0){
        TOH(n - 1, x, z, y);
        printf("%c -> %c\n", x, y);
        TOH(n - 1, z, y, x);
    }
}
