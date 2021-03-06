/* vanishing_island.c */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *opens;
    char *closes;
    struct island *next;
} island;

island* create(char *name)
{
    island *i = malloc(sizeof(island));
    i->name = name;
    i->opens = "09:00";
    i->closes = "17:00";
    i->next = NULL;
    return i;
}

void display(island *start)
{
    island *i = start;
    for (; i != NULL; i = i->next) {
        printf("Name: %s open %s-%s\n", i->name, i->opens, i->closes);
    }
}

int main()
{
    char name[80];
    fgets(name, 80, stdin);
    island *island0 = create(name);
    fgets(name, 80, stdin);
    island *island1 = create(name);
    island0->next = island1;
    display(island0);
    return 0;
}