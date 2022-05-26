#include "game-state/condition.h"
#include "game-state/game.h"


/* helper for valid_condition. Checks if the attribute condition's
 * item to check actually exists within the game, and if the 
 * attribute itself is valid
 * 
 * Parameters:
 *  pointer to a game struct
 *  pointer to an attribute condition to check
 * 
 * Returns:
 *  SUCCESS if condition is valid
 *  ITEM_MODIFY_NULL if the item does not exist in the game or is null
 *  ATTRIBUTE_NULL if the attribute does not exist in the item or is null  
 */
int valid_attr_condition(game_t *game, attribute_condition_t *condition)
{

    item_t *check_item = get_item_from_game(game, condition->item->item_id);
    if (check_item == NULL)
        return ITEM_MODIFY_NULL; // item not in game

    attribute_t *check_attribute;
    if(condition->attribute_to_check == NULL)
        return ATTRIBUTE_NULL;

    check_attribute = get_attribute(condition->item,
                                    condition->attribute_to_check->attribute_key);
    if (check_attribute == NULL ||
        check_attribute != condition->attribute_to_check)
        return ATTRIBUTE_NULL; // item does not possess attribute

    return SUCCESS;
}

/* helper for valid_condition. Checks if the inventory condition's 
 * item and player to check actually exist within the game
 * 
 * Parameters:
 *  pointer to a game struct
 *  pointer to an inventory condiiton to check
 * 
 * Returns:
 *  SUCCESS if condition is valid
 *  ITEM_MODIFY_NULL if the item does not exist in the game or is null
 *  PLAYER_NULL if the player does not exist in the game or is null  
 */
int valid_inven_condition(game_t *game, inventory_condition_t *condition)
{

    item_t *check_item = get_item_from_game(game, condition->expected_item->item_id);
    if (check_item == NULL)
        return ITEM_MODIFY_NULL; // item not in game

    player_t *check_player = get_player(game, condition->player_to_check->player_id);
    if(check_player == NULL)
        return PLAYER_NULL; // player not in game

    return SUCCESS;
}

/* helper for valid_condition. Checks if the player actually exists within a
 * game.
 * 
 * Parameters:
 *  pointer to a game struct
 *  pointer to a level condiiton to check
 * 
 * Returns:
 *  SUCCESS if condition is valid
 *  PLAYER_NULL if the player does not exist in the game or is null
 */
int valid_level_condition(game_t *game, level_condition_t *condition)
{
    player_t *check_player = get_player(game, condition->player_to_check->player_id);
    if(check_player == NULL)
        return PLAYER_NULL; // player not in game

    return SUCCESS;
}

/* see condition.h */
int valid_condition(game_t *game, condition_t *condition)
{
    if(condition == NULL)
        return CONDITION_NULL;

    switch (condition->condition_tag)
    {
    case (ATTRIBUTE):
        return valid_attr_condition(game, condition->condition.attribute_type);
        break;
    case (INVENTORY):
        return valid_inven_condition(game, condition->condition.inventory_type);
        break;
    case (LEVEL):
        return valid_level_condition(game, condition->condition.level_type);
        break;
    default:
        // should never get to here
        return -1;
    }
}

/* See condition.h */
int free_condition(condition_t* condition)
{
    assert(condition != NULL);

    /* Free the condition regardless of the type */
    switch (condition->condition_tag)
    {
    case (ATTRIBUTE):
        free(condition->condition.attribute_type);
        break;
    case (INVENTORY):
        free(condition->condition.inventory_type);
        break;
    case (LEVEL):
        free(condition->condition.level_type);
        break;
    }

    /* Free the "condition wrapper" that is condition_t */ 
    free(condition);

    return SUCCESS;
}

/* see condition.h */
int delete_condition_llist(condition_list_t *conditions)
{
    condition_t *elt, *tmp;
    LL_FOREACH_SAFE(conditions, elt, tmp)
    {
        LL_DELETE(conditions, elt);
        switch (elt->condition_tag)
        {
        case (ATTRIBUTE):
            free(elt->condition.attribute_type);
            break;
        case (INVENTORY):
            free(elt->condition.inventory_type);
            break;
        }
        free(elt);
    }
    return SUCCESS;
}

/* see condition.h */
condition_t *attribute_condition_new(item_t *item_to_modify, char *attribute_name,
                                     attribute_value_t *new_value)
{
    attribute_t *attribute = get_attribute(item_to_modify, attribute_name);
    if (item_to_modify == NULL || attribute == NULL)
        return NULL;

    attribute_condition_t *new_condition = malloc(sizeof(attribute_condition_t));
    
    new_condition->item = item_to_modify;
    new_condition->attribute_to_check = attribute;
    new_condition->expected_value = new_value;

    condition_t *condition_wrapper = calloc(1, sizeof(condition_t));
    condition_wrapper->condition.attribute_type = new_condition;
    condition_wrapper->condition_tag = ATTRIBUTE;

    return condition_wrapper;
}

/* helper for check_condition. Matches the item's attribute with the
 * attribute to see if they are the same.
 * 
 * Parameters:
 *  the attribute condition to check
 * 
 * Returns:
 *  true if the item attribute correctly matches, false otherwise 
 *  */
bool check_attribute_condition(attribute_condition_t *condition)
{
    if (!condition)
        return false;
    //check if NULL attribute, return true if true
    attribute_t *actual_attribute = condition->attribute_to_check;
    if (actual_attribute == NULL)
        return true;

    switch (actual_attribute->attribute_tag)
    {
    case (DOUBLE):
        if (actual_attribute->attribute_value.double_val ==
            condition->expected_value->double_val)
            return true;
        break;
    case (BOOLE):
        if (actual_attribute->attribute_value.bool_val ==
            condition->expected_value->bool_val)
            return true;
        break;
    case (CHARACTER):
        if (actual_attribute->attribute_value.char_val ==
            condition->expected_value->char_val)
            return true;
        break;
    case (STRING):
        if (!strcmp(actual_attribute->attribute_value.str_val,
                    condition->expected_value->str_val))
            return true;
        break;
    case (INTEGER):
        if (actual_attribute->attribute_value.int_val ==
            condition->expected_value->int_val)
            return true;
        break;
    }
    return false;
}

/* see game_action.h */
condition_t *inventory_condition_new(player_t *player, item_t *expected_item)
{
    if (player == NULL || expected_item == NULL)
        return NULL;

    inventory_condition_t *new_condition = malloc(sizeof(inventory_condition_t));
    new_condition->player_to_check = player;
    new_condition->expected_item = expected_item;

    condition_t *condition_wrapper = calloc(1, sizeof(condition_t));
    condition_wrapper->condition.inventory_type = new_condition;
    condition_wrapper->condition_tag = INVENTORY;

    return condition_wrapper;
}

/* helper for check_condition. Checks if the condition's specified item
 * exists in the player's inventory.
 * 
 * Parameters:
 *  the inventory condition to check
 * 
 * Returns:
 *  true if item is in inventory, false otherwise
 */
bool check_inventory_condition(inventory_condition_t *condition)
{
    return item_in_inventory(condition->player_to_check, condition->expected_item);
}

/* see game_action.h */
condition_t *level_condition_new(player_t *player, int level_required)
{
    if (player == NULL)
        return NULL;

    level_condition_t *new_condition = malloc(sizeof(level_condition_t));
    new_condition->player_to_check = player;
    new_condition->level_required = level_required;

    condition_t *condition_wrapper = calloc(1, sizeof(condition_t));
    condition_wrapper->condition.level_type = new_condition;
    condition_wrapper->condition_tag = LEVEL;

    return condition_wrapper;
}

/* helper for check_condition. Checks if the player's level meets or exceeds
 * the condition's required level
 * 
 * Parameters:
 *  the level condition to check
 * 
 * Returns:
 *  true if the player's level is greater than or equal to the
 *  required level, false otherwise
 */
bool check_level_condition(level_condition_t *condition)
{
    return (get_level(condition->player_to_check) >= condition->level_required);
}

/* see game_action.h */
bool check_condition(condition_t *condition)
{
    switch (condition->condition_tag)
    {
    case (ATTRIBUTE):
        return check_attribute_condition(condition->condition.attribute_type);
    case (INVENTORY):
        return check_inventory_condition(condition->condition.inventory_type);
    case (LEVEL):
        return check_level_condition(condition->condition.level_type);
    }
}

/* see game_action.h */
bool all_conditions_met(condition_list_t *cond_list)
{
    if (cond_list == NULL)
        return true; // no conditions to check
    condition_t *tmp = cond_list;
    while (tmp != NULL) // iterate through all conditions
    {
        if (!(check_condition(tmp)))
            return false;
        tmp = tmp->next;
    }
    // all conditions met
    return true;
}
