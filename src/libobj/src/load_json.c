#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "libobj/load.h"

/* Recursive helper for load_obj_json
   See load_internal.h */
int _load_obj_json(obj_t *parent, struct json_object *json)
{
    // Find the type of the object
    enum json_type type = json_object_get_type(json);

    switch (type)
    {
    case json_type_boolean:
        return obj_set_bool(parent, ".", json_object_get_boolean(json));
        break;

    case json_type_int:
        return obj_set_int(parent, ".", json_object_get_int(json));
        break;

    case json_type_string:
        ; // Need this semicolon because C is weird
        // https://stackoverflow.com/questions/8384388/variable-declaration-after-goto-label
        
        const char *str = json_object_get_string(json);
        return obj_set_str(parent, ".", (char *)str);
        break;

    case json_type_object:
        ;
        json_object_object_foreach(json, key, val)
        {
            obj_t *child = obj_get_attr(parent, key, true);
            _load_obj_json(child, val);
        }
        return EXIT_SUCCESS;
        break;

    case json_type_array:
        ;
        obj_list_t *lst = NULL;
        int n = json_object_array_length(json);

        for (int i = 0; i < n; i++)
        {
            char str[MAXLEN_ID + 1] = { 0 };
            snprintf(str, MAXLEN_ID, "%d", i);
            obj_t *tmp = obj_new(str);

            json_object *el = json_object_array_get_idx(json, i);
            _load_obj_json(tmp, el);

            DL_APPEND(lst, tmp);
        }

        return obj_set_list(parent, ".", lst);
        break;
    
    default:
        return EXIT_FAILURE;
    }
}

/* See load.h */
int load_obj_store_from_json(obj_t *obj, char *json_str)
{
    struct json_object *json = json_tokener_parse(json_str);
    int rc = _load_obj_json(obj, json);

    // Frees the json object
    json_object_put(json);

    return rc;
}
