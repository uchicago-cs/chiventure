#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "game.h"
#include "item.h"


/* hack alert
 * stop-gap solution until we get access to the game-state function
 * used as helper for load_items()
 */
room_t *find_room(game_t *game, char* room_id) {
    room_t *r;
    HASH_FIND(hh, game->all_rooms, room_id, strlen(room_id), r);
    return r;
}


/* See load_item/h */
int load_actions(obj_t *doc, item_t *i)
{
    // getting a list of actions from item
    attr_list_t *action_ls = get_item_actions(doc);

    if (action_ls == NULL) {
        fprintf(stderr, "action fails type checking, or action list is empty\n");
        return -1;
    }

    attr_list_t *curr = action_ls;

    // setting action attributes; might need to change this in the future
    while (curr != NULL) {
        set_str_attr(i, obj_get_str(curr->obj, "action"), obj_get_str(curr->obj, "action"));
        curr = curr->next;
    }

    return 0;
}


/* See load_item/h */
int load_items(obj_t *doc, game_t *g)
{
    // we use extract_objects() instead of obj_list_attr() because the former does type checking
    attr_list_t *items_obj = extract_objects(doc, "ITEMS");
    if (items_obj == NULL) {
        fprintf(stderr, "items fail type checking\n");
    }

    // set current item
    attr_list_t *curr = items_obj;

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
        char* in = obj_get_str(curr->obj, "in");

        // create new game_state item
        item_t *item = item_new(id, short_desc, long_desc);
        /* in parameter yet to implemented by game-state
        item_t *item = item_new(id, short_desc, long_desc, in); */

        //load actions into item
        if(load_actions(doc, item) == -1)
	    {
	        fprintf(stderr, "actions havw not been loaded properly");
	        return -1;
	    }

        //retrieve the pointer for the room that the item is located in
        room_t *item_room = find_room(g, in);

        // add item to room
        add_item_to_room(item_room, item);
        curr = curr->next;
    }
    return 0;
}