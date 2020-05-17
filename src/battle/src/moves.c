#include "../include/structs.h"
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/** See moves.h */
int init_class(class_t *class, enum class cl, char* info, enum stats st, double bonus)
{
    assert(class != NULL);
    assert(info != NULL);

    class->cl = cl;

    class->info = (char*) malloc(sizeof(char) * 100);
    strcpy(class->info, info);

    class->st = st;

    class->bonus = bonus;

    return 0;
}

/** See moves.h */
class_t *new_class(enum class cl, char* info, enum stats st, double bonus)
{
    class_t *class = (class_t*) malloc(sizeof(class_t));
    int rc;

    if(class == NULL)
    {
        fprintf(stderr,"Could not allocate memory\n");
        return NULL;
    }

    rc = init_class(class, cl, info, st, bonus);

    if(rc != 0)
    {
        fprintf(stderr,"Could not initialize class\n");
        return NULL;
    }

    return class;
}


int main()
{
    //Creates test bard class
    char* bard_des = "Charismatic, always has a joke, song, or moving speech ready";
    class_t *test_bard = new_class(0, bard_des, 3, 2.0);

    //Creates test cleric class
    char* cleric_des = "Fueled by divine inspiration, devout to the craft";
    class_t *test_cleric = new_class(1, cleric_des, 1, 2.0);

    //Creates test paladin class
    char* paladin_des = "Driven and committed to justice";
    class_t *test_paladin = new_class(2, paladin_des, 2, 2.0);

    //Creates test wizard class
    char* wizard_des = "Draws power from nature";
    class_t *test_wizard = new_class(3, wizard_des, 0, 2.0);

    printf("Success\n");
}
