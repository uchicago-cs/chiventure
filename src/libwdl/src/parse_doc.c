#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parse_document.h"

/* See parse_document.h */
void create_rooms(attr_list_t *ls, game_t *g)
{
    attr_list_t* tmp = ls;

    while(tmp != NULL)
    {   
        char* id = obj_get_str(tmp->obj, id_str);
        char* short_desc = obj_get_str(tmp->obj, short_str);
        char* long_desc = obj_get_str(tmp->obj, long_str);

        attr_list_t* connections_list = connections_get_list(tmp->obj);

        //based on linked list structs instead of hash table as per conversation today
        room_new(id, short_desc, long_desc, 
                get_items_in_room(id, extract_objects(doc_obj, id)), connections_list);
        add_room_to_game(room_new, g); //ADD TO GAME when game state gives us this function
        tmp = tmp->next;
    }
}

/* See parse_document.h */
attr_list_t* get_items_in_room(char* room_id, attr_list_t *all_items)
{
    attr_list_t* ret_ls = (attr_list_t*) malloc (sizeof(attr_list_t));
    attr_list_t* tmp = all_items;
    while(tmp != NULL)
    {
        //will update this to item_compare in the future
        if(strcmp(obj_get_str(tmp->obj, in), room_id) == 0)
        {
            ret_ls->object = tmp->obj;
            attr_list_t* next_in_ls = (attr_list_t*) malloc (sizeof(attr_list_t));
            ret_ls->next = next_in_ls;
            ret_ls = ret_ls->next; 
        }
        tmp = tmp->next;
    }
    return ret_ls;
}

