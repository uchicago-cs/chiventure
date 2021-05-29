#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "libobj/load.h"

// Reverse strstr
// From https://stackoverflow.com/questions/1634359/is-there-a-reverse-function-for-strstr
char *_rstrstr(char *__restrict s1, char *__restrict s2)
{
  size_t  s1len = strlen(s1);
  size_t  s2len = strlen(s2);
  char *s;

  if (s2len > s1len)
    return NULL;
  for (s = s1 + s1len - s2len; s >= s1; --s)
    if (strncmp(s, s2, s2len) == 0)
      return s;
  return NULL;
}

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

    // Strip off the string DEFAULT
    char *default_str = _rstrstr(str, "DEFAULT");
    if (default_str != NULL)
    {
        *default_str = '.';
        *(default_str + 1) = '\0';
    }

    return rc;
}

/* See load.h */
int load_obj_store_from_zip(obj_t *obj, zip_t *zip)
{
    if (obj == NULL || zip == NULL)
    {
        return EXIT_FAILURE;
    }

    zip_int64_t n_entries = zip_get_num_entries(zip, 0);
    if (n_entries <= 0) // negative number means error, 0 means empty zip
    {
        // Close without saving
        zip_discard(zip);
        return EXIT_FAILURE;
    }

    for (zip_int64_t i = 0; i < n_entries; i++)
    {
        // Get the name of the file and see if it's a .json file
        zip_file_t *curr_file = zip_fopen_index(zip, i, 0);
        const char *path = zip_get_name(zip, i, 0);
        char *name_buf = calloc(sizeof(char), MAX_DEPTH * (MAXLEN_ID + 1));
        if (name_buf == NULL)
        {
            zip_discard(zip);
            return EXIT_FAILURE;
        }

        strncpy(name_buf, path, MAX_DEPTH * (MAXLEN_ID + 1) - 1);

        // Don't try to load non-json files
        if (_strip_expected_extension(name_buf, "json") == false)
        {
            free(name_buf);
            continue;
        }

        // Pull the json file into memory
        char *json_buf = calloc(MAXBUFSIZE + 1, sizeof(char));
        if (json_buf == NULL)
        {
            free(name_buf);
            zip_discard(zip);
            return EXIT_FAILURE;
        }

        if (zip_fread(curr_file, json_buf, MAXBUFSIZE) == -1)
        {
            free(name_buf);
            free(json_buf);
            zip_discard(zip);
            return EXIT_FAILURE;
        }

        // Load the json file into an object at <name_buf>
        for (int p = 0; p < strnlen(name_buf, MAX_DEPTH * (MAXLEN_ID + 1) - 1); p++)
        {
            if (name_buf[p] == '/')
            {
                name_buf[p] = '.';
            }
        }
        obj_t *to_load = obj_get_attr(obj, name_buf, true);
        if (load_obj_store_from_json(to_load, json_buf) == EXIT_FAILURE)
        {
            free(name_buf);
            free(json_buf);
            zip_discard(zip);
            return EXIT_FAILURE;
        }

        free(name_buf);
        free(json_buf);
    }

    return EXIT_SUCCESS;
}
