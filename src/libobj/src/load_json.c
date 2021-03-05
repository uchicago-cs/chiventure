#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libobj/obj.h"
#include "common/utlist.h"

obj_t *_load_obj_json(obj_t *parent, struct json_object *json)
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
        
        default:
            break;
        }


        // if (json_object_is_type(val, json_type_array))
        // {
        //     obj_list_t *lst = NULL;

        //     int n = json_object_array_length(val);
        //     for (int i = 0; i < n; i++)
        //     {
        //         obj_t *tmp = obj_new(id)
        //         obj_t *tmp = load_obj_json();
        //         DL_APPEND(lst, tmp);
        //     }

        //     return lst;
        // }
        // else if (json_object_is_type(val, json_type_object))
        // {
        //     /* The only file with an object-type value as top-level
        //      * is players.json. Other special cases can go here, but unlikely.
        //      */
        //     printf("Found player object.\n");
        //     json_object *j_player_obj; 
        //     json_object_object_get_ex(val, key, &j_player_obj);
        //     object_t *player = convert_j_obj_to_game_obj(j_player_obj, key);
        //     if (!player)
        //     {
        //         return NULL;
        //     }
        //     add_objstore(obj_store, player);
        //     return SUCCESS;
        // }
        // else 
        // {
        //     return NULL;
        // }
    }
}

/* See load_json.h */
obj_t *load_obj_json(char *path)
{
    obj_t *obj = obj_new(path);

    struct json_object *json = json_tokener_parse(path);

    return _load_obj_json(obj, json);
}