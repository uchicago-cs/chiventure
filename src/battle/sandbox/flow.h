#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "structs.h"

/* Starts the beginning of a game
 *  PARAMETERS:
 *  enemy: the stats and name of the enemy encountered
 *  OUTPUT:
 *  Returns 0 to show end of game
 */
int start_game(enemy_t enemy);

/* Commences battle 
 * NO PARAMETERS
 * OUTPUT:
 * returns 1 when battle is over or 0 when still in progress
 */
int battle();
