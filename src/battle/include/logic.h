#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

#ifndef LOGIC_H
#define LOGIC_H

/*
 * Checks the targets of a move to see if they exist and are targetable
 *
 * Parameters:
 * - e: information about the enemy
 * Returns:
 * - 0 for if targetable and 1 for not being targetable
 */
int check_target(enemy_t *e);

/*
 * Checks the move's effectiveness against a certain target
 *
 * Parameters:
 * - p: information about the player
 * - e: information about the enemy
 * - move: information about the inputted move
 * Returns:
 * - an effectiveness value (either 0.5, 1, 1.5, or 2.0)
 */
double check_effectiveness(player_t *p, enemy_t *e, move_t *move);

/*
 * Modifies a certain STAT value
 *
 * Parameters:
 * - stat: A given stat for either player or enemy
 * - status: the given code for what to change
 *   - 0: HP
 *   - 1: STR
 *   - 2: DEF
 *   - 3: SPD
 * Returns:
 * - Returns 0 for success
 */
int mod_stat(stats_t *stat, int status);

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
int battle_over(player_t p, enemy_t *e);

/* Function detemines what player goes first
 *
 *  Inputs: 
 *      difficulty: difficulty level of the game
 *  Outputs:
 *      -1 - invalid input
 *      0 - user goes first
 *      1 - enemy goes first    */
int goes_first(int difficulty);

/* Uses the item with the given ID on the player
 *
 *  Inputs: 
 *      e - the enemy using the item
 *      p - the player being attacked
 *      ID - the ID of the item
 *  Outputs:
 *      returns item used    */
int enemy_use_item(enemy_t *e, player_t *p, int ID);

#endif
