#include "game-state/game_action.h"

/* See common_game_action.h */
int game_action_init(game_action_t *new_action, char *act_name,
                     char *success_str, char *fail_str)
{
    assert(new_action != NULL);
    if (new_action == NULL)
    {
        return FAILURE;
    }
    strncpy(new_action->action_name, act_name, strlen(act_name));
    new_action->conditions = NULL; //by UTLIST rules
    new_action->effects = NULL;    //by UTLIST rules
    strncpy(new_action->success_str, success_str, strlen(success_str));
    strncpy(new_action->fail_str, fail_str, strlen(fail_str));

    return SUCCESS;
}

/* see common_game_action.h */
game_action_t *game_action_new(char *action_name, char *success_str, char *fail_str)
{
    game_action_t *new_action = malloc(sizeof(game_action_t));
    new_action->action_name = calloc(1, MAX_ID_LEN * sizeof(char));
    new_action->success_str = calloc(1, MAX_MSG_LEN * sizeof(char));
    new_action->fail_str = calloc(1, MAX_MSG_LEN * sizeof(char));

    int check = game_action_init(new_action, action_name, success_str, fail_str);

    if (new_action == NULL || new_action->action_name == NULL)
    {

        fprintf(stderr,
                "game_action_new(): game action struct not properly malloced");
        return NULL;
    }

    if (check != SUCCESS)
    {
        return NULL;
    }

    return new_action;
}

// ---------------------------------------------------------------------------

/* see game_action.h */
game_action_t *get_action(item_t *item, char *action_name)
{
    game_action_t *action;
    HASH_FIND(hh, item->actions, action_name, strlen(action_name), action);
    if (action == NULL)
    {
        return NULL;
    }
    return action;
}

/* see game_action.h */
int add_action(item_t *item, char *action_name, char *success_str, char *fail_str)
{
    game_action_t *check = get_action(item, action_name);
    if (check != NULL)
    {
        return FAILURE;
    }
    game_action_t *action = game_action_new(action_name, success_str, fail_str);
    HASH_ADD_KEYPTR(hh, item->actions, action_name, strlen(action_name), action);
    return SUCCESS;
}

/* see game_action.h */
int possible_action(item_t *item, char *action_name)
{
    game_action_t *possible_action = get_action(item, action_name);
    if (possible_action == NULL)
    {
        return FAILURE;
    }
    else
    {
        return SUCCESS;
    }
}

// ------------------------------------- CONDITIONS -------------------------------------

/* see game_action.h */
int add_action_attribute_condition(game_action_t *action, item_t *cond_item,
                         attribute_t *cond_attribute, attribute_value_t cond_value)
{
    if (cond_item == NULL)
    {
        return ITEM_MODIFY_NULL;
    }

    if(action == NULL)
    {
        return ACTION_NULL;
    }

    condition_t *new_condition = attribute_condition_new(cond_item, cond_attribute->attribute_key, cond_value);

    LL_APPEND(action->conditions, new_condition);

    return SUCCESS;
}

/* see game_action.h */
int add_action_inventory_condition(game_action_t *action, player_t *player,
                                    item_t *item)
{    
    if (player == NULL)
    {
        return PLAYER_NULL;
    }

    if (item == NULL)
    {
        return ITEM_MODIFY_NULL;
    }

    if(action == NULL)
    {
        return ACTION_NULL;
    }

    condition_t *new_condition = inventory_condition_new(player, item);

    LL_APPEND(action->conditions, new_condition);

    return SUCCESS;
}

/* see game_action.h */
int add_action_condition(game_action_t *action, condition_t *condition)
{
    if(action == NULL)
    {
        return ACTION_NULL;
    }

    LL_APPEND(action->conditions, condition);

    return SUCCESS;
}


// ------------------------------------- EFFECTS -------------------------------------

/* see game_action.h */
//we either use item_to_add or action as action is loacted within item_to_add
int add_action_effect(game_action_t *action, item_t *item_to_add, attribute_t *attribute, attribute_value_t new_value)
{
    if (action == NULL)
    {
        return ACTION_NULL;
    }
    if (item_to_add == NULL)
    {
        return ITEM_MODIFY_NULL;
    }

    game_action_effect_t *new_effect = effect_new(item_to_add, attribute, new_value);

    LL_APPEND(action->effects, new_effect);

    return SUCCESS;
}

/* see game_action.h */
int delete_action_effect_llist(action_effect_list_t *effects)
{
    game_action_effect_t *elt, *tmp;
    LL_FOREACH_SAFE(effects, elt, tmp)
    {
        LL_DELETE(effects, elt);
        free(elt);
    }
    return SUCCESS;
}

/* see common-game-action.h */
game_action_effect_t *effect_new(item_t *item_to_modify, attribute_t *attribute, attribute_value_t new_value)
{

    if (item_to_modify == NULL || attribute == NULL)
    {
        return NULL;
    }
    game_action_effect_t *effect = malloc(sizeof(game_action_effect_t));
    effect->item = item_to_modify;
    effect->attribute_to_modify = attribute;
    effect->new_value = new_value;
    effect->next = NULL;

    return effect;
}

/* see common_game_action.h */
int do_effect(game_action_effect_t *effect)
{
    attribute_t *attr = effect->attribute_to_modify;
    attribute_value_t new_val = effect->new_value;
    switch (attr->attribute_tag)
    {
    case (DOUBLE):
        attr->attribute_value.double_val = new_val.double_val;
        return SUCCESS;
    case (BOOLE):
        attr->attribute_value.bool_val = new_val.bool_val;
        return SUCCESS;
    case (CHARACTER):
        attr->attribute_value.char_val = new_val.char_val;
        return SUCCESS;
    case (STRING):
        attr->attribute_value.str_val = new_val.str_val;
        return SUCCESS;
    case (INTEGER):
        attr->attribute_value.int_val = new_val.int_val;
        return SUCCESS;
    }
    return FAILURE;
}

/* see game_action.h */
int do_all_effects(item_t *item, char *action_name)
{
    game_action_t *action = get_action(item, action_name);
    if (action == NULL)
    {
        return FAILURE;
    }
    game_action_effect_t *tmp;
    for (tmp = action->effects; tmp != NULL; tmp = tmp->next)
    {
        int check = do_effect(tmp);
        if (check == FAILURE)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}
