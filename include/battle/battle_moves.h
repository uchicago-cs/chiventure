#ifndef BATTLE_MOVES_H
#define BATTLE_MOVES_H

#include <stdbool.h>
#include <string.h>
#include "playerclass/class_structs.h"
#include "battle/battle_common.h"
#include "battle_structs.h"

/* defines max length of class info */
#define MAX_MOVE_INFO_LEN (100)


/* Creates a new move struct 
 * Parameters:
 * - id: move id number 
 * - name: the name of the move
 * - info: a string with a short description of move 
 * - dmg_type: the type of damage the move will do
 * - stat_mods: the targets the stat modifications of the move will be used on
 * - effects: the targets the effects of the move will be used on
 * - count: whether the move is a single target or multi target move
 * - sp_cost: the amount of sp required to use the move
 * - req_items a pointer to the battle_item struct involved with the move 
 * - damage: amount of damage the move does 
 * - accuracy: the accuracy of the move
 * - user_mods: how the user's stats get modified by the move
 * - opponent_mods: how the opponent's stats get modified by the move
 * - prev: a pointer to the preveious move
 * - next: a pointer to the next move
 * returns: a pointer to the new move 
 */
move_t* move_new(int id, char* name, char* info, damage_type_t dmg_type,
                 target_type_t stat_mods, target_type_t effects, target_count_t count, 
                 int sp_cost, battle_item_t* req_item, int damage, int accuracy,
                 stat_changes_t* user_mods, stat_changes_t* opponent_mods, move_t* prev,
                 move_t* next);


 /* Initialize a move struct 
  * Parameters:
  * - id: move id number 
  * - name: the name of the move
  * - info: a string with a short description of move 
  * - dmg_type: the type of damage the move will do
  * - stat_mods: the targets the stat modifications of the move will be used on
  * - effects: the targets the effects of the move will be used on
  * - count: whether the move is a single target or multi target move
  * - sp_cost: the amount of sp required to use the move
  * - req_items a pointer to the battle_item struct involved with the move 
  * - damage: amount of damage the move does 
  * - accuracy: the accuracy of the move
  * - user_mods: how the user's stats get modified by the move
  * - opponent_mods: how the opponent's stats get modified by the move
  * - prev: a pointer to the preveious move
  * - next: a pointer to the next move 
  * returns:
  * - SUCCESS for successful init
  * - FAILURE for unsuccessful init
  */
int move_init(move_t* move, int id, char* name, char* info, damage_type_t dmg_type,
                 target_type_t stat_mods, target_type_t effects, target_count_t count, 
                 int sp_cost, battle_item_t* req_item, int damage, int accuracy,
                 stat_changes_t* user_mods, stat_changes_t* opponent_mods, move_t* prev,
                 move_t* next);


/* Frees a battle struct from memory 
 * Parameters:
 * - move: a move struct allocated with move_new();
 * Returns: 
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int move_free(move_t *move);

/* For use in testing battle code,
make a test move for each class */

move_t *test_move_bard();

move_t *test_move_cleric();

move_t *test_move_paladin();

move_t *test_move_wizard();


#endif
