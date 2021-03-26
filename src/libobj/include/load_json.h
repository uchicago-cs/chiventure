#ifndef INCLUDE_LOAD_JSON_H
#define INCLUDE_LOAD_JSON_H

#include <stdbool.h>
#include <json-c/json.h>
#include "libobj/obj.h"


/*
 * Do not call this function directly. This is exposed
 * only for testing purposes. Use load_obj_json instead
 * 
 * Recursive helper for load_obj_json. 
 * 
 * Parameters:
 *  - path: The path to the JSON file
 * 
 * Returns:
 *  - EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int _load_obj_json(obj_t *parent, struct json_object *json);


#endif /* INCLUDE_LOAD_JSON_H */
