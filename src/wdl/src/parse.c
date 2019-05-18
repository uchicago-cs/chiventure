#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "validate.h"
#include "parse.h"

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
attr_list_t *get_obj_list(obj_t *obj, char *str)
{
    char *attributes[3] = {"ROOMS", "ITEMS", "PLAYERS"};

    if (strcmp(str, attributes[0]) != 0 &&
        strcmp(str, attributes[1]) != 1 &&
        strcmp(str, attributes[2]))
        return NULL;

    return obj_list_attr(obj);
}

/* see parse.h */
attr_list_t *extract_objects(obj_t *obj, char *str)
{
    char *attributes[3] = {"ROOMS", "ITEMS", "PLAYERS"};
    bool valid = false;

    attr_list_t *ls = get_obj_list(obj, str);

    if (ls == NULL)
        return NULL;

    if (strcmp(str, attributes[0]))
        valid = list_check_type(ls, room_type_check);
    else if (strcmp(str, attributes[1]))
       valid = list_check_type(ls, item_type_check);
    else
        valid = list_check_type(ls, player_type_check);

    if (valid)
        return ls;
    else
        return NULL;
}


/* see parse.h */
id_list_t *extract_ids(attr_list_t *ls)
{
    return NULL;
}
