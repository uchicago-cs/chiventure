#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include <stdlib.h>
#include <stdio.h>
#include "battle_structs.h"

/*
 * Checks the targets of a move to see if they exist and are targetable
 *
 * Parameters:
 * - e: information about the enemy
 * Returns:
 * - 0 for if targetable and 1 for not being targetable
 *
 * NOTE: Unsure of how this function will play into our code
int check_target(enemy_t *e); */

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
int battle_over(player_t *p, enemy_t *e);

/* Function detemines what player goes first
 *
 *  Inputs: 
 *      difficulty: difficulty level of the game
 *  Outputs:
 *      -1 - invalid input
 *      0 - user goes first
 *      1 - enemy goes first    */
int goes_first(double p_speed, double e_speed);

/* Uses the item with the given ID on the player
 *
 *  Inputs: 
 *      e - the enemy using the item
 *      p - the player being attacked
 *      ID - the ID of the item
 *  Outputs:
 *      returns item used    */
item_t *enemy_use_item(enemy_t *e, int ID);

/* Awards xp to the player 
 * Parameters:
 *  - stats: stats of the player
 *  - xp: amount of xp to be rewarded
 * Returns:
 *  0 for success
 */
    int award_xp(stats_t *stats, double xp);

#endif
