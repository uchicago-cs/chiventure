#ifndef BATTLE_FLOW_H
#define BATTLE_FLOW_H

#include <stdbool.h>
#include <string.h>
#include "battle_flow_structs.h"
#include "battle_state.h"
#include "battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"

/*
 * Starts the battle, sets up structs, then runs a battle loop until finished
 * For now, since we will be starting out with an implementation fo the set-up
 * of a new battlee, this function will essentially act as a battle set-up.
 * Later, the battle loop and other aspects of running the game
 * at the high-level will be added.
 *
 * Parameters:
 *  - ctx = the current chiventure context
 *  - npc_enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *  - env = environment for the battle
 *
 * Returns:
 *  - SUCCESS if successful, FAILURE otherwise
 */
 int start_battle(chiventure_ctx_battle_t *ctx, npc_enemy_t *npc_enemies,
                  environment_t env);

/*
 * Sets up the player's combatant_t struct for a new battle
 *
 * Parameters:
 *  - ctx_player = the current player in the game_t struct, which is in
 *                 the chiventure context struct
 *
 * Returns:
 *  - pointer to player's combatant_t struct initialized for new battle
 */
combatant_t *set_player(player_t *ctx_player);

/*
 * Sets up all enemy combatant structs for a new battle
 *
 * Parameters:
 *  - npc_enemies = pointer to list of enemy/ies (stub for enemy NPCs)
 *
 * Returns:
 *  - pointer to list of enemy's/enemies' combatant_t structs initialized for
 *  a new battle
 */
combatant_t *set_enemies(npc_enemy_t *npc_enemies);

/*
 * Sets up battle struct for a new battle
 *
 * Parameters:
 *  - ctx_player = pointer to player_t player in game_t struct
 *  - npc_enemies = pointer to list of enemy/ies (NPC enemy stub)
 *  - env = the environment for the battle
 *
 * Returns:
 *  - A pointer to new battle struct initialized for a new battle
 *
 */
battle_t *set_battle(player_t *ctx_player, npc_enemy_t *npc_enemies,
                      environment_t env);


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
int print_start_battle(battle_t *b, char *string, char **ret_string);

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
 int print_battle_move(battle_t *b, turn_t turn, move_t *move, char *string, char **ret_string);

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
 int print_battle_winner(battle_status_t status, int xp, char *string, char **ret_string);

#endif
