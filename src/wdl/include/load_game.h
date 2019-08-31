/*
 * Header file for loading game Object into game struct
 */

#ifndef INCLUDE_LOAD_GAME_H
#define INCLUDE_LOAD_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "wdl_common.h"

 /*
 * load_wdl, loads a wdl specified internally into all game-state structs
 *
 * input: nothing
 * 
 * output: a pointer to an game_t struct
 * that has been filled with the contents of the yaml file
 */
game_t *load_wdl(char *path_to_file);

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

void print_out_game(game_t *game);




#endif /* INCLUDE_LOAD_GAME_H */
