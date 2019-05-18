/*
 * Header file for loading game Object into game struct
 */

#ifndef INCLUDE_LOAD_GAME_H
#define INCLUDE_LOAD_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"

/*
 * Function to load a complete game into game_t struct
 *
 * input: 
 *   - an attr_list_t pointer to a list of rooms
 *   - another attr_list_t pointer to a list of all items in the game
 *   - a pointer to the game_t struct that will be filled.
 *
 * output:
 *
 */
void load_rooms(atrr_list_t *rooms, attr_list_t *all_items, game_t *g);



#endif /* INCLUDE_LOAD_GAME_H */
