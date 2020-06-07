/*
 * Lindsey Hsi, Patrick Koopmans, Jessica Xia
 * A player structure
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "game_state_common.h"
#include "item.h"
#include "playerclass/class.h"


/* A player in game */
typedef struct player {
    /* hh is used for hashtable, as provided in uthash.h*/
    UT_hash_handle hh;
    char *player_id;
    int level;
    int health;
    int xp;
    class_t player_class;
    item_hash_t *inventory;
} player_t;

/* This typedef is to distinguish between player_t pointers which are 
* used to point to the player_t structs themselves, and those which are used
* to hash player_t structs with the UTHASH macros as specified
* in src/common/include */
typedef struct player player_hash_t;

/*
 * Initializes a player with level 1, given health, and 0 experience
 *
 * Parameters:
 *  plyr: A player. Must point to already allocated memory.
 *  health: The starting health of the player
 *  player_id: the unique string ID of the player. currently
 *   this will always be "1" since there is only one player
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int player_init(player_t *plyr, char* player_id, int health);

/*
 * Allocates a new player
 *
 * Parameters:
 *  health: The starting health of the player
 *  player_id: the unique string ID of the player
 *
 * Returns:
 *  Pointer to allocated player
 */
player_t *player_new(char* player_id, int health);

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
 *
 * Returns:
 *  SUCCESS if successful
 */
int delete_all_players(player_hash_t* players);

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
 *  change: the desired amount to increment in player level
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
 *  points: how much to change xp (positive or negative)
 *
 * Returns:
 *  int, the player's new xp
 */
int change_xp(player_t *plyr, int points);

/*
 * Returns the inventory list
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t* get_inventory(player_t *plyr);


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

/* Removes an item from the given player
 * Note that the memory associated with this item is not freed
 * 
 * Parameters:
 *  player struct
 *  item struct
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int remove_item_from_player(player_t *player, item_t *item);

/*
 * Function to get a linked list (utlist) of all the items in the player's inventory
 *
 * Parameters:
 *  player
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_inventory(player_t *player);

/*
 * Assigns a table of stats to a player
 *
 * Parameters:
 *  player: the players
 *  sh: the stats hashtable
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int assign_stats_player(player_t *plyr, stats_hash_t *sh);

#endif
