#ifndef INCLUDE_LOAD_H
#define INCLUDE_LOAD_H

#include <stdbool.h>
#include <json-c/json.h>
#include "libobj/obj.h"

/*
 * Loads a string containing JSON into an obj
 * 
 * Parameters:
 *  - obj: The object to load data into
 *  - json_str: The string containing the JSON
 * 
 * Returns:
 *  - EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int load_obj_json(obj_t *obj, char *json_str);


#endif /* INCLUDE_LOAD_H */
