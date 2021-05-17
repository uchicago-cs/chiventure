#include "npc_action.h"
#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "game-state/game_action.h"
#include "game-state/condition.h"

/* 
 * Creates a new condition in an npc with given inputs
 * Parameters:
 *  - npc: a pointer to the npc to be modified
 *  - attribute: a pointer to the attribute
 *  - new_value: the desired value of the attribute
 * Returns:
 *  - NULL if npc or attribute are NULL, the new condition if succcessful
 */
condition_t *npc_condition_new(npc_t *npc, attribute_t *attribute, attribute_value_t new_value);

/* 
 * Checks if all of the conditions of an action are met
 * Parameters:
 *  - npc: a pointer to the npc to check
 *  - action_name: the action name
 * Returns:
 *  SUCCESS if all conditions are met, FAILURE if not
 *  2 if action not possible
 */
int all_npc_conditions_met(npc_t *npc, char* action_name);