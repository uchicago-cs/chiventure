#ifndef _COMMON_PLAYER_H
#define _COMMON_PLAYER_H

#include "player.h"

/* Adds a player to the given hashtable of players
 *
 * Parameters:
 *  hashtable the player is added to
 *  player id
 *  pointer to the player
 * Returns:
 *  SUCCESS if successful, exits if failed
 */
//int add_player_to_hash(player_hash_t all_players, char *player_id, player_t *player);
int add_player_to_hash(game_t *game, player_t *player);
#endif
