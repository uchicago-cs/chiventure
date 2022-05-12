/*
 * This module defines an inventory struct and the
 * necessary functions for manipulating this window
 */

#include "item.h"
#include "read_gdl.h"

/* The set of background colors availible for the inventory */
typedef enum color {
    WHITE,
    GRAY,
    BLACK,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    PURPLE,
    PINK,
} color;


// define a hash table?

/* Defines the custom inventory represenation specified by the game developer */
typedef struct inventory_display {
    unsigned int rows;
    unsigned int columns;
    color color;
} inventory_display_t;

/*
 * Defines the player inventory
 */ 
typedef struct player_inventory {
    inventory_display_t display;
// hash?    item **items;
} player_inventory_t;

// read graphics struct -- init invenetory display
// take gdl -> graphics info necessary for display struct

// init inventory - game struct + initalized display


// free inventory (player)

// free display

// draw inventory (player_inv) -> window

// update ...
