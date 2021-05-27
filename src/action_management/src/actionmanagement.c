#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "action_management/action_structs.h"
#include "action_management/actionmanagement.h"
#include "game-state/game_action.h"
#include "game-state/room.h"
#include "npc/npc.h"


#define BUFFER_SIZE (100)
#define WRONG_KIND (2)
#define NOT_ALLOWED_DIRECT (3)
#define NOT_ALLOWED_INDIRECT (4)
#define NOT_ALLOWED_PATH (5)
#define CONDITIONS_NOT_MET (6)
#define EFFECT_NOT_APPLIED (7)


/* See actionmanagement.h */
action_type_t *action_type_new(char *c_name, enum action_kind kind)
{
    action_type_t *a = malloc(sizeof(action_type_t));

    if (a == NULL)
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    int new_a = action_type_init(a, c_name, kind);
    if (new_a != SUCCESS)
    {
        fprintf(stderr, "Could not initialize action type %s", c_name);
        return NULL;
    }

    return a;
}


/* See actionmanagement.h */
int action_type_init(action_type_t *a, char *c_name, enum action_kind kind)
{
    assert(a);
    a->c_name = c_name;
    a->kind = kind;
    a->room = NULL;
    a->direction = NULL;

    return SUCCESS;
}


/* See actionmanagement.h */
int action_type_free(action_type_t *a)
{
    assert(a);
    free(a);
    return SUCCESS;
}


/* See actionmanagement.h */
int action_type_init_room_dir(action_type_t *a, room_t *room, char *direction)
{
    a->room = room;
    a->direction = direction;
    return SUCCESS;
}


/* ========================================================================== */


/* 
 * helper function that removes condition
 *
 * Parameter:
 * action that's being one
 *
 * Returns:
 * SUCCESS if action's removed
 */
int helper_remove(action_type_t *a)
{
            path_t *closed_path;
            closed_path = path_search(a->room,a->direction);
            /* only if action is a condition to something (action with
               null room and direction produce null path) */
            if (closed_path)
            {
                list_action_type_t *delete_node;
                int condition;
                closed_path = path_search(a->room,a->direction);
                delete_node = find_act(closed_path->conditions, a);
                condition = remove_condition(closed_path, delete_node);
                if (condition != SUCCESS)
                {
                    return CONDITIONS_NOT_MET;
                }
            }
    return SUCCESS;
}


/* KIND 1
 * See actionmanagement.h */
int do_item_action(chiventure_ctx_t *c, action_type_t *a, item_t *i, char **ret_string)
{
    assert(c);
    assert(c->game);
    assert(a);
    assert(i);
    
    game_t *game = c->game;

    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    // checks if the action type is the correct kind
    if (a->kind != ITEM)
    {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }

    /* use representative c_name for action synonyms */
    if(strncmp(a->c_name, "PICKUP", BUFFER_SIZE) == 0) 
    {
        a->c_name = "TAKE";
    } 
    else if(strncmp(a->c_name, "USE", BUFFER_SIZE) == 0 || strncmp(a->c_name, "EAT", BUFFER_SIZE) == 0 || strncmp(a->c_name, "DRINK", BUFFER_SIZE) == 0)
    {
        a->c_name = "CONSUME";
    }

    agent_t *agent = NULL;
    agent->item = i;

    // checks if the action is possible
    if (possible_action(agent, a->c_name) == FAILURE)
    {
        sprintf(string, "Action %s can't be requested with item %s",
                a->c_name, i->item_id);
        *ret_string = string;
        return NOT_ALLOWED_DIRECT;
    }

    // get the game action struct
    game_action_t *game_act = get_action(agent, a->c_name);

    // check if all conditions are met
    if (!all_conditions_met(game_act->conditions))
    {
        sprintf(string, "%s", game_act->fail_str);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }
    else
    {
        // implement the action (i.e. dole out the effects)
        int applied_effects;
        applied_effects = do_all_effects(agent, a->c_name);
        if (applied_effects == FAILURE)
        {
            sprintf(string, "Effect(s) of Action %s were not applied", a->c_name);
            *ret_string = string;
            return EFFECT_NOT_APPLIED;
        }
        else
        {
	    //remove action from any conditions
	    int rc;
	    rc = helper_remove(a);

            // successfully carried out action
            sprintf(string, "%s", game_act->success_str);
            if (is_game_over(game))
            {
                string = strcat(string, " Congratulations, you've won the game! "
                        "Press ctrl+D to quit.");
            }
            *ret_string = string;
            return SUCCESS;
        }
    }
}


/* KIND 2
 * See actionmanagement.h */
int do_path_action(chiventure_ctx_t *c, action_type_t *a, path_t *p, char **ret_string)
{
    assert(c);
    assert(c->game);
    assert(c->game->curr_room);
    assert(a);


    /* INITIALIZATION */
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);
    char *direction = p->direction;
    game_t *g = c->game;
    room_t *room_dest = p->dest;
    room_t *room_curr = g->curr_room;
    path_t *path_found = path_search(room_curr, direction);

    /* VALIDATION */
    // checks if the action type is the correct kind
    if (a->kind != PATH)
    {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }
    /* validate existence of path and destination
       third condition checks if conditions have been met */
    if ((path_found == NULL) || (room_dest == NULL) || (p->conditions != NULL))
    {
        sprintf(string, "The path or room provided was invalid.");
        *ret_string = string;
        return NOT_ALLOWED_PATH;
    }

    /* PERFORM ACTION */
    int move = move_room(g, room_dest);

    //remove action from any conditions
    int rc;
    rc = helper_remove(a);

    // successfully carried out action
    if (is_game_over(g)) {
        sprintf(string, "Moved into %s. This is the final room, you've won the game! Press ctrl+D to quit.",
                 room_dest->room_id);
        *ret_string = string;
        return SUCCESS;
    }
    else if (move == SUCCESS || move == FINAL_ROOM)
    {
        snprintf(string, BUFFER_SIZE, "Moved into %s. %s",
                 room_dest->room_id, room_dest->long_desc);
        *ret_string = string;
        return SUCCESS;
    }
    else {
        sprintf(string, "Move action %s via %s into %s failed.",
                a->c_name, direction, room_dest->room_id);
        *ret_string = string;
        return NOT_ALLOWED_PATH;
    }
}


/* KIND 3
 * See actionmanagement.h */
int do_item_item_action(chiventure_ctx_t *c, action_type_t *a, item_t *direct,
                        item_t *indirect, char **ret_string)
{
    assert(c);
    assert(c->game);
    assert(a);
    assert(direct);
    assert(indirect);
    
    agent_t *agentdir = NULL;
    agentdir->item = direct;

    
    game_t *game = c->game;
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    // checks if the action type is the correct kind
    if (a->kind != ITEM_ITEM)
    {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }


    // checks if the action is possible with the direct item
    if (possible_action(agentdir, a->c_name) == FAILURE)
    {
        sprintf(string, "Action %s can't be requested with item %s",
                a->c_name, direct->item_id);
        *ret_string = string;
        return NOT_ALLOWED_DIRECT;
    }

    // get the game action struct
    game_action_t *dir_game_act = get_action(agentdir, a->c_name);

    // check if all conditions of the action are met
    if (!all_conditions_met(dir_game_act->conditions))
    {
        sprintf(string, "%s", dir_game_act->fail_str);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }
    else
    {
        // implement the action (i.e. dole out the effects)
        action_effect_list_t *act_effects = dir_game_act->effects;
        int applied_effect = FAILURE;
        while (act_effects)
        {
            // apply the effects of the direct item action (use, put) on the indirect item
            if (strcmp(act_effects->agent->item->item_id, indirect->item_id) == 0)
            {
                applied_effect = do_effect(act_effects);
                if (applied_effect == FAILURE)
                {
                    sprintf(string, "Effect of Action %s could not be applied to Item %s",
                            a->c_name, indirect->item_id);
                    *ret_string = string;
                    return EFFECT_NOT_APPLIED;
                }
            }
            act_effects = act_effects->next;
        }
        if (applied_effect == FAILURE)
        {
            sprintf(string, "Action %s can't be requested on item %s",
                    a->c_name, indirect->item_id);
            *ret_string = string;
            return NOT_ALLOWED_INDIRECT;
        }
        else if (applied_effect == SUCCESS)
        {
            //remove action from any conditions
            int rc;
            rc = helper_remove(a);

            // successfully carried out action
            sprintf(string, "%s", dir_game_act->success_str);
            if (is_game_over(game))
            {
                string = strcat(string, " Congratulations, you've won the game! "
                        "Press ctrl+D to quit.");
            }
            *ret_string = string;
            return SUCCESS;
        }
    }
    return FAILURE;
}

/* KIND 4
 * See npc_action.h */
int do_npc_action(chiventure_ctx_t *c, action_type_t *a, npc_t *npc, char **ret_string)
{
    assert(c);
    assert(c->game);
    assert(a);
    assert(npc);
    
    game_t *game = c->game;

    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    agent_t *agent = NULL;
    agent->npc = npc;

    // checks if the action type is the correct kind
    if (a->kind != NPC)
    {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }

    // checks if the action is possible
    if (possible_action(agent, a->c_name) == FAILURE)
    {
        sprintf(string, "Action %s can't be requested with npc %s",
                a->c_name, npc->npc_id);
        *ret_string = string;
        return NOT_ALLOWED_DIRECT;
    }

    // get the game action struct
    game_action_t *game_act = get_action(agent, a->c_name);

    // check if all conditions are met
    if (!all_conditions_met(game_act->conditions))
    {
        sprintf(string, "%s", game_act->fail_str);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }
    else
    {
        // implement the action (i.e. dole out the effects)
        // maybe incorporates and initialize conversation function to
        int applied_effects;
        applied_effects = do_all_effects(agent, a->c_name);
        if (applied_effects == FAILURE)
        {
            sprintf(string, "Effect(s) of Action %s were not applied", a->c_name);
            *ret_string = string;
            return EFFECT_NOT_APPLIED;
        }
        else
        {
	    //remove action from any conditions
	    int rc;
	    rc = helper_remove(a);

            // successfully carried out action
            sprintf(string, "%s", game_act->success_str);
            if (is_game_over(game))
            {
                string = strcat(string, " Congratulations, you've won the game! "
                        "Press ctrl+D to quit.");
            }
            *ret_string = string;
            return SUCCESS;
        }
    }
} 

/* KIND 5
 * See npc_action.h */
int do_npc_item_action(chiventure_ctx_t *c, action_type_t *a, item_t *item, npc_t *npc, char **ret_string)
{
    agent_t *agent_n = NULL;
    agent_n->npc = npc;

    if(a->kind != NPC_ITEM)
    {
        return WRONG_KIND;
    }
    // get the game action struct
    game_action_t *game_act = get_action(agent_n, a->c_name);
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    // check if all conditions are met
    if (!all_conditions_met(game_act->conditions))
    {
        sprintf(string, "%s", game_act->fail_str);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }
    if(item_in_npc_inventory(npc, item) || item_in_inventory(c->game->curr_player, item))
    {
        *ret_string = "Items Allocated";
        return SUCCESS;
        
    } else{
        *ret_string = "Action cannot be completed since item is not in either inventory";
        return CONDITIONS_NOT_MET;
    }
    
}

/* KIND 6
 * See npc_action.h */
int do_npc_exchange_action(chiventure_ctx_t *c, action_type_t *a, item_t *item, npc_t *npc, char **ret_string, item_t* ret_item)
{

    agent_t *agent_n = NULL;
    agent_n->npc = npc;

    if(a->kind != NPC_ITEM_ITEM)
    {
        return WRONG_KIND;
    }
    // get the game action struct
    game_action_t *game_act = get_action(agent_n, a->c_name);
    char *string = malloc(BUFFER_SIZE);
    memset(string, 0, BUFFER_SIZE);

    // check if all conditions are met
    if (!all_conditions_met(game_act->conditions))
    {
        sprintf(string, "%s", game_act->fail_str);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }
    if(!item_in_npc_inventory(npc, item))
    {
        *ret_string = "NPC doesn't have desired item in inventory";
        return CONDITIONS_NOT_MET;
        
    } else{
        int cost = strlen(item->short_desc);
        item_list_t *player_inventory;
        player_inventory = get_all_items_in_hash(c->game->curr_player->inventory);
        bool can_buy = false;
        while(player_inventory != NULL){
            if(strlen(player_inventory->item->short_desc) >= cost){
                can_buy = true;
                ret_item = player_inventory->item;
                return SUCCESS;
            }
            player_inventory = player_inventory->next;
        }
        *ret_string = "Action cannot be completed since you have no items of equal or greater value";
        return CONDITIONS_NOT_MET;
    }
}
