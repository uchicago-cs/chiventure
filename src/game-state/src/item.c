/* Implementations of the object struct */
#include <stdio.h>
#include <stdlib.h.h>
#include "item.h"

item_t *item_new();

int add_item_to_hash(all_items_t all_items, int item_id, item_t *item) {
    item_t *s;
    HASH_FIND_INT(all_items, &item_id, s);
    if (s != NULL) {
        /* WARNING */
        /* SHOULD BE ABLE TO SUPPORT STACKING MULTIPLE OBJECTS */
        printf("FATAL: item_id already used!\n");
        exit(0);
    }
    HASH_ADD_INT(all_items, item_id, s);
    return 1;
}

int item_init(char *item_id, char *short_desc, char *long_desc)
{

    /* TO DO */

    return 0;
}

/* the following functions retrieve specific information from desired object
in anticipation of supporting player demands */
/* will add function basics to ensure compilation */


char *get_id(item_t obj)
{

    /* TO DO */

    return NULL;
}


char *get_short_desc(item_t obj)
{

    /* TO DO */

    return NULL;
}


char *get_long_desc(object_t obj)
{

    /* TO DO */

    return NULL;
}


int *get_obj_type(enum object_type_t obj_t)
{

    /* TO DO */

    return NULL;
}


int take_object(object_t obj)
{

    /* TO DO */

    return 0;
}
