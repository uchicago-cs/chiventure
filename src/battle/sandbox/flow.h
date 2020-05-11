#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "structs.h"

/* Starts the beginning of a game
 *  PARAMETERS:
 *  - player: player data
 *  - enemy: enemy data
 *  OUTPUT:
 *  Returns 0 to show end of game
 */
int start_game(player_t *player, enemy_t *enemy);

/* Commences battle 
 * PARAMETERS:
 *  - player: player data
 *  - enemy: enemy data
 * OUTPUT:
 * returns 1 when battle is over or 0 when still in progress
 */
int battle(player_t *player, enemy_t *enemy);
