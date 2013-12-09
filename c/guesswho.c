#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 30
#define PEOPLE 5
#define DEBUG 1

const char *COLORS[] = {"grey", "brown", "black"};
const char *YESNO[] = {"NO", "YES"};

/* hair and eyes could be used as the index of an array of colors */
typedef struct person {
    char *name;
    int hair;       /* values: 0, 1, 2 */
    int eyes;       /* values: 0, 1, 2 */
    int sunglasses; /* values: 0, 1 */
    int beard;      /* values: 0, 1 */
    struct person *next;
} person;

person* create(char *name, int hair, int eyes, int sunglasses, int beard);
person *generate_combination(char *pname, int index);
person* get_by_index(person *first, int index);
void print_people(person *first);
void play(person *first, person *target);

int main()
{
    int i;
    int seed;
    char name[BUFSIZE];
    person *first = NULL;
    person *prev = NULL;
    person *new_person = NULL;
    person *target = NULL;

    srand(time(NULL));
    seed = rand() % 36;

    printf("Guess Who? :v\n");

    for (i = 0; i < PEOPLE; i++) {
        printf("Name of person #%d: ", i);
        fgets(name, BUFSIZE, stdin);
        name[strlen(name) - 1] = '\0';

        new_person = generate_combination(name, seed);
        seed++;

        if (!prev) { /*set the first person */
            first = new_person;
        } else { /* link previous person to the current one */
            prev->next = new_person;
        }

        prev = new_person;
    }

    // Select a random person
    target = get_by_index(first, rand() % PEOPLE);

    if (DEBUG)
        printf("Target: %s\n", target->name);

    play(first, target);

    return 0;
}

person* create(char *name, int hair, int eyes, int sunglasses, int beard)
{
    person *new_person = malloc(sizeof(person));
    new_person->name = name;
    new_person->hair = hair;
    new_person->eyes = eyes;
    new_person->sunglasses = sunglasses;
    new_person->beard = beard;
    new_person->next = NULL;
    return new_person;
}

person *generate_combination(char *pname, int index)
{
    char *name = strdup(pname);
    int hair, eyes, sunglasses, beard;

    person *new_person;

    hair = (index / 12) % 3;
    eyes = (index / 4) % 3;
    sunglasses = (index / 2) % 2;
    beard = index % 2;

    if (DEBUG)
        printf("Generating #%d:\nH: %d\nE: %d\nS: %d\nB: %d\n\n",
                index, hair, eyes, sunglasses, beard);

    new_person = create(name, hair, eyes, sunglasses, beard);
    return new_person;
}

person* get_by_index(person *first, int index)
{
    int i;
    person *current;
    current = first;

    for (i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}

void print_people(person *first)
{
    person *current = first;
    while (current) {
        printf("%s: H: %d (%s), E: %d (%s), S: %d (%s), B: %d (%s)\n",
                current->name, current->hair, COLORS[current->hair],
                current->eyes, COLORS[current->eyes], current->sunglasses,
                YESNO[current->sunglasses], current->beard,
                YESNO[current->beard]);
        current = current->next;
    }
}

void play(person *first, person *target)
{
    int found;
    char key;
    int value;
    char name[BUFSIZE];

    found = 0;

    print_people(first);

    do {
        printf("Key? ");
        scanf("%c%*c", &key);

        switch (key) {
        case 'N':
            printf("Guess the name: ");
            scanf("%s", name);
            if (DEBUG)
                printf("%s == %s ?\n", target->name, name);

            if (!strcmp(target->name, name))
                found = 1;
            break;
        case 'H':
            printf("Value? ");
            scanf("%d%*c", &value);
            if (target->hair == value)
                printf("Yep.\n");
            else
                printf("No.\n");
            break;
        case 'E':
            printf("Value? ");
            scanf("%d%*c", &value);
            if (target->eyes == value)
                printf("Yep.\n");
            else
                printf("No.\n");
            break;
        case 'S':
            printf("Value? ");
            scanf("%d%*c", &value);
            if (target->sunglasses == value)
                printf("Yep.\n");
            else
                printf("No.\n");
            break;
        case 'B':
            printf("Value? ");
            scanf("%d%*c", &value);
            if (target->beard == value)
                printf("Yep.\n");
            else
                printf("No.\n");
            break;
        default:
            printf("Invalid key, retry. Valid keys are: H E S B.\n");
            break;
        }
    } while (!found);

    printf("You won. :v\n");
}