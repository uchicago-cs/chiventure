/*
 * Lindsey Hsi, Patrick Koopmans, Jessica Xia
 * A player structure
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utlist.h"
#include "uthash.h"
#include "item.h"

#define SUCCESS 1
#define FAILURE 1

/* A player in game */
typedef struct player {
    /* hh is used for hashtable, as provided in uthash.h*/
    UT_hash_handle hh;
    int player_id;
    char username[20];
    int level;
    int health;
    int xp;
    item_hash_t *inventory;
    item_hash_t *clothes;
} player_t;

typedef struct player* player_hash_t;

/*
 * Initializes a player
 *
 * Parameters:
 *  p: A player. Must point to already allocated memory.
 *  health: The starting health of the player
 *
 * Returns:
 *  0 on success, 1 if an error occurs.
 */
int player_init(player_t* plyr, int health);

/*
 * Allocates a new player
 *
 * Parameters:
 *  health: The starting health of the player
 *
 * Returns:
 *  Pointer to allocated player
 */
player_t* player_new(int health);

/*
 * Frees resources associated with a player
 *
 * Parameters:
 *  plyr: the player to be freed
 *
 * Returns:
 *  always returns 0
 */
int player_free(player_t* plyr);

/* Deletes a hashtable of players
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of players that need to be deleted
 * Returns:
 *  1 if successful, 0 if failed
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
int get_health(player_t* plyr);

/*
 * Changes the health of the player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, remaining health
 */
int change_health(player_t* plyr, int change, int max);

/*
 * Returns the level of the player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, the player's level
 */
int get_level(player_t* plyr);

/*
 * Increments the level of the player by one
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, the new level
 */
int change_level(player_t* plyr, int change);

/*
 * Returns the experience points of the player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, the player's experience
 */
int get_xp(player_t* plyr);

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
int change_xp(player_t* plyr, int points);

/*
 * Adds an item to the player's inventory
 *
 * Parameters:
 *  plyr: the player
 * 	points: how much to change xp (positive or negative)
 *
 * Returns:
 *  int, 1 for success, 0 for failure
 */
int add_clothes_item(item_t* item, player_t* plyr);

/*
 * Adds an item to the player's inventory
 *
 * Parameters:
 *  item: the item too add
 * 	plyr: the plyaer
 *
 * Returns:
 *  int, 1 for success, 0 for failure
 */
int add_inventory_item(item_t* item, player_t* plyr);

/*
 * Returns the inventory list
 *
 * Parameters:
 * 	plyr: the player
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t get_inventory(player_t* plyr);

/*
 * Returns the inventory list
 *
 * Parameters:
 * 	plyr: the player
 *
 * Returns:
 *  hashtable of items, the clothes
 */
item_hash_t get_clothes(player_t* plyr);


#endif
