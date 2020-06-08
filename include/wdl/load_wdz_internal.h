#ifndef LOADWDZ_INTERNAL_HEADER
#define LOADWDZ_INTERNAL_HEADER

#include "common/common.h"
#include <json-c/json.h>

#include <zip.h>

#include "load_wdz.h" // Re-export the public header for internal use as well

/* 
 * filename_extension_is: Checks if a filename string has a certain extension
 * 
 * parameters:
 *  - ext: the extension string to check. For instance, "json" or "png"
 *  - str: the filename string to check for extension.
 * 
 * returns:
 *  - true if the filename contains the extension
 *  - false otherwise.
 */
bool filename_extension_is(const char *ext, const char *str);


/* 
 * load_game_objects_from_json_object
 * Scans through the parsed JSON object and puts all the game objects found
 * into the object store hash table.
 * 
 * Parameters:
 * - obj_store: the object store hash table
 * - j_obj: the top-level JSON object to read from. This is the top-level JSON
 *          dictionary whose only key is the name of the JSON file
 *          it's in. For example, {"items": [...]} in items.json
 * - j_name: the name of that key. For the example above this would be "items".
 *          Note: We could have actually just looped through all json objects
 *              in this file to find the type, but 
 */
int load_game_objects_from_json_object
(
    objstore_t *obj_store, 
    json_object *j_obj
);

#endif /* LOADWDZ_INTERNAL_HEADER */
