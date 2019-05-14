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

    if (strcmp(str, &attributes[0]) != 0 &&
        strcmp(str, &attributes[1]) != 1 &&
        strcmp(str, &attributes[2]))
        return NULL;

    return obj_list_attr(obj);
}

/* see parse.h */
attr_list_t *extract_objects(obj_t *obj, char *str)
{
    attr_list_t *ls = get_obj_list(obj, str);
    return ls;
}


/* make_char_id()
 * a helper function for extract_ids();
 * used to add a char id to the id list
 *
 * parameters:
 *  - obj: the object for which to get the id
 *
 * returns:
 *  - a single id item to be added to the list by extract_ids()
 *
attr_list_t *make_char_id(obj_t *obj)
{

}*/


/* make_str_id()
 * a helper function for extract_ids();
 * used to add a str id to the id list
 *
 * parameters:
 *  - obj: the object for which to get the id
 *
 * returns:
 *  - a single id item to be added to the list by extract_ids()
 *
attr_list_t *make_str_id(obj_t *obj)
{
    
}*/


/* see parse.h */
id_list_t *extract_ids(attr_list_t *ls)
{
    return NULL;
}