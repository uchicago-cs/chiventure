#include "game_action.h"
#include "common-item.h"

/* See game_action.h */
int game_action_init(game_action_t *new_action, char *act_name, char* success_str, char* fail_str)
{
    assert(new_action != NULL);

    strncpy(new_action->action_name, act_name, strlen(act_name));
    // new_action->action_type = act_type; //REMOVED action_type
    new_action->conditions = NULL; //by UTLIST rules
    new_action->effects= NULL; //by UTLIST rules
    strncpy(new_action->success_str, success_str, strlen(success_str));
    strncpy(new_action->fail_str, fail_str, strlen(fail_str));

    return SUCCESS;
}


/* see game_action.h */
game_action_t *game_action_new(char *action_name, char* success_str, char* fail_str)
{
    game_action_t *new_action = malloc(sizeof(game_action_t));
    new_action->action_name = malloc(MAX_ID_LEN * sizeof(char));
    // new_action->action_type = malloc(sizeof(action_type_t)); //REMOVED action_type

    int check = game_action_init(new_action, action_name, success_str, fail_str);

    if (new_action == NULL || new_action->action_name == NULL) {

        fprintf(stderr,
            "game_action_new(): game action struct not properly malloced");
        return NULL;

    }

    if(check != SUCCESS) {
        return NULL;
    }

    return new_action;

}

// ---------------------------------------------------------------------------

/* see game_action.h */
game_action_t *get_action(item_t *item, char* action_name) {
    game_action_t *action;
    HASH_FIND(hh, item->actions, action_name, strlen(action_name), action);
    if (action == NULL) {
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
        //fprintf(stderr, "Error: this action is already present.\n");
        return FAILURE;
    }
    game_action_t* action = game_action_new(action_name, success_str, fail_str);
    HASH_ADD_KEYPTR(hh, item->actions, action_name, strlen(action_name), action);
    return SUCCESS;
}



/* see game_action.h */
bool possible_action(item_t *item, char* action_name)
{
    game_action_t* possible_action = get_action(item, action_name);
    if (possible_action == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }   
}

// ------------------------------------- CONDITIONS -------------------------------------

/* see game_action.h */
int add_action_condition(item_t *item, game_action_t *action,
			 item_t *cond_item, attribute_t *cond_attribute, attribute_value_t *cond_value)
{
    if (item == NULL) {
        return 1;
    }
    if (cond_item == NULL) {
        return 3;
    }
    game_action_condition_t *new_condition = malloc(sizeof(game_action_condition_t));
    new_condition->item = cond_item;
    new_condition->attribute_to_check = cond_attribute;
    new_condition->expected_value = *cond_value;

    game_action_t *ret_action;
    HASH_FIND(hh, item->actions, action->action_name, strlen(action->action_name), ret_action);
    if (ret_action == NULL) {
        return 2;
    }

    game_action_condition_t *tmp = *(action->conditions);
    while (tmp != NULL) {
      tmp = tmp->next;
    }

    tmp = new_condition;
    return 0;
}


/* see game_action.h */
bool check_condition(item_t *item, game_action_condition_t *condition)
{
    //check if NULL attribute, return true if true
    attribute_t* actual_attribute = condition->attribute_to_check;
    if(actual_attribute == NULL) 
        return true;
    char* attribute_name = actual_attribute->attribute_key;

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
    //call possible action to see if the action exists
    if (!(possible_action(item, action_name))) 
    {
        return 2;
    }

  //PATRICK
}

// ------------------------------------- EFFECTS -------------------------------------

//header unwritten
int add_effect(game_t *game, char* room_id, char* action, char* item_src, char* item_modify, attribute_t *attribute, attribute_value_t new_value)
{
    room_t *room = find_room_from_game(game, room_id);
    if(room == NULL)
    {
        return 2;
    }
    item_t *item_src = get_item_in_room(room, item_id);
    if(item_src == NULL)
    {
        return 3;
    }
    item_t *item_modify = get_item_in_room(room, item_id);
    if(item_modify == NULL)
    {
        return 4;
    }
    game_action_t *action = get_action(item_src, action);
    if(action == NULL)
    {
        return 5;
    }
    int check = add_action_effect(action, item_modify, attribute, new_value);
    
    return check;
}
/* see game_action.h */
int add_action_effect(game_action_t *action, item_t *item_to_modify, attribute_t *attribute, attribute_value_t new_value) 
{
    //create effect
    game_action_effect_t *effect = create_effect(item_to_modify, attribute, new_value);
    
    //ADD TO LIST IDK HOW?

    return SUCCESS;
}

/* see game_action.h */
game_action_effect_t *create_effect(item_t *item_to_modify, attribute_t *attribute, attribute_value_t new_value) 
{
    game_action_effect_t *effect = malloc(sizeof(game_action_effect_t));
    effect->attribute_to_modify = attribute;
    effect->new_value = new_value;
    effect->next = NULL;

    return effect;
}

/* see game_action.h */
bool affect_effect(game_action_effect_t *effect) 
{
    item_t *item = effect->item;
    attribute_t *attr = effect->attribute_to_modify;
    attribute_value_t val = effect->new_value;
    switch(attr->attribute_tag)
    {
        case(DOUBLE):
            if(set_double_attr(item, attr->attribute_key, val.double_val))
            {
                return true;
            }
            break;
        case(BOOLE):
            if(set_bool_attr(item, attr->attribute_key, val.bool_val))
            {
                return true;
            }
            break;
        case(CHARACTER):
            if(set_char_attr(item, attr->attribute_key, val.char_val))
            {
                return true;
            }
            break;
        case(STRING):
            if(set_str_attr(item, attr->attribute_key, val.str_val))
            {
                return true;
            }
            break;
        case(INTEGER):
            if(set_int_attr(item, attr->attribute_key, val.int_val))
            {
                return true;
            }
            break;
    }
    return false;
}
