#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "libobj/load.h"

obj_t *load_obj_store(char *path)
{
    // See if this ends in ".*" and get the location
    char *ending_dot = strrchr(path, '.');
    if (ending_dot == NULL)
    {
        return NULL;
    }

    int len = strnlen(path, PATH_MAX);
    obj_t *obj = obj_new("doc");
    int rc = EXIT_FAILURE;

    // Parse into an obj depending on the file extension
    if (strncmp(ending_dot + 1, "wdl", len) == 0)
    {
        char json_buf[MAXBUFSIZE + 1] = {0};
        FILE *fp = fopen(path, "r");
        fread(json_buf, 1, MAXBUFSIZE, fp);

        obj = obj_new("doc");
        rc = load_obj_store_from_json(obj, json_buf);
    }
    else if (strncmp(ending_dot + 1, "wdz", len) == 0)
    {
        int open_status;
        zip_t *zip = zip_open(path, 0, &open_status);
        rc = load_obj_store_from_zip(obj, zip);
    }
    else if (path[len - 1] == '/')
    {
        // TODO
    }
    // add other parsing formats here
    
    if (rc != EXIT_SUCCESS)
    {
        obj_free_all(obj);
        return NULL;
    }

    return obj;
}