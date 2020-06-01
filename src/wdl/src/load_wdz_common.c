#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "load_wdz_internal.h"

#define MAX_GAME_OBJ_TYPE_LENGTH 32


obj_t *convert_j_obj_to_game_obj(json_object *j_game_obj, char *j_name)
{
    // duimmy function for now.
    return NULL;
}


int add_objstore(objstore_t *obj_store, obj_t *game_obj)
{
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



int get_filename_from_path(const char *path_and_name, char *just_name_here)
{
    const char *name_and_ext = strrchr(path_and_name, '/');
    if (!name_and_ext)
    {
        name_and_ext = path_and_name;
    }
    const char *file_extension_dot = strrchr(name_and_ext, '.');
    if (!file_extension_dot)
    {
        char *cpy = strncpy(just_name_here, name_and_ext, MAX_GAME_OBJ_TYPE_LENGTH);
        if (!cpy) 
        {
            return FAILURE;
        }
    }
    else
    {
        char *cpy = strncpy(just_name_here, name_and_ext, strlen(name_and_ext) -  strlen(file_extension_dot));
        if (!cpy)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}


/* See load_wdz_internal.h */
int load_game_objects_from_json_object
(
    objstore_t *obj_store, 
    json_object *j_obj,
    const char *j_path_and_name
)
{
    if (!obj_store)
    {
        return FAILURE;
    }
    if (!j_obj)
    {
        return FAILURE;
    }
    if (!j_path_and_name)
    {
        return FAILURE;
    } 
    char j_name[MAX_GAME_OBJ_TYPE_LENGTH];
    int bad_filename = get_filename_from_path(j_path_and_name, j_name);
    if (bad_filename)
    {
        return FAILURE;
    }
    json_object *j_game_objs_j_arr;
    json_object_object_get_ex(j_obj, j_name, &j_game_objs_j_arr);
    if (json_object_is_type(j_game_objs_j_arr, json_type_array))
    {
        int n_objects = json_object_array_length(j_game_objs_j_arr);
        for (int i = 0; i < n_objects; i++) // for each json_object in the array
        {
            json_object *j_game_obj = json_object_array_get_idx(j_game_objs_j_arr, i);
            obj_t *game_obj = convert_j_obj_to_game_obj(j_game_obj, j_name);
            // ^^^ waiting for obj_t implementation before we can write this conversion! 
            if (!game_obj) 
            {
                return FAILURE;
            }
            add_objstore(obj_store, game_obj);
        }
        return SUCCESS;
    }
    return FAILURE;
}


