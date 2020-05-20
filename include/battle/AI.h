#ifndef BATTLE_AI_H
#define BATTLE_AI_H

#include <stdlib.h>
#include <stdio.h>
#include "common/utlist.h"
#include "battle_structs.h"


/* Given a difficulty level and the player the move is going to be used 
 *      against, give_move returns a move
 * Inputs:
 *      difficulty - the difficulty level of the game
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* give_move(int difficulty, player_t* player, enemy_t* enemy);

/* Given the player the move is going to be used against, 
 *          easy_move returns the move that will deal the lighest damage
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* easy_move(player_t* player, enemy_t* enemy);

/* Given the player the move is going to be used against, 
 *          medium_move returns a random move
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* easy_move(player_t* player, enemy_t* enemy);

/* Given the player the move is going to be used against, 
 *          hard_move returns the move that will deal the most damage
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* easy_move(player_t* player, enemy_t* enemy);

/* Function returns the damage dealt to a player
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 *      move - the move being played
 * Outputs:
 *      damage - the damage dealt     */
double damage(player_t* player, move_t* move, enemy_t* enemy);

#endif