#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include <stdlib.h>
#include <stdio.h>
#include "battle/battle_structs.h"
#include "battle/battle_state.h"

/*
 * Checks the targets of a move to see if they exist and are targetable
 *
 * Parameters:
 * - b: information about the battle
 * - target: name of the person
 * Returns:
 * - 0 for if targetable and 1 for not being targetable/not found
 */
int check_target(battle_t *b, char *target);

/*
 * Determines if a battle has reached its conclusion
 *
 * Parameters:
 * - p: information about the player
 * - e: information about the enemy
 * Returns:
 * - 0 for game still in play
 * - 1 for game over due to enemy
 * - 2 for game over due to player
 * - -1 for an error with not passing conditions
 */
int battle_over(combatant_t *p, combatant_t *e);

/* 
Function detemines what player goes first
 *
 *  Parameters: 
 *  - difficulty: difficulty level of the game
 *  Returns:
 *  -1 - invalid input
 *  0 - user goes first
 *  1 - enemy goes first    
 */
int goes_first(double p_speed, double e_speed);

/* 
 * Finds the desired item to be used
 * 	Parameters:
 *   inventory - an player or enemy's inventory
 * 	 ID - the ID number of the desired item
 * 	Returns:
 * 	 temp->item - pointer to the desired item 
 */
item_t *find_item(item_t *inventory, int ID);

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
 *   ID - the ID of the item
 *  Returns:
 *   0 - successfully used item
 *   1 - there is nothing in the inventory
 *   2 - item does not exist or the player does not have any more
 */
int player_use_item(combatant_t *c, item_t *inv, int ID);

/* Awards xp to the player 
 * Parameters:
 *  - stats: stats of the player
 *  - xp: amount of xp to be rewarded
 * Returns:
 *  0 for success
 */
int award_xp(stat_t *stats, double xp);

#endif
