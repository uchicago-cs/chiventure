#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "libobj/load_json.h"

/* Recursive helper for load_obj_json
   See load_json.h */
void _load_obj_json(obj_t *parent, struct json_object *json)
{
    json_object_object_foreach(json, key, val)
    {
        // Find the type of the object
        enum json_type type = json_object_get_type(json);

        switch (type)
        {
        case json_type_boolean:
            obj_set_bool(parent, key, json_object_get_boolean(val));
            break;

        case json_type_int:
            obj_set_int(parent, key, json_object_get_int(val));
            break;

        case json_type_string:
            obj_set_str(parent, key, json_object_get_string(val));
            break;

        case json_type_object:
            obj_t *child = obj_get_attr(parent, key, true);
            _load_obj_json(child, val);
            break;

        case json_type_array:
            int n = json_object_array_length(val);
            obj_list_t *lst = NULL;

            for (int i = 0; i < n; i++)
            {
                obj_t *tmp = obj_new(key);
                json_object *el = json_object_array_get_idx(val, i);
                _load_obj_json(tmp, val);
                DL_APPEND(lst, tmp);
            }

            obj_set_list(parent, key, lst);
            break;
        
        default:
            break;
        }
    }
}

/* See load_json.h */
obj_t *load_obj_json(char *path)
{
    obj_t *obj = obj_new(path);

    struct json_object *json = json_tokener_parse(path);
    _load_obj_json(obj, json);

    return obj;
}