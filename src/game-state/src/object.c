#include "object.h"

object_t *object_new();

int add_object_to_hash(all_objects_t all_objects, int object_id, object_t *object) {
    object_t *s;
    HASH_FIND_INT(all_objects, &object_id, s);
    if (s != NULL) {
        /* WARNING */
        /* SHOULD BE ABLE TO SUPPORT STACKING MULTIPLE OBJECTS */
        printf("FATAL: object_id already used!\n");
        exit(0);
    }
    HASH_ADD_INT(all_objects, object_id, s);
    return 1;
}

int object_init(char *object_id, char *short_desc, char *long_desc)
{

    /* TO DO */

    return 0;
}

/* the following functions retrieve specific information from desired object
in anticipation of supporting player demands */
/* will add function basics to ensure compilation */


char *get_id(object_t obj)
{

    /* TO DO */

    return NULL;
}


char *get_short_desc(object_t obj)
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
