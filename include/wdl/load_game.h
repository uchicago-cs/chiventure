/*
 * Header file for loading game Object into game struct
 */

#ifndef INCLUDE_LOAD_GAME_H
#define INCLUDE_LOAD_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wdl_common.h"
#include "wdl/load_quests.h"

/*
 * load_game, when passed libobj objects, will load into a game
 *
 * Parameters:
 *   - obj_store: an obj_t of libobj objects
 *
 * Returns:
 *   - a pointer to a game object on success
 8   - NULL if error
 *
 */
game_t *load_game(obj_t *obj_store);

/*
 * Function to create a pointer to an empty game
 *
 * input: 
 *   - document object that contains whole game
 *
 * output:
 *   - a pointer to a game_t struct
 *
 */
game_t *create_game(obj_t *doc);


/*
 * Function set start room in a game
 *
 * input: 
 *   - room id, pointer to game_t struct
 *
 * output:
 *   - none
 *
 */
void game_set_start(char *room_id, game_t *game);

/*
 * Helper function for debugging that prints main objects in the game
 * 
 * input:
 *  - game, pointer to game_t struct
 * 
 * output: 
 *  - none
 */ 
void debug_print(game_t *game);




#endif /* INCLUDE_LOAD_GAME_H */
