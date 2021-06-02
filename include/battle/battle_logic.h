#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include "battle/battle_state.h"
#include "battle/battle_structs.h"
#include "battle/battle_common.h"
#include "battle/battle_flow_structs.h"

/*
 * Checks the targets of a move to see if they exist and are targetable
 *
 * Parameters:
 * - b: information about the battle
 * - target: name of the person
 * Returns:
 * - Returns the combatant selected
 */
combatant_t *check_target(battle_t *b, char *target);

/*
 * Determines if a battle has reached its conclusion
 *
 * Parameters:
 * - b: information about the battle
 * Returns:
 *  A battle status based on the combatants of the battle
 */
battle_status_t battle_over(battle_t *b);

/* 
 * Function detemines if the battle_player goes first
 *
 *  Parameters: 
 *  - b: information about the battle
 *  Returns:
 *  PLAYER or ENEMY which shows who goes first
 */
turn_t goes_first(battle_t *b);

/* 
 * Finds the desired battle_item to be used
 * Parameters:
 *    inventory - a battle_player or enemy's inventory
 *    input - the char name of the desired battle_item
 * Returns:
 *    Returns a pointer to the desired battle_item
 */
battle_item_t *find_battle_item(battle_item_t *inventory, char *input);

/* This ensures that the user's inputted move exists.
 * Parameters:
 *  ctx: main structure of the battle
 *  move_name: name of the desired move
 * Returns:
 *  a pointer to the found move or NULL for no move 
 */ 
move_t *find_player_move(battle_ctx_t *ctx, char *move_name);

/*
 * Consumes a battle_item for the said combatant
 * Parameters:
 *  c - information about the combatant
 *  item - the battle_item to be consumed
 * Returns:
 *  Always returns 0
 */
int consume_battle_item(combatant_t *c, battle_item_t *item);

/* Uses the battle_item with the given ID on the battle_player
 * ! currently checks to see if the battle_item is a weapon or consumable !
 *
 *  Parameters: 
 *   c - combatant information
 *   battle - battle information   
 *   name - the name of the battle_item
 *  Returns:
 *   SUCCESS or FAILURE
 */
int use_battle_item(combatant_t *c, battle_t *battle, char *name);

/* Removes a battle item from a combatant's list of battle items
 *
 * Parameters:
 * - c: the combatant
 * - item: the battle item to remove
 * Returns:
 * - SUCCESS or FAILURE
 */
int remove_battle_item(combatant_t *c, battle_item_t *item);

/* Awards xp to the battle_player 
 * Parameters:
 *  - stats: stats of the battle_player
 *  - xp: amount of xp to be rewarded
 * Returns:
 *  Always returns 0
 */
int award_xp(stat_t *stats, double xp);

/* Adds new temporary status changes from an item. Note: Does
 *     not yet change the number of turns left, because items
 *     do not have that supported yet.
 * Parameters:
 * - sc: a pointer to a stat_changes struct in memory
 * - item: a pointer to an item struct in memory
 * returns:
 * - SUCCESS for successful completion
 * - FAILURE for unsuccessful completion
 */
int stat_changes_add_item_node(stat_changes_t *sc, battle_item_t *item);

#endif
