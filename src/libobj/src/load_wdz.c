#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "libobj/load.h"

/* Maximum buffer size for json file, in bytes. 
 * This is currently set to 2 MiB. 
 */


/* See load_internal.h */
bool _strip_expected_extension(char *str, char *ext)
{
    // See if this ends in ".*" and get the location
    char *ending_dot = strrchr(str, '.');
    if (ending_dot == NULL)
    {
        return false;
    }

    // See if the extension matches
    bool rc = strcmp(ending_dot + 1, ext) == 0;
    // Since str is allowed to be modified, strip the extension off
    *ending_dot = '\0';

    return rc;
}

/* See load.h */
int load_obj_zip(obj_t *obj, char *wdz_path)
{
    printf("start\n");
    if (obj == NULL || wdz_path == NULL)
    {
        return EXIT_FAILURE;
    }
    printf("openming\n");

    int open_status;    
    zip_t *zip = zip_open(wdz_path, 0, &open_status);
    if (zip == NULL)
    {
        printf("open status: %d\n", open_status);
        return EXIT_FAILURE;
    }
    printf("getting entries\n");

    zip_int64_t n_entries = zip_get_num_entries(zip, 0);
    if (n_entries <= 0) // negative number means error, 0 means empty zip
    {
        zip_close(zip);
        return EXIT_FAILURE;
    }

    printf("n_entries: %ld\n", n_entries);

    for (zip_int64_t i = 0; i < n_entries; i++)
    {
        // Get the name of the file and see if it's a .json file
        zip_file_t *curr_file = zip_fopen_index(zip, i, 0);
        const char *path = zip_get_name(zip, i, 0);
        char name_buf[10 * (MAXLEN_ID + 1)] = { 0 };
        strncpy(name_buf, path, MAX_DEPTH * (MAXLEN_ID + 1) - 1);


        printf("reading\n");
        if (_strip_expected_extension(name_buf, "json") == false)
        {
            // Don't try to load non-json files
            continue;
        }

        printf("cont\n");

        // Pull the json file into memory
        char *json_buf = calloc(MAXBUFSIZE + 1, sizeof(char));
        if (json_buf == NULL)
        {
            return EXIT_FAILURE;
        }
        if (zip_fread(curr_file, json_buf, MAXBUFSIZE) == -1)
        {
            free(json_buf);
            return EXIT_FAILURE;
        }

        // Load the json file into an object at <name_buf>
        for (int p = 0; p < strnlen(name_buf, MAX_DEPTH * (MAXLEN_ID + 1) - 1); p++)
        {
            if (name_buf[i] == '/')
            {
                name_buf[i] == '.';
            }
        }
        obj_t *to_load = obj_get_attr(obj, name_buf, true);
        if (load_obj_json(to_load, json_buf) == EXIT_FAILURE)
        {
            free(json_buf);
            return EXIT_FAILURE;
        }

        free(json_buf);
    }

    return EXIT_SUCCESS;
}
