#ifndef BATTLE_PRINT_H
#define BATTLE_PRINT_H

#include <stdbool.h>
#include <string.h>
#include "battle_flow_structs.h"
#include "battle_logic.h"
#include "battle_state.h"
#include "battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"

/*
 * Stores the message to be printed at the start of the battle in the return
 * string, mirroring the preparation of the return string in action-management
 *
 * Parameters:
 *  - b = pointer to the battle
 *  - string = malloced string used in actionmanagement.c for sprintf
 *  - ret_string = the return string that will store the message
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 *
 */
int print_start_battle(battle_t *b, char *string);

/*
 * Stores the message to be printed at the end of a move in the return
 * string, mirroring the preparation of the return string in action-management
 * The message varies based off whether it is the player or enemy move.
 *
 * Parameters:
 *  - b = pointer to the battle
 *  - turn = whose turn it is for this move
 *  - move = pointer to the move being used
 *  - string = malloced string used in actionmanagement.c for sprintf
 *  - ret_string = the return string that will store the message
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 *
 */
 int print_battle_move(battle_t *b, turn_t turn, move_t *move, char *string);

/*
 * Stores the message to be printed at the end of the battle in the return
 * string, mirroring the preparation of the return string in action-management.
 * Message varies based off whether the player or enemy won
 *
 * Parameters:
 *  - status = status of the finished battle. Only pass BATTLE_VICTOR_PLAYER or
 *             BATTLE_VICTOR_ENEMY
 *  - xp = amount of xp to be awarded to the player if they win
 *  - string = malloced string used in actionmanagement.c for sprintf
 *  - ret_string = the return string that will store the message
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 *
 */
 int print_battle_winner(battle_status_t status, int xp, char *string);
 #endif
