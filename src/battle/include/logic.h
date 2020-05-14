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
 * Returns:
 * - Returns 0 for success
 */
int mod_stat(stats_t *stat);

/*
 * Determines if a battle has reached its conclusion
 *
 * Parameters:
 * - p: information about the player
 * - e: information about the enemy
 * Returns:
 * - 0 for game over, 1 for game still in play
 */
int battle_over(player_t p, enemy_t *e);

#endif
