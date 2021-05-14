#ifndef BATTLE_MOVE_MAKER_H
#define BATTLE_MOVE_MAKER_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "../src/playerclass/examples/class-list.h"
#include "battle_structs.h"
#include "battle_flow_structs.h"
#include "battle_moves.h"
#include "battle_structs.h"

/* Packages class-specific move from player class's linked list 
   into battle move struct, adds this move to the input combatant's move list 
 * Parameters:
 * - c: a pointer to the combatant we want to get class-specific moves for 
 * Returns:
 * - SUCCESS or FAILURE 
 */
int build_moves(combatant_t *c);

/*
 * Adds a move to the combatants list of moves 
 *
 * Parameters:
 *  - combatant: pointer to a combatant_t 
 *  - move: pointer to the move to be added to the comabatant's list of moves
 *
 * Returns:
 *  - Success or failure and modifies the status
 *
 */
int add_move(combatant_t *combatant, move_t *move);

#endif
