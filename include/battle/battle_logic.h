#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include "battle/battle_state.h"
#include "battle/battle_structs.h"

/*
 * Checks the targets of a move to see if they exist and are targetable
 *
 * Parameters:
 * - b: information about the battle
 * - target: name of the person
 * Returns:
 * - Returns a true or false bool for if the target exists
 */
bool check_target(battle_t *b, char *target);

typedef enum battle_status
{
    BATTLE_IN_PROGRESS,
    BATTLE_VICTOR_PLAYER,
    BATTLE_VICTOR_ENEMY
} battle_status_t;

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
 * Function detemines if the player goes first
 *
 *  Parameters: 
 *  - b: information about the battle
 *  Returns:
 *  PLAYER or ENEMY which shows who goes first
 */
turn_t goes_first(battle_t *b);

/* 
 * Finds the desired item to be used
 * 	Parameters:
 *   inventory - an player or enemy's inventory
 * 	 id - the id number of the desired item
 * 	Returns:
 * 	 returns a pointer to the desired item 
 */
item_t *find_item(item_t *inventory, int id);

/*
 * Consumes an item for the said combatant
 * Parameters:
 *  c - information about the combatant
 *  item - the item to be consumed
 * Returns:
 *  Always returns 0
 */
int consume_item(combatant_t *c, item_t *item);

/* Uses the item with the given ID on the player
 * ! Currently assumes that this is a battle item !
 *
 *  Parameters: 
 *   c - combatant information
 *   inv - inventory of the player
 *   id - the number id of the item
 *  Returns:
 *   0 - successfully used item
 *   1 - there is nothing in the inventory
 *   2 - item does not exist or the player does not have any more
 */
int player_use_item(combatant_t *c, item_t *inv, int id);

/* Awards xp to the player 
 * Parameters:
 *  - stats: stats of the player
 *  - xp: amount of xp to be rewarded
 * Returns:
 *  0 for success
 */
int award_xp(stat_t *stats, double xp);

#endif
