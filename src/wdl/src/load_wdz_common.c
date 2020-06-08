#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "wdl/load_wdz_internal.h"

// Helper macros for the json name -> game object type conversion

#define SAME_STRING(s1, s2) (strcmp(s1, s2) == (0))
#define TYPE_PLAYER_STR "player"
#define TYPE_ROOM_STR "rooms"
#define TYPE_ITEM_STR "items"
#define TYPE_ACTION_STR "actions"
#define TYPE_GCONDITION_STR "globalconditions"
#define TYPE_DIALOG_STR "dialog"
#define TYPE_NPC_STR "npcs"
#define TYPE_CUSTOM_SCRIPT_STR "customscripts"

/*
 * match_j_name_to_game_obj_type:
 * Converts a raw json filename/top-level key name into
 * the corresponding objtype_t enum value.
 * 
 * Parameters:
 * - j_name: A string that is the raw name
 * 
 * Returns:
 * - An objtype_t value corresponding to that name
 */
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
    else if (SAME_STRING(j_name, TYPE_CUSTOM_SCRIPT_STR))  
    {
        game_obj_type = TYPE_CUSTOM_SCRIPT;
    }
    else if (strlen(j_name) == 0)
    {
        game_obj_type = TYPE_NONE;
    }
    else
    {
        game_obj_type = TYPE_ERR;
    }
    
    return game_obj_type;
}

/* 
 * make_data_from_j_value
 * Recursively converts every JSON object that isn't formatted like a proper
 * game object. This works on nested JSON objects and arrays, too.
 * Serves to make the void ptr data field for attributes.
 * WARNING: This mallocs the data, so they must later be freed.
 * 
 * Parameters:
 * - j_value: the json_object to be converted
 * 
 * Returns:
 * - a void pointer pointing to allocated memory containing the desired data
 */
void *make_data_from_j_value(json_object *j_value)
{
    json_type j_type = json_object_get_type(j_value);
    switch (j_type)
    {
        case json_type_boolean: 
        {
            json_bool *val = malloc(sizeof(*val));
            *val = json_object_get_boolean(j_value); 
            return (void*)val;
        }
        case json_type_double:
        {
            double *val = malloc(sizeof(*val));
            *val = json_object_get_double(j_value);
            return (void*)val;
        }
        case json_type_int:
        {
            int *val = malloc(sizeof(*val));
            *val = json_object_get_int(j_value);
            return (void*)val;
        }
        case json_type_string:
        {
            int str_len = json_object_get_string_len(j_value);
            char *val = calloc(str_len + 1, sizeof(*val));

            strcpy(val, json_object_get_string(j_value));
            return (void*)val;
        }
        case json_type_null:
        {
            void *val = NULL;
            return (void*)val;
        }
        /* the recursive converters */
        case json_type_object:
        {
            object_t *val = new_object("", TYPE_NONE);
            json_object_object_foreach(j_value, attr_name, attr_val)
            {
                printf("Adding object key \"%s\" value %s\n",attr_name, json_object_to_json_string(attr_val));
                add_attribute(&(val->attrs), attr_name, 
                    make_data_from_j_value(attr_val));
            }
            return (void*)val;

        }
        case json_type_array:
        {
            int arr_len = json_object_array_length(j_value);
            if (arr_len == 0)
            {
                void *val = NULL;
            }
            object_t *val = new_object("", TYPE_NONE);
            for (int i = 0; i < arr_len; i++)
            {
                // var->attrs is the head element
                json_object *arr_elt = json_object_array_get_idx(j_value, i);
                void *raw_data = make_data_from_j_value(arr_elt);
                assert(raw_data != NULL);
                append_attr(val->attrs, raw_data);
            }
            return (void*)val;
        }
        default:
        {
            void *val = NULL;
            return (void*)val;
        }
    }
    return NULL;
}


object_t *convert_j_obj_to_game_obj(json_object *j_game_obj, char *j_name)
{
    /* First find game object type (e.g. a room, or an item) */
    objtype_t game_obj_type = match_j_name_to_game_obj_type(j_name);
    
    /* Then find the game object's ID */
    char game_obj_id[MAXLEN_ID];
    strncpy(game_obj_id, DEFAULT_PLAYER_OBJ_ID, MAXLEN_ID);
    json_object *game_obj_id_j_obj = NULL;
    json_object_object_get_ex(j_game_obj, "id", &game_obj_id_j_obj);
    if (!game_obj_id_j_obj)
    {
        // Player object is a one-off obj that doesn't need an id field
        // the Other object types also should not require an id field
        if ((game_obj_type != TYPE_PLAYER) 
         && (game_obj_type != TYPE_NONE)
         && (game_obj_type != TYPE_ERR))
        {
            fprintf(stderr, 
                "No id key found in the JSON of this game object!\n");
            return NULL;
        }
    }
    if ((!json_object_is_type(game_obj_id_j_obj, json_type_null))
        && json_object_is_type(game_obj_id_j_obj, json_type_string))
    {
        strncpy(game_obj_id, json_object_get_string(game_obj_id_j_obj), MAXLEN_ID);
    }
    else
    {
        fprintf(stderr, 
            "id key in the JSON of this game object has wrong value type (must be string!)\n");
        return NULL;
    }

    /* Once type and id are obtained, create the game object */
    object_t *game_obj = new_object(game_obj_id, game_obj_type);
    if (!game_obj)
    {
        fprintf(stderr, "Unable to allocate memory for game object\n");
        return NULL;
    }
    
    /* Loops through all attributes in the JSON object */
    json_object_object_foreach(j_game_obj, attr_name, j_value)
    {
        if (SAME_STRING(attr_name, "id"))
        {
            continue; // we already added the ID above
        }
        else
        {
            add_attribute(&(game_obj->attrs), attr_name, make_data_from_j_value(j_value));
        }
    }
    return game_obj;
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
    objstore_t **obj_store, 
    json_object *j_obj
)
{
    if (!j_obj)
    {
        return FAILURE;
    }

    json_object_object_foreach(j_obj, j_name, j_value)
    {
        if (json_object_is_type(j_value, json_type_array))
        {
            int n_objects = json_object_array_length(j_value);
            int omitted = 0;
            int added = 0;
            for (int i = 0; i < n_objects; i++) // for each json_object in the array
            {
                json_object *j_game_obj = json_object_array_get_idx(j_value, i);
                object_t *game_obj = convert_j_obj_to_game_obj(j_game_obj, j_name);
                if (!game_obj) 
                {
                    fprintf(stderr, "Couldn't convert json object %s[%d] into game object\n", j_name, i);
                    omitted++;
                    continue;
                }
                if (add_objstore(obj_store, game_obj) == FAILURE)
                {
                    omitted++;
                }
                else
                {
                    added++;
                }
            }
            if (omitted > 0)
            {
                fprintf(stderr, "Omitted import of %d game objects\n", omitted);
            }
            if (added > 0)
            {
                return SUCCESS;
            }
            else
            {
                return FAILURE;
            }
        }
        else if (json_object_is_type(j_value, json_type_object))
        {
            // The only file with an object-type value as top-level
            // is players.json. Other special cases can go here, but unlikely.
            
            object_t *player = convert_j_obj_to_game_obj(j_value, j_name);

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

