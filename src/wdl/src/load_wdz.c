#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "load_wdz.h"

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
bool filename_extension_is(const char *ext, const char *str)
{
    char *dot_and_ext = strrchr(str, '.');
    if (dot_and_ext) // if there was a period
    {
        return (strncmp(dot_and_ext + 1, ext, strlen(ext)) == 0);
    }
}


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


int load_game_objects_from_json_object
(
    objstore_t *obj_store, 
    json_object *j_obj,
    const char *j_name
)
{
    json_object *j_game_objs_j_arr;
    json_object_object_get_ex(j_obj, j_name, &j_game_objs_j_arr);
    if (json_object_is_type(j_game_objs_j_arr, json_type_array))
    {
        int n_objects = json_object_array_length(j_game_objs_j_arr);
        for (int i = 0; i < n_objects; i++) // for each json_object in the array
        {
            json_object *j_game_obj = json_object_array_get_idx(j_game_objs_j_arr, i);
            obj_t *game_obj = convert_j_obj_to_game_obj(j_game_obj, j_name);
            // ^^^ waiting for obj_t implementation before we can write this conversion! 
            if (!game_obj) 
            {
                return FAILURE;
            }
            add_objstore(obj_store, game_obj);
        }
        return SUCCESS;
    }
    return FAILURE;
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
            const char *j_name = zip_entry_name(wdz);
            if (j_obj)
            {
                load_game_objects_from_json_object(obj_store, j_obj, j_name);
                // increment the current number of json files.
                count++;
            }
        }
        zip_entry_close(wdz);
    }

    *n_jsons = count;

    return SUCCESS;   
}

