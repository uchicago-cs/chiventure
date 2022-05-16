#include <stdio.h>

#include "game-state/item.h"
#include "wdl/validate.h"
#include "cli/util.h"

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
    while (curr != NULL)
    {
        if (strcmp(curr->act->c_name, action) == 0)
        {
            break;
        }
        curr = curr->next;
    }

    if (curr == NULL)
        return NULL;
  
    return curr->act;
}

/* See load_item.h */
int load_actions(obj_t *item_obj, agent_t *agent)
{
    // getting a list of actions from item
    obj_t *action_ls = obj_get_attr(item_obj, "actions", false);
    if (action_ls == NULL)
    {
        fprintf(stderr, "action list is empty\n");
        return FAILURE;
    }
    else if (list_type_check(action_ls, action_type_check) == FAILURE)
    {
        fprintf(stderr, "object actions failed typechecking\n");
        return FAILURE;
    }

    // setting action attributes; might need to change this in the future

    action_type_t *temp;
    list_action_type_t *val_actions = get_supported_actions();

    obj_t *curr;
    DL_FOREACH(action_ls->data.lst, curr)
    {
        char *action = case_insensitized_string(obj_get_str(curr, "action"));
        
        temp = get_game_action(action, val_actions);

        if (obj_get_str(curr, "text_success") != NULL && obj_get_str(curr, "text_fail") != NULL)
        {
            add_action(agent, action, obj_get_str(curr, "text_success"), obj_get_str(curr, "text_fail"));
        }
        else if(obj_get_str(curr, "text_success") != NULL)
        {
            add_action(agent, action, obj_get_str(curr, "text_success"), "Action failed");
        }
        else
        {
            add_action(agent, action, "Action succeeded", obj_get_str(curr, "text_fail"));
        }

        free(action);
    }

    return SUCCESS;
}


/* See load_item.h */
int load_items(obj_t *doc, game_t *g)
{
    // we use extract_objects() instead of obj_list_attr() because the former does type checking
    obj_t *items_obj = obj_get_attr(doc, "ITEMS", false);
    if (items_obj == NULL)
    {
        fprintf(stderr, "items not found\n");
        return FAILURE;
    }
    else if (list_type_check(items_obj, item_type_check) == FAILURE)
    {
        fprintf(stderr, "items fail type checking\n");
        return FAILURE;
    }

    // while list of items exists, create new game_struct item, add item to room
    obj_t *curr, *tmp;
    HASH_ITER(hh, items_obj->data.obj.attr, curr, tmp)
    {
        // get id, short_desc, and long_desc
        char *id = curr->id;
        char *short_desc = obj_get_str(curr, "short_desc");
        char *long_desc = obj_get_str(curr, "long_desc");
        char *in = obj_get_str(curr, "in");

        // create new game_state item
        item_t *item = item_new(id, short_desc, long_desc);
        /* in parameter yet to implemented by game-state
        item_t *item = item_new(id, short_desc, long_desc, in); */
        agent_t *agent;
        agent->item = item;

        // load actions into item
        if(load_actions(curr, agent) == FAILURE)
        {
            fprintf(stderr, "actions have not been loaded properly");
            return FAILURE;
        }

        add_item_to_game(g, agent->item);

        // add item to its room, unless it is meant to be an NPC-held item
        if (strcmp(in, "npc") != 0) {
            room_t *item_room = find_room_from_game(g, in);
            add_item_to_room(item_room, item);
        }
    }
    return SUCCESS;
}
