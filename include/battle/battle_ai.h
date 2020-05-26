#ifndef BATTLE_AI_H
#define BATTLE_AI_H

#include <stdlib.h>
#include <stdio.h>
#include "common/utlist.h"
#include "battle_state.h"
#include "battle_structs.h"
#include "battle_moves.h"
#include "battle_classes.h"


/* Given a difficulty level, the player the move is going to be used 
 *      against, and the enemy, give_move returns a move
 * Inputs:
 *      difficulty - the difficulty level of the game
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* give_move(int difficulty, combatant_t* player, combatant_t* enemy);

/* Given the player the move is going to be used against and the enemy,
 *          easy_move returns the move that will deal the lighest damage
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* easy_move(combatant_t* player, combatant_t* enemy);

/* Given the player the move is going to be used against, 
 *          medium_move returns a random move
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* medium_move(combatant_t* player, combatant_t* enemy);

/* Given the player the move is going to be used against, 
 *          hard_move returns the move that will deal the most damage
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* hard_move(combatant_t* player, combatant_t* enemy);

/* Given a moves list, function will find the 
 *      move dealing the least damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_easy(combatant_t* player, combatant_t* enemy);

/* Given a moves list, function will find the 
 *      move dealing the most damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_hard(combatant_t* player, combatant_t* enemy);

/* Function returns the damage dealt to a player
 * Inputs:
 *      player - the player the damage is going to be dealt to
 *      enemy - the enemy using the move
 *      move - the move being played
 * Outputs:
 *      damage - the damage dealt     */
double damage(combatant_t* player, move_t* move, combatant_t* enemy);

#endif