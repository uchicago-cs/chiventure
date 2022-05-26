#ifndef _CONDITION_H
#define _CONDITION_H

#include "game_state_common.h"
#include "player.h"
#include "item.h"

/* Forward declaration. Full typedef can be found in game.h */
 typedef struct game game_t;

typedef struct attribute_condition{
    item_t *item;
    attribute_t *attribute_to_check;
    attribute_value_t *expected_value;
} attribute_condition_t;

typedef struct inventory_condition{
    player_t *player_to_check;
    item_t *expected_item;
} inventory_condition_t;

typedef struct level_condition{
    int level_required;
    player_t *player_to_check;
} level_condition_t;

typedef union condition_value{
    attribute_condition_t* attribute_type;
    inventory_condition_t* inventory_type;
    level_condition_t* level_type;
} condition_value_t;

enum condition_tag {ATTRIBUTE,INVENTORY, LEVEL};

typedef struct condition{
    condition_value_t condition;
    enum condition_tag condition_tag;
    struct condition *next;
} condition_t;

/* This typedef is to distinguish between condition_t
* pointers which are used to point to the condition_t structs
* in the traditional sense, and those which are used to enable UTLIST functionality
* on the condition_t structs as specified in src/common/include
*/
typedef struct condition condition_list_t;

/* valid_condition checks with the game given to make sure that the condition's
 * inputted variables are valid
 * 
 * Parameters:
 *   the game to check against
 *   the condition
 * 
 * Returns:
 *   ITEM_MODIFY_NULL if item does not exist in game
 *   ATTRIBUTE_NULL if attribute is null or does not exist in item
 *   PLAYER_NULL if player does not exist in game
 *   CONDITION_NULL if condition is null
 *   SUCCESS otherwise
 */
int valid_condition(game_t *game, condition_t *condition);

/* free_condition: Frees a given condition without freeing the identifying fields
 *                 This includes the attribute and item (for attribute conditions),
 *                 the player and item (for inventory conditions) or
 *                 solely the player (for level conditions)
 *                 
 * 
 * Inputs:
 *      - Condition: The given condition to free
 * 
 * Returns: 
 *      - Will always output SUCCESS
 */
int free_condition(condition_t* condition);

/* delete_condition_llist frees a linked list of action conditions
 * Parameters:
 *  linked list of conditions
 *
 * Returns:
 *  always returns SUCCESS
 */
int delete_condition_llist(condition_list_t *conditions);

/* attribute_condition_new() creates a new attribute condition in an item with given inputs
 * Parameters:
 *  a pointer to the item to be modified
 *  a string representing name of the attribute to add a condition on
 *  the desired value of the attribute
 *  the value to check against
 * Returns:
 *  NULL if item or attribute are NULL, the new condition if succcessful
 */
condition_t *attribute_condition_new(item_t *item_to_modify, char *attribute_name,
				       attribute_value_t *new_value);


/* inventory_condition_new() creates a new inventory condition in an item with given inputs
 * Parameters:
 *  a pointer to the player whose inventory to check
 *  a pointer to the item
 * Returns:
 *  NULL if player or item are NULL, the new condition if succcessful
 */
condition_t *inventory_condition_new(player_t *player, item_t *expected_item);


/* level_condition_new() creates a new level condition 
 * Parameters:
 *  a pointer to the player whose level to check
 *  the required level
 * Returns:
 *  NULL if player is NULL, the new condition if succcessful
 */
condition_t *level_condition_new(player_t *player, int required_level);

/* check_condition() checks if the actual attribute of an item is equal
 * to the desired attribute
 * Parameters:
 *  a pointer to the item to check
 *  the desired attribute
 * Returns:
 *  true if desired attribute matches the actual, false if not
 */
bool check_condition(condition_t *condition);


/* all_conditions_met() checks if all of the conditions of an action are met
 * Parameters:
 *  a pointer to the head of a condition list
 * Returns:
 *  true if all conditions are met, false if not
 */
bool all_conditions_met(condition_list_t *cond_list);


#endif
