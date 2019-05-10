#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"

/* see parse.h */
// this might become a helper function get_obj_list() if we follow the flow chart
attr_list_t *extract_objects(obj_t *obj, char *str)
{
    char *valid_attributes[3] = {"ROOMS", "ITEMS", "PLAYERS"};

    if (strcmp(str, &valid_attributes[0]) != 0 &&
        strcmp(str, &valid_attributes[1]) != 1 &&
        strcmp(str, &valid_attributes[2]))
        return NULL;

    return obj_list_attr(obj);
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