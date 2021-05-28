#ifndef BATTLE_PRINT_H
#define BATTLE_PRINT_H

#include <stdbool.h>
#include <string.h>
#include "battle_ai.h"
#include "battle_flow_structs.h"
#include "battle_logic.h"
#include "battle_state.h"
#include "battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"

#define BATTLE_BUFFER_SIZE (2000) // copied from actionmanagement.c, changed to 200

/*
 * Stores the message to be printed at the start of the battle in the return
 * string
 *
 * Parameters:
 *  - b = pointer to the battle
 *
 * Returns:
 *  - malloced string with the message about the start of the battle
 *
 */
char *print_start_battle(battle_t *b);

/*
 * Stores the message to be printed at the end of a move in the return
 * string. The message varies based off whether it is the battle_player or enemy move.
 *
 * Parameters:
 *  - b = pointer to the battle
 *  - turn = whose turn it is for this move
 *  - move = pointer to the move being used
 *
 * Returns:
 *  - malloced string with the message about the recent move
 *
 */
 char *print_battle_move(battle_t *b, turn_t turn, move_t *move);

 /*
  * Stores a message about a list of the enemy HP to a previously allocated string.
  * Appends this message to the end of any message that might already be in
  * that string.
  *
  * Parameters:
  *  - b = pointer to the battle
  *  - string = the string to which the hp will be printed to
  *
  * Returns:
  *  - SUCCESS if successfully stored message about HP, FAILURE otherwise
  *
  */
 int print_hp(battle_t* b, char* string);

/*
 * Stores the message to be printed at the end of the battle in the return
 * string. Message varies based off whether the battle_player or enemy won
 *
 * Parameters:
 *  - status = status of the finished battle. Only pass BATTLE_VICTOR_PLAYER or
 *             BATTLE_VICTOR_ENEMY
 *  - xp = amount of xp to be awarded to the battle_player if they win
 *
 * Returns:
 *  - malloced string with the message about the end of the battle
 *
 */
char *print_battle_winner(battle_status_t status, int xp);

/*
 * Stores the message to be printed at the start of the turn in the return
 * string. Message prompts player to either use a move or item
 *
 * Parameters:
 *  - b = pointer to the battle
 *
 * Returns:
 *  - malloced string with the message about the turn
 *
 */
char *print_start_turn(battle_t* b);

/* Returns a string for the avaliable battle_items for the player
 * Parameter:
 *  - b = pointer to the battle
 * Returns:
 *  A string containing the available items
 */ 
char *print_battle_items(battle_t *b, char* items);

/* Returns a string for the avaliable moves for the player
 * Parameter:
 *  - b = pointer to the battle
 * Returns:
 *  A string containing the available moves
 */ 
char *print_moves(battle_t *b, char* moves);
 #endif
