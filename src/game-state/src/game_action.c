#include "game-state/game_action.h"

/* See common_game_action.h */
int game_action_init(game_action_t *new_action, char *act_name,
                     char* success_str, char* fail_str)
{
    assert(new_action != NULL);
    if(new_action == NULL)
    {
        return FAILURE;
    }
    strncpy(new_action->action_name, act_name, strlen(act_name));
    new_action->conditions = NULL; //by UTLIST rules
    new_action->effects= NULL; //by UTLIST rules
    strncpy(new_action->success_str, success_str, strlen(success_str));
    strncpy(new_action->fail_str, fail_str, strlen(fail_str));

    return SUCCESS;
}


/* see common_game_action.h */
game_action_t *game_action_new(char *action_name, char* success_str, char* fail_str)
{
    game_action_t *new_action = malloc(sizeof(game_action_t));
    new_action->action_name = malloc(MAX_ID_LEN * sizeof(char));
    new_action->success_str = malloc(MAX_MSG_LEN * sizeof(char));
    new_action->fail_str = malloc(MAX_MSG_LEN * sizeof(char));

    int check = game_action_init(new_action, action_name, success_str, fail_str);

    if (new_action == NULL || new_action->action_name == NULL)
    {

        fprintf(stderr,
                "game_action_new(): game action struct not properly malloced");
        return NULL;

    }

    if(check != SUCCESS)
    {
        return NULL;
    }

    return new_action;

}

// ---------------------------------------------------------------------------

/* see game_action.h */
game_action_t *get_action(item_t *item, char* action_name)
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
int add_action(item_t* item, char *action_name, char* success_str, char* fail_str)
{
    game_action_t* check = get_action(item, action_name);
    if (check != NULL)
    {
        return FAILURE;
    }
    game_action_t* action = game_action_new(action_name, success_str, fail_str);
    HASH_ADD_KEYPTR(hh, item->actions, action_name, strlen(action_name), action);
    return SUCCESS;
}


/* see game_action.h */
int possible_action(item_t *item, char* action_name)
{
    game_action_t* possible_action = get_action(item, action_name);
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
int add_action_condition(item_t *item, game_action_t *action,
                         item_t *cond_item, attribute_t *cond_attribute, attribute_value_t cond_value)
{
    if (item == NULL)
    {
        return ITEM_SRC_NULL;
    }
    if (cond_item == NULL)
    {
        return ITEM_MODIFY_NULL;
    }

    game_action_t *ret_action = get_action(item, action->action_name);
    if (ret_action == NULL)
    {
        return ACTION_NULL;
    }

    game_action_condition_t *new_condition = condition_new(item, cond_attribute, cond_value);

    LL_APPEND(action->conditions, new_condition);

    return SUCCESS;
}

/* see game_action.h */
int delete_action_condition_llist(action_condition_list_t *conditions)
{
    game_action_condition_t *elt, *tmp;
    LL_FOREACH_SAFE(conditions, elt, tmp)
    {
        LL_DELETE(conditions, elt);
        free(elt);
    }
    return SUCCESS;
}

/* see game_action.h */
game_action_condition_t *condition_new(item_t *item_to_modify, attribute_t *attribute,
                                       attribute_value_t new_value)
{
    if (item_to_modify == NULL || attribute == NULL)
    {
        return NULL;
    }

    game_action_condition_t *new_condition = malloc(sizeof(game_action_condition_t));
    new_condition->item = item_to_modify;
    new_condition->attribute_to_check = attribute;
    new_condition->expected_value = new_value;

    return new_condition;
}

/* see game_action.h */
bool check_condition(game_action_condition_t *condition)
{
    //check if NULL attribute, return true if true
    attribute_t* actual_attribute = condition->attribute_to_check;
    if(actual_attribute == NULL)
    {
        return true;
    }

    switch(actual_attribute->attribute_tag)
    {
    case(DOUBLE):
        if (actual_attribute->attribute_value.double_val ==
                condition->expected_value.double_val)
        {
            return true;
        }
        break;
    case(BOOLE):
        if (actual_attribute->attribute_value.bool_val ==
                condition->expected_value.bool_val)
        {
            return true;
        }
        break;
    case(CHARACTER):
        if (actual_attribute->attribute_value.char_val ==
                condition->expected_value.char_val)
        {
            return true;
        }
        break;
    case(STRING):
        if (!strcmp(actual_attribute->attribute_value.str_val,
                    condition->expected_value.str_val))
        {
            return true;
        }
        break;
    case(INTEGER):
        if (actual_attribute->attribute_value.int_val ==
                condition->expected_value.int_val)
        {
            return true;
        }
        break;
    }
    return false;
}

/* see game_action.h */
int all_conditions_met(item_t* item, char* action_name)
{
    //call allowed action to see if the action exists
    if (possible_action(item, action_name))
    {
        return 2;
    }

    game_action_t *ret_action = get_action(item, action_name);

    game_action_condition_t *tmp = ret_action->conditions;
    while (tmp != NULL)
    {
        if(!(check_condition(tmp)))
        {
            return FAILURE;
        }
        tmp = tmp->next;
    }

    return SUCCESS;
}


/* See game_action.h */
list_action_type_t *find_act(list_action_type_t *head, action_type_t *a)
{
    list_action_type_t *delete_node, *temp;
    delete_node = LL_SEARCH_SCALAR(head,temp,act,a);
    return delete_node;
}


/* See game_action.h */
int delete_action(list_action_type_t **head, list_action_type_t *act)
{
    if (*head == NULL) 
    {
        printf("head null!\n");
        return -1;
    }

    LL_DELETE(*head, act);
    return SUCCESS;
}


// ------------------------------------- EFFECTS -------------------------------------

/* see game_action.h */
//we either use item_to_add or action as action is loacted within item_to_add
int add_action_effect(game_action_t *action, item_t *item_to_add, attribute_t *attribute, attribute_value_t new_value)
{
    if(action == NULL)
    {
        return ACTION_NULL;
    }
    if(item_to_add == NULL)
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
    switch(attr->attribute_tag)
    {
    case(DOUBLE):
        attr->attribute_value.double_val = new_val.double_val;
        return SUCCESS;
    case(BOOLE):
        attr->attribute_value.bool_val = new_val.bool_val;
        return SUCCESS;
    case(CHARACTER):
        attr->attribute_value.char_val = new_val.char_val;
        return SUCCESS;
    case(STRING):
        attr->attribute_value.str_val = new_val.str_val;
        return SUCCESS;
    case(INTEGER):
        attr->attribute_value.int_val = new_val.int_val;
        return SUCCESS;
    }
    return FAILURE;
}

/* see game_action.h */
int do_all_effects(item_t *item, char* action_name)
{
    game_action_t* action = get_action(item, action_name);
    if(action == NULL)
    {
        return FAILURE;
    }
    game_action_effect_t* tmp;
    for(tmp = action->effects; tmp != NULL; tmp = tmp->next)
    {
        int check = do_effect(tmp);
        if(check == FAILURE)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}

