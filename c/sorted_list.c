#include <stdio.h>
#define ASIZE 10

typedef struct list{
    int value;
    struct list *next;
} list;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int *arr, int len)
{
    int i;
    int top = len - 1;
    while (top > 0) {
        for (i = 0; i < top; i++) {
            if (arr[i] > arr[i + 1])
                swap(arr + i, arr + i + 1); // &arr[i], &arr[i+1]
        }
        top--;
    }
}

list* create(int value)
{
    list *n = malloc(sizeof(list));
    n->value = value;
    n->next = NULL;
    return n;
}

int main()
{
    list *first = NULL;
    list *prev = NULL;
    list *new_el = NULL;
    int numbers[ASIZE];
    int i;

    for (i = 0; i < ASIZE; i++) {
        printf("Next number: ");
        scanf("%d", numbers + i); // &numbers[i]
    }

    bubblesort(numbers, ASIZE);

    for (i = 0; i < ASIZE; i++) {
        new_el = create(numbers[i]);
        if (prev) {
            prev->next = new_el;
        } else {
            first = new_el;
        }

        prev = new_el;
    }

    while (first) {
        printf("%d\n", first->value);
        first = first->next;
    }

    return 0;
}