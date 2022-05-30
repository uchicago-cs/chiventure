#ifndef LOAD_H
#define LOAD_H
#include "game-state/game.h"

/*
 * Unpacks the protofile and reloads all saved information into game structs
 *
 * Parameters:
 * - filename: pointer to string name of file with sereialized information
 * - g_t: pointer game struct
 * 
 * Returns:
 * - 0 (SUCCESS) if successful
 * - 1 (FAILURE) if unsuccessful
 */
int load(char *filename, game_t *g_t);


#endif
