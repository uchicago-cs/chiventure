#include "npc/npc_action.h"
#include <string.h>
#include "npc/npc_game_action.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (2)
#define NOT_ALLOWED_DIRECT (3)
#define NOT_ALLOWED_INDIRECT (4)
#define NOT_ALLOWED_PATH (5)
#define CONDITIONS_NOT_MET (6)
#define EFFECT_NOT_APPLIED (7)

/* See npc_action.h */
npc_action_t *npc_action_new(char *c_name, npc_actions_t action)
{
    npc_action_t *a;
    int rc;
    a = malloc(sizeof(npc_action_t));
    if(a == NULL)
    {
        error("npc_action_t: Could not allocate memory\n");
        return NULL;
    }
    rc = npc_action_init(a, c_name, action);
    if(rc != SUCCESS)
    {
        error("npc_action_t: Could not initialize action\n");
        return NULL;
    }
    return a;
}


/* See npc_action.h */
int npc_action_init(npc_action_t *a, char *c_name, npc_actions_t action)
{
    assert(a != NULL);
    a->c_name = strdup(c_name);
    a->action = action;
    if (a->c_name == NULL)
    {
        error("npc_action_init: Could not initialize action name\n");
        return FAILURE;
    }
    return SUCCESS;
}


/* See npc_action.h */
int npc_action_free(npc_action_t *a)
{
    assert(a != NULL);
    free(a->c_name);
    free(a);
    return SUCCESS;
}


/* See npc_action.h */
list_npc_action_t *get_npc_actions()
{
    //TODO
}


/* KIND 4
 * See npc_action.h */
int do_npc_action(chiventure_ctx_t *c, npc_actions_t *a, npc_t *npc, char **ret_string)
{
    assert(c);
    assert(c->game);
    assert(a);
    assert(npc);

    char *string = malloc(BUFFER_SIZE);
    memset(string, ‘\0’, BUFFER_SIZE);

    // case for TALK_TO
    if (a == TALK_TO) {
        // check if NPC has TALK_TO in their list_npc_action_t
        if (contains_action(npc, TALK_TO) == 0) {
        sprintf(string, “Player cannot TALK_TO the NPC”);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
        }
        // initiates conversation (set_game_mode to CONVERSATION)
        int switch_mode;
        switch_mode = set_game_mode(c->game, CONVERSATION, “NORMAL”);
        if (switch_mode == FAILURE)
        {
            sprintf(string, “Failed to switch to normal mode”);
            return FAILURE;
        }
    }

    // case for IGNORE
    if (a == IGNORE) {
        // check if NPC has IGNORE in their list_npc_action_t
        if (contains_action(npc, IGNORE) == 0) {
            sprintf(string, “Player cannot IGNORE the NPC”);
            *ret_string = string;
        return CONDITIONS_NOT_MET;
        }
        // exits conversation (set_game_mode to NORMAL)
        int switch_mode;
        switch_mode = set_game_mode(c->game, NORMAL, “CONVERSATION”);
        if (switch_mode == FAILURE)
        {
            sprintf(string, “Failed to switch to conversation mode”);
            return FAILURE;
        }
    }

    // case for all other actions 
    if (a != TALK_TO || a != IGNORE) {
        sprintf(string, “cannot perform %s with do_npc_action”, *a);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }
}


/* KIND 5
 * See npc_action.h */
int do_npc_item_action(chiventure_ctx_t *c, npc_actions_t *a, npc_t *npc, item_t *i, char **ret_string)
{
    //TODO
}


/* KIND 6
 * See npc_action.h */
 int do_npc_item_item_action(chiventure_ctx_t *c, npc_actions_t *a, npc_t *npc, item_t *direct, item_t *indirect, char **ret_string)
{
     //TODO
}


/*
 * helper function that checks if the action is listed on the list_npc_action_t of an npc
 *
 * Parameters:
 *    - npc: An npc_t. 
 *    - action: An npc_actions_t. 
 *
 * Returns:
 *    - 0 if action is not contained, 1 if action is contained
 */
int contains_action(npc_t npc, npc_actions_t action) {
	list_npc_action_t *actions = npc->npc_actions;
	while (actions != NULL) {
		if (actions->npc_action->action == action) {
			return 1;
        }
        actions = actions->next;
	}
	return 0;
}