#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "battle/battle_structs.h"

/** See moves.h */
class_t *new_class(class_type_t cl, char* info, possible_stats_t st, double bonus)
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

/** See moves.h */
int init_class(class_t *class, class_type_t cl, char* info, possible_stats_t st, double bonus)
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
