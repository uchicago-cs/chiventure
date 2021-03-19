#ifndef INCLUDE_LOAD_JSON_H
#define INCLUDE_LOAD_JSON_H

#include <stdbool.h>
#include <json-c/json.h>
#include "libobj/obj.h"


/*
 * Do not call this function directly. This is exposed
 * only for testing purposes
 * 
 * Recursive helper for load_obj_json. 
 * 
 * Parameters:
 *  - path: The path to the JSON file
 * 
 * Returns:
 *  - An obj containing the JSON file's data
 *  - NULL on error
 */
int _load_obj_json(obj_t *parent, struct json_object *json);

/*
 * Loads a JSON file into an object
 * 
 * Parameters:
 *  - path: The path to the JSON file
 * 
 * Returns:
 *  - An obj containing the JSON file's data
 *  - NULL on error
 */
obj_t *load_obj_json(char *path);


#endif /* INCLUDE_LOAD_JSON_H */
