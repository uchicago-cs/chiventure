/*
 * Header file for loading game Object into game struct
 */

#ifndef INCLUDE_LOAD_GAME_H
#define INCLUDE_LOAD_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "room.h"

#define FILE_PATH "../examples/sample_yaml/connected_rooms.yaml"

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




#endif /* INCLUDE_LOAD_GAME_H */
