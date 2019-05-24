#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "item.h"



item_t* load_item(wdl_i)
{
    obj_t *items_obj = obj_get_attr(doc, "ITEMS", false);

    // extract list of items
    attr_list_t *curr = obj_list_attr(items_obj);

    // if items list is empty then return 1
    if (curr != NULL) {
        fprintf(stderr, "items list is empty\n");
        return -1;
    }

    // while list of itemss exists, create new game_struct item, add item to room
    while (curr != NULL) {
        // get id, short_desc, and long_desc
        char *id = obj_get_str(curr->obj, "id");
        char *short_desc = obj_get_str(curr->obj, "short_desc");
        char *long_desc = obj_get_str(curr->obj, "long_desc");

        // create new game_state item
        item_t *ret_item = item_new(id, short_desc, long_desc);

        // add item to room
        add_room_to_game(g, room); //FIXME 
        curr = curr->next;
    }
}
