/* 
 * Flag to use miniz-based zip library for this file.
 * See the common header load_wdz.h
 */
#define _LOADWDZ_USING_MINIZ

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "load_wdz_internal.h"


struct json_object *get_json_obj_from_entryopened_wdz
(
    struct zip_t *wdz
)
{
    if (!wdz)
    {
        return NULL;
    }
    
    // Don't try to JSON-parse files that don't have a .json extension.
    if (!filename_extension_is("json", zip_entry_name(wdz)))
    {
        return NULL;
    }

    void *buf;
    size_t bufsize;
 
    zip_entry_read(wdz, &buf, &bufsize);

    if (!buf)
    {
        fprintf(stderr, "Opened zip entry but unable to read contents");
        return NULL;
    }    

    // buf now contains the raw JSON. Use parser to convert into json obj.
    struct json_object *result = json_tokener_parse((char *)buf);

    // buf was allocated inside zip_entry_read, so now we free it
    free(buf);

    return result;
}


int populate_objstore_from_wdz
(
    objstore_t *obj_store,
    int *n_jsons, 
    char *wdz_name
)
{
    struct zip_t *wdz = zip_open(wdz_name, ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
    if (!wdz)
    {
        fprintf(stderr, "Unable to open wdz zip archive\n");
        *n_jsons = 0;
        return FAILURE;
    }

    int n_entries = zip_total_entries(wdz);
    if (n_entries <= 0) // negative number means error, 0 means empty zip
    {
        *n_jsons = 0;
        return FAILURE;
    }
    
    int count;
    
    for (int i = 0; i < n_entries; i++) // foreach json file,
    {
        zip_entry_openbyindex(wdz, i);
        { // Within the context of this opened entry...
            struct json_object *j_obj = get_json_obj_from_entryopened_wdz(wdz);
            const char *j_path_and_name = zip_entry_name(wdz);
            if (j_obj)
            {
                load_game_objects_from_json_object(obj_store, j_obj, j_path_and_name);
                // increment the current number of json files.
                count++;
            }
        }
        zip_entry_close(wdz);
    }

    *n_jsons = count;
    zip_close(wdz);
    return SUCCESS;   
}

