#include <stdbool.h>
#include "libobj/obj.h"

#ifndef INCLUDE_LOAD_JSON_H
#define INCLUDE_LOAD_JSON_H

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
