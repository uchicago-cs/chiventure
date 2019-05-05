/*
 * Lindsey Hsi, Patrick Koopmans, Jessica Xia
 * A player structure
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include <stdbool.h>


/* A player in game */
typedef struct player{
    int level;
    int health;
    int xp;
    llist* inventory;
    llist* clothes;
    //objectives? 
} player_t;

/*
 * Initializes a player
 *
 * Parameters:
 *  - p: A player. Must point to already allocated memory.
 *  - health: The starting health of the player
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs.
 */
int player_init(player_t* plyr, int health);

/*
 * Allocates a new player
 *
 * Parameters:
 *  - health: The starting health of the player
 *
 * Returns:
 *  - Pointer to allocated player
 */
player_t* player_new(int health);

/*
 * Frees resources associated with a player
 *
 * Parameters:
 *  - plyr: the player to be freed
 *
 * Returns:
 *  - always returns 0
 */
int player_free(player_t* plyr);

int get_health();

int change_health();

int get_level();

int change_level();

int get_xp();

int change_xp();

int add_clothes_item(object_t* item);

int add_inventory_item(object_t* item);

object_t* remove_inventory_item();

object_t* remove_clothes_item();

object_t* see_inventory_item();

object_t* see_clothes_item();



