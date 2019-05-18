/*
 * Header file for wdl/yaml parsing functions and related utilities
 */

#ifndef INCLUDE_PARSE_H
#define INCLUDE_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

/*
 * extract_objects()
 * extracts the a list of objects associated with an attribute of the primary object;
 * used to get a list of rooms, items, and players
 * note that this function will only return if it determines all the objects are valid
 *
 * Parameters:
 *  - obj: The document object
 *  - str: the attribute asssociated with the desired objects
 *
 * Returns:
 *  - a list of objects
 *  - null if attribute does not have associated objects, or if no such attribute exists
 */
attr_list_t *extract_objects(obj_t *obj, char *str);


/*
 * extract_ids()
 * gets the ids of a list of room, item, or player objects
 *
 * parameters:
 *  - ls: a list of room,s items, or players
 *
 * returns:
 *  - a list of ids, more specifically, a doubly linked list of strings
 */
id_list_t *extract_ids(attr_list_t *ls);

#endif /* INCLUDE_PARSE_H */
