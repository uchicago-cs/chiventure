#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libobj/obj.h"
#include "common/utlist.h"

/* See load_json.h */
obj_t *load_obj_json(char *path)
{
    obj_t *obj = obj_new(path);

    struct json_object *result = json_tokener_parse(path);

    // json_object_object_foreach(result, key, val)
    // {
    //     if (json_object_is_type(val, json_type_array))
    //     {
    //         int n_objects = json_object_array_length(val);
    //         for (int i = 0; i < n_objects; i++) // for each json_object in the array
    //         {
    //             json_object *j_game_obj = json_object_array_get_idx(val, i);
    //             object_t *game_obj = convert_j_obj_to_game_obj(j_game_obj, key);
    //             if (!game_obj) 
    //             {
    //                 return NULL;
    //             }
    //             add_objstore(obj_store, game_obj);
    //         }
    //         return SUCCESS;
    //     }
    //     else if (json_object_is_type(val, json_type_object))
    //     {
    //         /* The only file with an object-type value as top-level
    //          * is players.json. Other special cases can go here, but unlikely.
    //          */
    //         printf("Found player object.\n");
    //         json_object *j_player_obj; 
    //         json_object_object_get_ex(val, key, &j_player_obj);
    //         object_t *player = convert_j_obj_to_game_obj(j_player_obj, key);
    //         if (!player)
    //         {
    //             return NULL;
    //         }
    //         add_objstore(obj_store, player);
    //         return SUCCESS;
    //     }
    //     else 
    //     {
    //         return NULL;
    //     }
    // }
    
    return NULL;
}