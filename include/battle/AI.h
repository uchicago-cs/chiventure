#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

#ifndef AI_H
#define AI_H

/* Given a difficulty level and the player the move is going to be used 
 *      against, give_move returns a move
 * Inputs:
 *      difficulty - the difficulty level of the game
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* give_move(int difficulty, player_t player);

/* Given the player the move is going to be used against, 
 *          easy_move returns the move that will deal the lighest damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* easy_move(player_t* player);

/* Given the player the move is going to be used against, 
 *          medium_move has a 50% chance of returning a 
 *          hard move and  50% chance of returning an easy move
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* medium_move(player_t* player);

/* Given the player the move is going to be used against, 
 *          hard_move returns the move that will deal the most damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* hard_move(player_t* player);

#endif