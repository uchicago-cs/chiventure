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

/*
 * Do not call this function directly. This is exposed
 * only for testing purposes.
 * 
 * Helper for load_obj_zip. Sees if a path ends in an expected
 * file extension. If it ends in any file extension, strips the
 * extension
 * 
 * Parameters:
 *  - str: A string containing the path to examine. Will be modified
 *  - ext: The expected file extension
 * 
 * Returns:
 *  - true if the path ends in the expected extension, false otherwise
 *
 * Side effect:
 *  - Strips the file extension if *any* exist
 *  - Strips off trailing "DEFAULT" if it exists and replaces with "."
 */
bool _strip_expected_extension(char *str, char *ext);


#endif /* INCLUDE_LOAD_JSON_H */
