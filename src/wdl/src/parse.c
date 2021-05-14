#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libobj/obj.h"
#include "libobj/load.h"
#include "wdl/parse.h"

/* get_obj_list()
 * a helper function to load a list of the rooms, items, or players
 *
 * parameters:
 *  - obj: The document object
 *  - str: the attribute asssociated with the desired objects
 *
 * returns:
 *  - a list of objects
 *  - null if attribute does not have associated objects, or if no such attribute exists
 */
obj_t *get_obj_list(obj_t *obj, char *str)
{
    if (strcmp(str, "ROOMS") == 0)
    {
        return obj_get_attr(obj, "ROOMS", false);
    }
    else if (strcmp(str, "ITEMS") == 0)
    {
        return obj_get_attr(obj, "ITEMS", false);
    }
    else if (strcmp(str, "PLAYERS") == 0)
    {
        return obj_get_attr(obj, "PLAYERS", false);
    }
    else
    {
        return NULL;
    }
}

/* see parse.h */
obj_t *extract_objects(obj_t *obj, char *str)
{
    bool valid = false;

    if (obj == NULL)
    {
        return NULL;
    }

    if (strcmp(str, "ROOMS") == 0)
    {
        valid = list_type_check(obj, room_type_check);
    }
    else if (strcmp(str, "ITEMS") == 0)
    {
        valid = list_type_check(obj, item_type_check);
    }

    if (valid == SUCCESS)
    {
        return obj_get_attr(obj, str, false);
    }
    else
    {
        return NULL;
    }
}

/* see parse.h */
obj_t *get_item_actions(obj_t *item)
{
    bool valid = false;

    obj_t *ls = obj_get_attr(item, "actions", false);
    if (ls == NULL)
    {
        return NULL;
    }

    valid = list_type_check(ls, action_type_check);
    if (valid == SUCCESS)
    {
        return ls;
    }
    else
    {
        return NULL;
    }
}