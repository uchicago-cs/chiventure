#include "common/common.h"
#include <json-c/json.h>
#include "wdl/miniz-zip/zip.h"


// Dummy forward declarations. Will replace with the proper objstore_t
// and obj_t included from the correct modules later.
typedef int objstore_t;
typedef int obj_t;


/* 
 * populate_objstore_from_wdz:
 *  Populates the object store struct by loading from the wdz archive.
 * 
 * Parameters:
 *  - obj_store: The object store hash table to load into
 *  - n_jsons: A pointer where the number of json files 
 *             (game object types) found is stored
 *  - wdz_name: Path and filename of the wdz archive to load
 * 
 * Returns:
 *  - SUCCESS (0) if the loading was successful
 *  - FAILURE (1) if there was an error.
 */
int populate_objstore_from_wdz
(
    objstore_t *obj_store,
    int *n_jsons, 
    char *wdz_name
);

