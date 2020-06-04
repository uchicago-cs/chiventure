/* 
 * See demo-functions.h for more information
 */

#include "demo-functions.h"

void class_show(move_list_t* m)
{
    if (m == NULL)
    {
        fprintf(stderr, "Cannot show information of a NULL movelist.\n");
        exit(1);
    }
    move_list_t* tmp;
    DL_FOREACH(m, tmp)
    {
        fprintf(stdout, "Class info:\n");
        frpintf(stdout, "    Name: %s\n", tmp->c->name);
        fprintf(stdout, "    Short Description: %s\n", tmp->c->shortdesc);
        fprintf(stdout, "    Long Description: %s\n", tmp->c->longdesc);
        fprintf(stdout, "    Special Skill: %s\n", tmp->spell);
        fprintf(stdout, "    Skill Damage: %d\n", tmp->damage);
        frpintf(stdout, "    Skill id: %d\n", tmp->id);
    }
}