#ifndef SAVE_H
#define SAVE_H
#include "game-state/game.h"

/* 
 * Calls all above functions to save game into file
 * 
 * Parameters:
 *   - g: pointer to game_t struct containing the game we want to save
 *   - filename: pointer to string name of the save file
 *
 * Return:
 *   - 0 (SUCCESS) if successful
 *   - 1 (FAILURE) if unsuccessful 
 */
int save(game_t *g_t, char *filename);


#endif
