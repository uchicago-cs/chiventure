#ifndef BATTLE_AI_H
#define BATTLE_AI_H

#include <stdlib.h>
#include <stdio.h>
#include "battle/battle_common.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_state.h"
#include "battle/battle_structs.h"
#include "battle/battle_moves.h"
#include "common/utlist.h"
#include "battle/battle_default_objects.h"
/* Given a difficulty level, the player the move is going to be used 
 *      against, and the enemy, give_move returns a move
 * Inputs:
 *      difficulty - the difficulty level of the game
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* give_move(combatant_t* player, combatant_t* enemy, difficulty_t difficulty);


/* Given the player the move is going to be used against and the enemy,
 *          find_random returns a random move
 * Inputs:
 *      player - the player the move is going to be used against
 *      enemy - the enemy using the move
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_random(combatant_t* player, combatant_t* enemy);

/* Given a moves list, function will find the 
 *      move dealing the most damage
 * Inputs:
 *      player - the player the move is going to be used against
 * Outputs:
 *      move_t - the move to be used        */
move_t* find_greedy(combatant_t* player, combatant_t* enemy);

/* Function returns the damage dealt to a target
 * Inputs:
 *      target - the target the damage is going to be dealt to
 *      source - the source combatant using the move
 *      move - the move being played
 * Outputs:
 *      damage - the damage dealt     */
int damage(combatant_t* target, move_t* move, combatant_t* source);

#endif
