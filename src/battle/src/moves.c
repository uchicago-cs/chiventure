#include "../include/structs.h"
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int init_class(class_t *class, enum class cl, char* info, enum stats st, int bonus)
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


class_t *new_class(enum class cl, char* info, enum stats st, int bonus)
{
    class_t *class = (class_t*) malloc(sizeof(class_t));
    int rc;

    if(class == NULL)
    {
        fprintf(stderr,"Could not allocate memory\n");
        return NULL;
    }

    rc = init_class(class, cl, info, st, bonus);

    if(rc != 1)
    {
        fprintf(stderr,"Could not initialize class\n");
        return NULL;
    }

    return class;
}

//Charismatic, always has a joke, song, or moving speech ready

/**

class struct should have
    -enum class
    -char *description
    -enum stat (speed, dex, strength, intelligence)
    -int amount modified

**/

//enum class{bard, cleric, paladin, wizard};

int main()
{
    printf("MEOW\n");
}
