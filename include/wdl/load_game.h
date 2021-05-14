/*
 * Header file for loading game Object into game struct
 */

#ifndef INCLUDE_LOAD_GAME_H
#define INCLUDE_LOAD_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "wdl/wdl_ctx.h"

 /*
 * load_wdl, loads a wdl specified internally into all game-state structs
 *
 * input: path to wdl file
 * 
 * output: a pointer to a wdl_ctx struct
 * that has a game filled with the contents of the yaml file OR
 * a hash table of wdl objects
 */
wdl_ctx_t *load_wdl(char *path_to_wd);

/*
 * load_game, when passed libobj objects, will load into a game
 *
 * Parameters:
 *   - big_document: an obj_t of libobj objects
 *
 * Returns:
 *   - a pointer to a game object on success
 8   - NULL if error
 *
 */
game_t *load_game(obj_t *big_document);

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
