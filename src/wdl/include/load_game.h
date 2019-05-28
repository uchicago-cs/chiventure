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
 * Function to create a pointer to an empty game
 *
 * input: 
 *   - document object that contains whole game
 *
 * output:
 *   - a pointer to a game_t struct
 *
 */
game_t *create_game(obj_t *game);



#endif /* INCLUDE_LOAD_GAME_H */
