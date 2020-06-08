/* 
 * See demo-functions.h for more information
 */

#include "demo-functions.h"

/* See demo-functions.h */
void class_show(class_t* c)
{
    if (c == NULL)
    {
        fprintf(stderr, "Cannot show information of a NULL class.\n");
        exit(1);
    }
        printf("%s Class:\n", c->name);
        printf("    Short Description: %s\n", c->shortdesc);
        printf("    Long Description: %s\n", c->longdesc);
}

/* See demo-functions.h */
void list_class_show(move_list_t* m)
{
    if (m == NULL)
    {
        fprintf(stderr, "Cannot show information of a NULL movelist.\n");
        exit(1);
    }

    move_list_t* tmp;

    DL_FOREACH(m, tmp)
    {   
        class_show(tmp->c);
        printf("    Special Skill: %s\n", tmp->spell);
        printf("    Skill Damage: %d\n", tmp->damage);
        printf("    Skill id: %d\n", tmp->id);
    }
}
