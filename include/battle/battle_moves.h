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
 * - info: a string with a short description of move 
 * - id: move id number 
 * - items: a pointer to the battle_item struct involved with the move 
 * - attack: true if move is attack-based (vs defense), else false 
 * - damage: amount of damage the move does 
 * - defense: amount of defense the move provides 
 * returns: a pointer to the new move 
 */
move_t *move_new(int id, char* name, char* info, damage_type_t dmg_type, target_type_t stat_mods,
        target_type_t effects, target_count_t count, int sp_cost, battle_item_t *req_item,
        int damage, int accuracy, stat_changes_t *user_mods, stat_changes_t *opponent_mods);


 /* Initialize a move struct 
  * Parameters:
  * - move: a pointer to a move struct in memory
  * - info: a string with a short description of move 
  * - id: move id number 
  * - items: a pointer to the battle_item struct involved with the move 
  * - attack: true if move is attack-based (vs defense), else false 
  * - damage: amount of damage the move does 
  * - defense: amount of defense the move provides 
  * returns:
  * - SUCCESS for successful init
  * - FAILURE for unsuccessful init
  */
int move_init(move_t *move, int id, char* name, char* info, damage_type_t dmg_type,
        target_type_t stat_mods, target_type_t effects, battle_item_t *req_item,
        target_count_t count, int sp_cost, int accuracy, int damage,
        stat_changes_t* user_mods, stat_changes_t* opponent_mods);


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
