#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "wdl/load_wdz_internal.h"

#define SAME_STRING(s1, s2) (strcmp(s1, s2) == (0))
#define TYPE_PLAYER_STR "player"
#define TYPE_ROOM_STR "rooms"
#define TYPE_ITEM_STR "items"
#define TYPE_ACTION_STR "actions"
#define TYPE_GCONDITION_STR "globalconditions"
#define TYPE_DIALOG_STR "dialog"
#define TYPE_NPC_STR "npcs"

objtype_t match_j_name_to_game_obj_type(char *j_name)
{
    objtype_t game_obj_type;
    if (SAME_STRING(j_name, TYPE_PLAYER_STR))  
    {
        game_obj_type = TYPE_PLAYER;
    }
    else if (SAME_STRING(j_name, TYPE_ROOM_STR))    
    {
        game_obj_type = TYPE_ROOM;
    }
    else if (SAME_STRING(j_name, TYPE_ITEM_STR))    
    {
        game_obj_type = TYPE_ITEM;
    }
    else if (SAME_STRING(j_name, TYPE_ACTION_STR))  
    {
        game_obj_type = TYPE_ACTION;
    }
    else if (SAME_STRING(j_name, TYPE_GCONDITION_STR))  
    {
        game_obj_type = TYPE_GCONDITION;
    }
    else if (SAME_STRING(j_name, TYPE_NPC_STR))
    {
        game_obj_type = TYPE_NPC;
    }
    else if (SAME_STRING(j_name, TYPE_DIALOG_STR))  
    {
        game_obj_type = TYPE_DIALOG;
    }
    else
    {
        game_obj_type = TYPE_UNDEFINED;
    }
    
    return game_obj_type;
}


object_t *convert_j_obj_to_game_obj(json_object *j_game_obj, char *j_name)
{
    object_t* game_obj = malloc(sizeof(object_t));
    if (!game_obj)
    {
        fprintf(stderr, "Unable to allocate memory for game object\n");
        return NULL;
    }

    /* First set the game object type (e.g. a room, or an item */
    game_obj->type = match_j_name_to_game_obj_type(j_name);
    /* Loops through all attributes in the object */
    json_object_object_foreach(j_game_obj, attr_name, j_value)
    {
        if (strcmp(attr_name, "id") == 0)
        {
            strcpy(game_obj->id, json_object_get_string(j_value));
        } 
        else
        {
            // awaiting add_attr functions to add a new attribute to object here.
        }

    }
    return NULL;
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
    // // Commenting this out because while we have objstore_t init ready,
    // // it still depends on object_t init, which always returns NULL,
    // // so the objstore ends up always NULL.
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
                object_t *game_obj = convert_j_obj_to_game_obj(j_game_obj, j_name);
                if (!game_obj) 
                {
                    fprintf(stderr, "Couldn't convert json object %s[%d] into game object\n", j_name, i);
                    continue;
                }
                add_objstore(&obj_store, game_obj);
            }
            return SUCCESS;
        }
        else if (json_object_is_type(j_value, json_type_object))
        {
            // The only file with an object-type value as top-level
            // is players.json. Other special cases can go here, but unlikely.
            
            object_t *player = convert_j_obj_to_game_obj(j_value, j_name);
            printf("Parsed player json.\n");

            if (!player)
            {
                return FAILURE;
            }
            add_objstore(&obj_store, player);
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

