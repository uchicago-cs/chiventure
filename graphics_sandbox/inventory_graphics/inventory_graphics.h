#ifndef INVENTORY_GRAPHICS_H
#define INVENTORY_GRAPHICS_H


/*
 * This module defines an inventory struct and the necessary 
 * functions for manipulating an inventory pop-up window
 */


#include "item.h"
#include "player.h"
#include "read_gdl.h"
#include <stdlib.h>


/* Defines the status for a slot */
typedef enum status {EMPTY, FULL} status;


/* Define a slot containing an item and a tag / status */
typedef struct slot {
    status status;
    item_t *item;
} slot_t;

/*
 * Populates the 2D array that will be used to hold items for inventory 
 * grpahics
 *
 * Parameters:
 * p: pointer to heap allocated player struct
 * graphics : pointer to heap allocated graphics struct
 *
 * Returns:
 * 2D array of items corresponding to items in player's inventory
 */
slot_t **populate_items(player_t *p, graphics_t *graphics);


/*
 * Defines the player inventory based on the display
 * preferences of the game developer and a 2D array
 * of items
 *
 * Note:
 * A matrix was chosen to implement inventory items over
 * an adjancency list and hash table. Adjacency lists,
 * while sparse, require traversal and are thus slow
 * to search. Hash tables require a bit more complexity
 * than 2D arrays and require a seperate hash struct.
 * 2D arrays, given that the item struct has been edited
 * to contain a row and column field are quickly accessible
 * due to indexing. Moreover, we do not anticipate much wasted
 * space because game inventories tend to be small anyways.
 */ 
typedef struct player_inventory {
    inventory_display_t *display;
    slot_t **slots;
} player_inventory_t;


/* Allocates and initializes a player's inventory
 *
 * Parameters:
 * - The graphics information as specified by the author in the GDL
 * - A pointer to a heap allocated player struct
 * Returns:
 * - A player inventory struct
 */
player_inventory_t *new_player_inventory(graphics_t *graphics, player_t *p);


/* Frees an inventory struct
 *
 * Parameters:
 * - The player's inventory struct
 *
 * Returns:
 * - Always returns 0
 */
int free_player_inventory(player_inventory_t *player_inventory);


/* Updates the player's inventory once a game changing event occurs
 *
 * Parameters:
 * - the player's current inventory
 * - the item to be added
 *
 * Returns:
 * - void (the changes occur as a side-effect)
 */
void add_item_inventory(player_inventory_t *player_inventory, item_t *item);


/*
 * Removes an item from a player's inventory
 *
 * Parameters:
 * - the player's inventory
 * - the item to be removed
 *
 * Returns:
 * - void (this all occurs as a side effect)
 */
void remove_item_inventory(player_inventory_t *player_inventory, item_t *item);
 

/* Draws the inventory window on screen
 *
 * Parameters:
 * - The player's inventory
 *
 * Returns:
 * - void
 */
void draw_player_inventory(player_inventory_t *player_inventory);


#endif
