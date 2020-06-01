#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "load_wdz_internal.h"

#include "wdl/wdl_common.h" // to get obj_t


obj_t *convert_j_obj_to_game_obj(json_object *j_game_obj, char *j_name)
{
    // dummy function for now.
    // Waiting on new obj_t implementation before we can write this conversion! 
    return NULL;
}


int add_objstore(objstore_t *obj_store, obj_t *game_obj)
{
    // dummy function for now.
    return FAILURE;
}


/* See load_wdz_internal.h */
bool filename_extension_is(const char *ext, const char *str)
{
    char *dot_and_ext = strrchr(str, '.');
    if (dot_and_ext) // if there was a period
    {
        return (strcmp(dot_and_ext + 1, ext) == 0);
    }
}


/* See load_wdz_internal.h */
int load_game_objects_from_json_object
(
    objstore_t *obj_store, 
    json_object *j_obj
)
{
    // // Commenting this out because we don't have an objstore right now
    // // so this is always NULL.
    // if (!obj_store)
    // {
    //     return FAILURE;
    // }
    if (!j_obj)
    {
        return FAILURE;
    }

    json_object_object_foreach(j_obj, j_name, j_value)
    {
        if (json_object_is_type(j_value, json_type_array))
        {
            int n_objects = json_object_array_length(j_value);
            for (int i = 0; i < n_objects; i++) // for each json_object in the array
            {
                json_object *j_game_obj = json_object_array_get_idx(j_value, i);
                obj_t *game_obj = convert_j_obj_to_game_obj(j_game_obj, j_name);
                if (!game_obj) 
                {
                    return FAILURE;
                }
                add_objstore(obj_store, game_obj);
            }
            return SUCCESS;
        }
        else if (json_object_is_type(j_value, json_type_object))
        {
            // The only file with an object-type value as top-level
            // is players.json. Other special cases can go here, but unlikely.
            printf("Found player object.\n");
            json_object *j_player_obj; 
            json_object_object_get_ex(j_value, j_name, &j_player_obj);
            obj_t *player = convert_j_obj_to_game_obj(j_player_obj, j_name);
            if (!player)
            {
                return FAILURE;
            }
            add_objstore(obj_store, player);
            return SUCCESS;
        }
        else 
        {
            return FAILURE;
        }
    }
    // If no return yet by now then it failed.
    return FAILURE;    
}

