#ifndef BATTLE_MOVE_MAKER_H
#define BATTLE_MOVE_MAKER_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "../../playerclass/examples/class-list.h"
#include "battle/battle_structs.h"
#include "battle/battle_flow_structs.h"
#include "battle/battle_moves.h"

 /* Packages class-specific move from player class's linked list 
 into battle move struct, adds this move to the input player's move list 
 * Parameters:
 * - player: a pointer to the player we want to get class-specific moves for 
 * Returns:
 * - player: the input player with correct move added to move list 
 */
player_t *build_moves(player_t *player);


#endif
