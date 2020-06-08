/*
 * load_wdz_lzip.c
 * Functions to load the wdz zip archive.
 * 
 * This file contains implementations that are specific to
 * the libzip library.
 * 
 * Other parts of WDZ loading that are independent from the choice of
 * zip library can be found in load_wdz_common.c.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "wdl/load_wdz_internal.h"

// maximum buffer size for json file, in bytes. This is currently set to 2 MiB.
#define MAXBUFSIZE ((zip_int64_t)0x200000)

/* 
 * get_json_obj_from_zip_file_entry 
 * Opens the libzip file handle, parses the JSON string, and 
 * returns the JSON object.
 * 
 * Parameters:
 * - curr_file: The libzip file handle of the file in the archive
 * - entry_name: The full filename (with path) obtained from libzip
 * 
 * Returns:
 * - A json_object corresponding to the whole JSON file
 */
struct json_object *get_json_obj_from_zip_file_entry
(
    zip_file_t *curr_file,
    const char *entry_name
)
{
    if (!curr_file)
    {
        return NULL;
    }
    
    // Don't try to JSON-parse files that don't have a .json extension.
    if (!filename_extension_is("json", entry_name))
    {
        return NULL;
    }

    char *buf = calloc(MAXBUFSIZE, sizeof(char));
    printf("Filename: %s\n", entry_name);
    zip_fread(curr_file, buf, MAXBUFSIZE);

    if (!buf)
    {
        fprintf(stderr, "Opened zip entry but unable to read contents\n");
        return NULL;
    }    

    // buf now contains the raw JSON. Use parser to convert into json obj.
    // print out behind the main chiventure executable for debug and demo.
    printf("%s\n", (char *)buf);
    struct json_object *result = json_tokener_parse((char *)buf);

    free(buf);
    printf("%s\n", result ? "JSON successfully parsed." : "JSON object is null!");
    return result;
}


/* See load_wdz.h */
int populate_objstore_from_wdz
(
    objstore_t *obj_store,
    int *n_jsons, 
    char *wdz_name
)
{
    int open_error_code;

    zip_t *wdz = zip_open(wdz_name, 0, &open_error_code);
    if (!wdz)
    {
        fprintf(stderr, "Unable to open wdz. Error code %d\n", open_error_code);
        *n_jsons = 0;
        return FAILURE;
    }

    zip_int64_t n_entries = zip_get_num_entries(wdz, 0);
    if (n_entries <= 0) // negative number means error, 0 means empty zip
    {
        *n_jsons = 0;
        zip_close(wdz);
        return FAILURE;
    }
    
    zip_int64_t count = 0;
    
    for (zip_int64_t i = 0; i < n_entries; i++) // foreach file in zip,
    {
        zip_file_t *curr_file = zip_fopen_index(wdz, i, 0);
        { // Within the context of this opened entry...
            const char *j_path_and_name = zip_get_name(wdz, i, 0);
            struct json_object *j_obj = 
                get_json_obj_from_zip_file_entry(curr_file, j_path_and_name);
            
            if (j_obj) // This is NULL if the path doesn't end in .json
            {
                load_game_objects_from_json_object(obj_store, j_obj);
                // increment the current number of json files.
                count++;
            }
        }
        zip_fclose(curr_file);
    }

    *n_jsons = count;

    zip_close(wdz);
    
    return SUCCESS;   
}

