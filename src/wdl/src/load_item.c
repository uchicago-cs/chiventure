#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "item.h"

/* See load_item/h */
int load_items(obj_t *doc, game_t *g)
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
        char* in = obj_get_str(curr->obj. "in");

        // create new game_state item
        item_t *item = item_new(id, short_desc, long_desc, in);

        //retrieve the pointer for the room that the item is located in
        room_t *item_room = find_room(g, in);

        // add item to room
        add_item_to_room(item_room, item);
        curr = curr->next;
    }
    return 0;
}

/* See load_item/h */
int load_actions(obj_t *doc, item_t *i)
{
    return 0;
}
