#ifndef INCLUDE_LOAD_H
#define INCLUDE_LOAD_H

#include <stdbool.h>
#include <json-c/json.h>
#include <zip.h>
#include "libobj/obj.h"


/* Maximum buffer size for json file, in bytes. 
 * This is currently set to 2 MiB. 
 */
#define MAXBUFSIZE (0x200000)

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

/*
 * Loads a zipped JSON file into an obj
 * 
 * Parameters:
 *  - obj: The object to load data into
 *  - zip_json: The path to the wdz file
 * 
 * Returns:
 *  - EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int load_obj_zip(obj_t *obj, char *wdz_path);


#endif /* INCLUDE_LOAD_H */
