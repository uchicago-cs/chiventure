#ifndef LOADWDZ_INTERNAL_HEADER
#define LOADWDZ_INTERNAL_HEADER

#include "common/common.h"
#include <json-c/json.h>

#ifdef _LOADWDZ_USING_MINIZ
#include "wdl/miniz-zip/zip.h"
#else
#include <zip.h>
#endif

#include "load_wdz.h" // Include the public header

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

int load_game_objects_from_json_object
(
    objstore_t *obj_store, 
    json_object *j_obj,
    const char *j_name
);

#endif /* LOADWDZ_INTERNAL_HEADER */
