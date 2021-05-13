#include "npc/npc_action.h"
#include "npc/npc_game_action.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (2)
#define NOT_ALLOWED_DIRECT (3)
#define NOT_ALLOWED_INDIRECT (4)
#define NOT_ALLOWED_PATH (5)
#define CONDITIONS_NOT_MET (6)
#define EFFECT_NOT_APPLIED (7)

/* See npc_action.h */
npc_action_t *npc_action_new(char *c_name, enum npc_action_kind kind)
{
    npc_action_t *a;
    int rc;
    a = malloc(sizeof(npc_action_t));
    if(a == NULL)
    {
        error("Could not allocate memory");
        return NULL;
    }
    rc = npc_action_init(a, c_name, kind);
    if(rc != SUCCESS)
    {
        error("Could not initialize action");
        return NULL;
    }
    return a;
}

/* See npc_action.h */
int npc_action_init(npc_action_t *a, char *c_name, enum npc_action_kind kind)
{
    assert(a != NULL);
    a->c_name = strdup(c_name);
    a->kind = kind;
    if (a->c_name == NULL)
    {
        error("Could not initialize action name");
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

static npc_action_t valid_actions[] =
{
    //KIND 4
    {"TALK_TO", NPC},
    {"IGNORE", NPC},
    //{"ATTACK", NPC},

    //KIND 5
    {"GIVE", NPC_ITEM},
    {"STEAL", NPC_ITEM},

    //KIND 6
    {"TRADE", NPC_ITEM_ITEM},
    {"BUY", NPC_ITEM_ITEM}
};

static int NUM_ACTIONS = sizeof(valid_actions) / sizeof(npc_action_t);

/* See npc_action.h */
list_npc_action_t *get_npc_actions()
{
    list_npc_action_t *tmp = NULL;
    for (int i = 0; i < NUM_ACTIONS; i++)
    {
        list_npc_action_t *add = (list_npc_action_t*)malloc(sizeof(list_npc_action_t));
        npc_action_t *add_data = npc_action_new(valid_actions[i].c_name, valid_actions[i].kind);
        add->act = add_data;
        LL_PREPEND(tmp, add);
        tmp = add;
    }
    return tmp;
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

    // checks if the action type is the correct kind
    if (a->kind != NPC)
    {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }

    // checks if the action is possible
    if (possible_action(npc, a->c_name) == FAILURE)
    {
        sprintf(string, "Action %s can't be requested with item %s",
                a->c_name, npc->npc_id);
        *ret_string = string;
        return NOT_ALLOWED_DIRECT;
    }

    // get the game action struct
    game_action_t *game_act = get_action(npc, a->c_name);

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
        applied_effects = do_all_effects(npc, a->c_name);
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
int do_npc_item_action(chiventure_ctx_t *c, npc_action_t *a, npc_t *npc, item_t *i, char **ret_string)
{
    //TODO
}

/* KIND 6
 * See npc_action.h */
 int do_npc_item_item_action(chiventure_ctx_t *c, npc_action_t *a, npc_t *npc, item_t *direct, item_t *indirect, char **ret_string)
{
     //TODO
}
