#ifndef BATTLE_FEEDBACK_H
#define BATTLE_FEEDBACK_H

#include "battle_structs.h"

/* Prints out the beginning of a game 
 * PARAMETERS:
 *  - e: enemy struct which is used to display enemy name
 * RETURNS:
 *    1 indicating successful print
 */
int announce_game(enemy_t *e);

/* Prints out the attack used
 * PARAMETERS:
 *  - attack: name of the attack used
 *  - e: enemy stats
 *  RETURNS:
 *    1 for success
 */
int announce_attack(char *attack, enemy_t *e);

/* Prints out the amount of damage a move did
 * PARAMETERS:
 *  - d: amount of damage done
 *  RETURNS:
 *    1 for success
 */
int announce_damage(int d);

#endif
