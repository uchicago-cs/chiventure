#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "libobj/load.h"

/* Maximum buffer size for json file, in bytes. 
 * This is currently set to 2 MiB. 
 */
#define MAXBUFSIZE ((zip_int64_t)0x200000)

/* See load_json.h */
int attempt_load_obj_zip_json(obj_t *obj, zip_t *zip_json, int idx)
{
    char *buf = calloc(MAXBUFSIZE, sizeof(char));

    struct json_object *json = json_tokener_parse(json_str);
    int rc = _load_obj_json(obj, json);

    // Frees the json object
    json_object_put(json);

    return rc;
}

int load_wdz(obj_t *obj, char *wdz_path)
{
    int open_status;    
    zip_t *zip = zip_open(wdz_path, 0, &open_status);
    if (zip == NULL)
    {
        return EXIT_FAILURE;
    }

    zip_int64_t n_entries = zip_get_num_entries(zip, 0);
    if (n_entries <= 0) // negative number means error, 0 means empty zip
    {
        zip_close(zip);
        return EXIT_FAILURE;
    }

    for (zip_int64_t i = 0; i < n_entries; i++)
    {
        attempt_load_obj_zip_json(obj, zip, i);

        zip_file_t *curr_file = zip_fopen_index(wdz, i, 0);
        const char *path = zip_get_name(wdz, i, 0);
        char name_buf[]
    }

    return EXIT_SUCCESS;
}
