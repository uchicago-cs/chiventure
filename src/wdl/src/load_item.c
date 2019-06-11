#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "game.h"
#include "item.h"
#include "room.h"
#include "load_item.h"

/*
 * get_game_action()
 * A helper fuction to get the pointer to the game_action struct corresponding to
 * the action in the attribute list in the actions field of an item.
 *
 * parameters
 *  - action: a string corresponding to the action ID
 *  - val: a list of valid actions
 *
 * returns:
 *  - a pointer to an game_action struct
 *  - NULL if an error occurs
 */
action_type_t *get_game_action(char *action, list_action_type_t *valid) 
{
    list_action_type_t *curr = valid;
    
    // finding matching action_type_t
    while (curr != NULL) {
        if (strcmp(curr->act->c_name, action) == 0) {
            break;
        }
        curr = curr->next;
    }

    return curr->act;
}

/* See load_item.h */
int load_actions(obj_t *doc, item_t *i)
{
    // getting a list of actions from item
    attr_list_t *action_ls = get_item_actions(doc);
    if (action_ls == NULL) {
        fprintf(stderr, "action fails type checking, or action list is empty\n");
        return FAILURE;
    }

    attr_list_t *curr = action_ls;
    // setting action attributes; might need to change this in the future
    
    action_type_t *temp;
    list_action_type_t *val_actions = get_supported_actions();

    while (curr != NULL) {
        temp = get_game_action(obj_get_str(curr->obj, "action"), val_actions);
        set_act_attr(i, obj_get_str(curr->obj, "action"), temp);

        curr = curr->next;
    }

    return SUCCESS;
}


/* See load_item.h */
int load_items(obj_t *doc, game_t *g)
{
    // we use extract_objects() instead of obj_list_attr() because the former does type checking
    attr_list_t *items_obj = extract_objects(doc, "ITEMS");
    if (items_obj == NULL) {
        fprintf(stderr, "items fail type checking\n");
    }

    // set current item
    attr_list_t *curr = items_obj;

    // if items list is empty then return -1
    if (curr == NULL) {
        fprintf(stderr, "items list is empty\n");
        return FAILURE;
    }

    // while list of items exists, create new game_struct item, add item to room
    while (curr != NULL) {
        // get id, short_desc, and long_desc
        char *id = obj_get_str(curr->obj, "id");
        char *short_desc = obj_get_str(curr->obj, "short_desc");
        char *long_desc = obj_get_str(curr->obj, "long_desc");
        char *in = obj_get_str(curr->obj, "in");

        // create new game_state item
        item_t *item = item_new(id, short_desc, long_desc);
        /* in parameter yet to implemented by game-state
        item_t *item = item_new(id, short_desc, long_desc, in); */

        //load actions into item
        if(load_actions(curr->obj, item) == FAILURE) {
	          fprintf(stderr, "actions have not been loaded properly");
	          return FAILURE;
        }

        //retrieve the pointer for the room that the item is located in
        room_t *item_room = find_room_from_game(g, in);

        // add item to room
        add_item_to_room(item_room, item);
        curr = curr->next;
    }
    return SUCCESS;
}
