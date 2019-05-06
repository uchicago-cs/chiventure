/*
 * Lindsey Hsi, Patrick Koopmans, Jessica Xia
 * A player structure
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include <stdbool.h>

/* A player in game */
typedef struct player{
    char username[20];
    int level;
    int health;
    int xp;
    llist* inventory;
    llist* clothes;
} player_t;

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
int change_health(player_t* plyr);

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
int change_level(player_t* plyr);

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
 * Adds an object to the player's inventory
 *
 * Parameters:
 *  plyr: the player 
 * 	points: how much to change xp (positive or negative)
 *
 * Returns:
 *  int, 1 for success, 0 for failure
 */
int add_clothes_object(object_t* item, player_t* plyr);

/*
 * Adds an object to the player's inventory
 *
 * Parameters:
 *  object: the object too add
 * 	plyr: the plyaer
 *
 * Returns:
 *  int, 1 for success, 0 for failure
 */
int add_inventory_object(object_t* item, player_t* plyr);

/*
 * Returns the inventory list
 *
 * Parameters:
 * 	plyr: the player
 *
 * Returns:
 *  linked list, the inventory
 */
llist* get_inventory(player_t* plyr);

/*
 * Returns the inventory list
 *
 * Parameters:
 * 	plyr: the player
 *
 * Returns:
 *  linked list, the clothes
 */
llist* get_clothes(player_t* plyr);


#endif