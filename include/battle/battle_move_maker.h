#ifndef BATTLE_MOVE_MAKER_H
#define BATTLE_MOVE_MAKER_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "../../src/playerclass/examples/class-list.h"
#include "battle_structs.h"
#include "battle_flow_structs.h"
#include "battle_moves.h"

 /* Packages class-specific move from player class's linked list 
 into battle move struct, adds this move to the input player's move list 
 * Parameters:
 * - player: a pointer to the player we want to get class-specific moves for 
 * Returns:
 * - player: the input player with correct move added to move list 
 */
player_t *add_class_move(player_t *player);


#endif
