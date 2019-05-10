#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include "validate.h"

/* see parse.h */
attr_list_t *extract_objects(obj_t *obj, char *str)
{
    char *valid_attributes[3] = {"ROOMS", "ITEMS", "PLAYERS"};

    if (strcmp(str, &valid_attributes[0]) != 0 &&
        strcmp(str, &valid_attributes[1]) != 1 &&
        strcmp(str, &valid_attributes[2]))
        return NULL;

    return obj_list_attr(obj);
}

/* list_type_check()
 * a function to to atomate type checking,
 * used before running extract_id() from parse.h
 * 
 * parameters:
 *  - ls: a list of objects
 *  - a function pointer to a type checking function
 *
 * returns:
 *  - true if all objects in the list pass the type checker
 *  - false if else
 */
bool list_type_check(attr_list_t *ls, bool(*validate)(obj_t*))
{
    if (ls == NULL)
        return false; // refer to flow chart

    bool result = true;
    attr_list_t *curr = ls;

    while(curr != NULL) {
        result = (result && (*validate)(curr->obj));
        curr = curr->next;
    }

    return result;
}