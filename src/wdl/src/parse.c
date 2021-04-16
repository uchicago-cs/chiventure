#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libobj/obj.h"
#include "libobj/load.h"
#include "wdl/parse.h"

/* See load_room.h */
obj_t *get_doc_obj(char *fpath)
{
    obj_t *obj = obj_new("doc");
    int open_status;
    zip_t *zip = zip_open(fpath, 0, &open_status);
    load_obj_zip(obj, zip);
    return obj;
}

/* get_obj_list()
 * a helper function to load a list of the rooms, items, or players
 *
 * parameters:
 *  - obj: The document object
 *  - str: the attribute asssociated with the desired objects
 *
 * returns:
 *  - a list of objects
 *  - null if attribute does not have associated objects, or if no such attribute exists
 */
obj_t *get_obj_list(obj_t *obj, char *str)
{
    if (strcmp(str, "ROOMS") == 0)
    {
        return obj_get_attr(obj, "ROOMS", false);
    }
    else if (strcmp(str, "ITEMS") == 0)
    {
        return obj_get_attr(obj, "ITEMS", false);
    }
    else if (strcmp(str, "PLAYERS") == 0)
    {
        return obj_get_attr(obj, "PLAYERS", false);
    }
    else
    {
        return NULL;
    }
}

/* see parse.h */
obj_t *extract_objects(obj_t *obj, char *str)
{
    bool valid = false;

    if (obj == NULL)
    {
        return NULL;
    }

    if (strcmp(str, "ROOMS") == 0)
    {
        valid = list_type_check(obj, room_type_check);
    }
    else if (strcmp(str, "ITEMS") == 0)
    {
        valid = list_type_check(obj, item_type_check);
    }

    if (valid == SUCCESS)
    {
        return obj_get_attr(obj, str, false);
    }
    else
    {
        return NULL;
    }
}

// /* See parse.h */
// obj_t* get_items_in_room(char* room_id, obj_t *all_items)
// {
//     attr_list_t* ret_ls = (attr_list_t*) malloc (sizeof(attr_list_t));
//     attr_list_t* tmp = all_items;

//     obj_t *curr, *tmp;
//     HASH_ITER(hh, all_items, curr, tmp)
//     {
//         //will update this to item_compare in the future
//         if(strcmp(obj_get_str(tmp->obj, "in"), room_id) == 0)
//         {
//             ret_ls->obj = tmp->obj;
//             attr_list_t* next_in_ls = (attr_list_t*) malloc (sizeof(attr_list_t));
//             ret_ls->next = next_in_ls;
//             ret_ls = ret_ls->next;
//         }
//         tmp = tmp->next;
//     }
//     return ret_ls;
// }

/* see parse.h */
obj_t *get_item_actions(obj_t *item)
{
    bool valid = false;

    obj_t *ls = obj_get_attr(item, "actions", false);
    if (ls == NULL)
    {
        return NULL;
    }

    valid = list_type_check(ls, action_type_check);
    if (valid == SUCCESS)
    {
        return ls;
    }
    else
    {
        return NULL;
    }
}