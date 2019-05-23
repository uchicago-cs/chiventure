/*
 * Lindsey Hsi, Patrick Koopmans, Jessica Xia
 * A player structure
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "game_state_common.h"
#include "item.h"

#define ITER_ALL_PLAYERS(game, curr_player) player_t *ITTMP_PLAYER; HASH_ITER(hh, (game)->all_players, (curr_player), ITTMP_PLAYER)

/* A player in game */
typedef struct player {
    /* hh is used for hashtable, as provided in uthash.h*/
    UT_hash_handle hh;
    char *player_id;
    int level;
    int health;
    int xp;
    item_hash_t inventory;
} player_t;

typedef struct player_t *player_hash_t;

/*
 * Initializes a player
 *
 * Parameters:
 *  p: A player. Must point to already allocated memory.
 *  health: The starting health of the player
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int player_init(player_t *plyr, int health);

/*
 * Allocates a new player
 *
 * Parameters:
 *  health: The starting health of the player
 *
 * Returns:
 *  Pointer to allocated player
 */
player_t *player_new(int health);

/*
 * Frees resources associated with a player
 *
 * Parameters:
 *  plyr: the player to be freed
 *
 * Returns:
 *  SUCCESS if successful
 */
int player_free(player_t *plyr);

/* Deletes a hashtable of players
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of players that need to be deleted
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
void delete_all_players(player_hash_t players);

/*
 * Returns the health of a player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, the player's health
 */
int get_health(player_t *plyr);

/*
 * Changes the health of the player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, remaining health
 */
int change_health(player_t *plyr, int change, int max);

/*
 * Returns the level of the player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, the player's level
 */
int get_level(player_t *plyr);

/*
 * Increments the level of the player by given amt
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, the new level
 */
int change_level(player_t *plyr, int change);

/*
 * Returns the experience points of the player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, the player's experience
 */
int get_xp(player_t *plyr);

/*
 * Changes the experience (xp) points of the player
 *
 * Parameters:
 *  plyr: the player
 * 	points: how much to change xp (positive or negative)
 *
 * Returns:
 *  int, the player's new xp
 */
int change_xp(player_t *plyr, int points);

/*
 * Returns the inventory list
 *
 * Parameters:
 * 	plyr: the player
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t get_inventory(player_t *plyr);

/* Adds a player to the given hashtable of players
 *
 * Parameters:
 *  hashtable the player is added to
 *  player id
 *  pointer to the player
 * Returns:
 *  SUCCESS if successful, exits if failed
 */
int add_player_to_hash(player_hash_t all_players, char *player_id, player_t *player);

/* Adds an item to the given player
 *
 * Parameters:
 *  player struct
 *  item struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_item_to_player(player_t *player, item_t *item);

#endif
