#ifndef LOADWDZ_PUBLIC_HEADER
#define LOADWDZ_PUBLIC_HEADER

#include <stdlib.h>
#include <stdio.h>

#include "wdl/objstore.h"

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
    objstore_t **obj_store,
    int *n_jsons, 
    char *wdz_name
);

#endif /* LOADWDZ_PUBLIC_HEADER */
