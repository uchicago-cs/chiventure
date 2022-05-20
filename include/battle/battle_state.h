#ifndef BATTLE_STATE_H
#define BATTLE_STATE_H

#include "battle/battle_ai.h"
#include "battle/battle_common.h"
#include "battle/battle_moves.h"
#include "battle/battle_structs.h"
#include "common/utlist.h"
#include "common/common.h"
#include <stdbool.h>
#include <string.h>

/* Creates a new battle  struct
 * Parameters:
 * - player: a pointer to player combatant
 * - enemy: a pointer to enemy combatant/s
 * - env: an environment enum
 * - turn: a turn_t enum indicating the current turn
 * returns: a pointer to the new battle
 */
battle_t *battle_new(combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn);

/* Initialize a battle  struct
 * Parameters:
 * - b: a pointer to a battle struct in memory
 * - player: a pointer to player combatant
 * - enemy: a pointer to enemy combatant/s
 * - env: an environment enum
 * - turn: a turn_t enum indicating the current turn
 * returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int battle_init(battle_t *b, combatant_t *player, combatant_t *enemy,
    environment_t env, turn_t turn);

/* Frees a battle struct from memory */
int battle_free(battle_t *b);

/* Initialize a combatant struct
 * Parameters:
 * - name: name string
 * - is_friendly: bool indicating character type
 * - c_type: pointer to the player class struct 
 * - stats: pointer to the stats of the combatant(stub)
 * - moves: pointer to the linked list of moves for the combatant (stub)
 * - items: pointer to the linked list of battle_items for the combatant (stub)
 * - weapon: a pointer to the weapon equiped to the combatant
 * - accessory: a pointer to the accessory equiped to the combatant
 * - armor: a pointer to the weapon equiped to the combatant
 * - ai: combatant's ai move strategy
 * returns: a pointer to the new character
 */
combatant_t *combatant_new(char *name, bool is_friendly, class_t *c_type,
            stat_t *stats, move_t *moves, battle_item_t *items, battle_equipment_t *weapon, 
            battle_equipment_t *accessory, battle_equipment_t *armor, difficulty_t ai);

/* Creates a new combatant struct
 * Parameters:
 * - c: a pointer to combatant in memory
 * - name: name string
 * - is_friendly: bool indicating character type
 * - c_type: pointer to the player class struct 
 * - stats: a pointer to the stats of the combatant (stub)
 * - moves: a pointer to the linked list of moves for the combatant (stub)
 * - items: a pointer to the linked list of battle_items for the combatant (stub)
 * - weapon: a pointer to the weapon equiped to the combatant
 * - accessory: a pointer to the accessory equiped to the combatant
 * - armor: a pointer to the weapon equiped to the combatant
 * - ai: combatant's ai move strategy
 * returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int combatant_init(combatant_t *c, char *name, bool is_friendly, class_t *c_type,
     stat_t *stats, move_t *moves, battle_item_t *items, battle_equipment_t *weapon, 
     battle_equipment_t *accessory, battle_equipment_t *armor, difficulty_t ai);

/* Frees a combatant struct from memory
 * Parameters:
 * - c: a pointer to combatant in memory
 * returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int combatant_free(combatant_t *c);

/* Frees a list of combatant structs from memory
 * Parameters:
 * - c: a pointer to combatant in memory
 * returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int combatant_free_all(combatant_t *c);

/* Initialize an empty stat_changes struct
 * Parameters:
 * - none
 * returns: a pointer to the new stat_changes_t node
 */
stat_changes_t *stat_changes_new();

/* Creates a new stat_changes struct
 * Parameters:
 * - sc: a pointer to an empty stat_changes node in memory
 * returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int stat_changes_init(stat_changes_t *sc);

/* Frees a stat_changes struct from memory. Note: Does NOT do anything
 *     more than freeing the given stat_changes node
 * Parameters:
 * - sc: a pointer to a stat_changes struct in memory
 * returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */
int stat_changes_free_node(stat_changes_t *sc);

/* Frees a list of stat_changes structs from memory. Note: only frees
 *     from the given stat_changes node ONWARDS.
 * Parameters:
 * - sc: a pointer to a stat_changes struct in memory
 * returns:
 * - SUCCESS for successful free
 * - FAILURE for unsuccessful free
 */

int stat_changes_free_all(stat_changes_t *sc);

/* Creates an empty stat_changes node at the end of a given
 *     stat_changes_t struct
 * Parameters:
 * - sc: a pointer to a stat_changes struct in memory
 * returns:
 * - SUCCESS for successful adding
 * - FAILURE for unsuccessful adding
 */
int stat_changes_add_node(stat_changes_t *sc);

/* Removes a given stat_changes node from the list it's in
 *     Note: Do not remove the header node of a stat_changes list
 * Parameters:
 * - sc: a pointer to a stat_changes struct in memory
 * returns:
 * - SUCCESS for successful removal
 * - FAILURE for unsuccessful removal
 */
int stat_changes_remove_node(stat_changes_t *sc);

/* Decrements all turn counts in the stat_changes struct by 1. If
 *     this becomes 0 for a given stat_changes node, remove it from
 *     list.
 * Parameters:
 * - sc: a pointer to a stat_changes struct in memory
 * - c: a pointer to a stat_changes_struct in memory in case of stat changes
 *     that need to be made/undone
 * returns:
 * - SUCCESS for successful decrement
 * - FAILURE for unsuccessful decrement
 */
int stat_changes_turn_increment(stat_changes_t *sc, combatant_t *c);

/* Undoes the temporary stat changes
 * Parameters:
 * - sc: a pointer to a stat_changes struct in memory
 * - c: a pointer to a combatan struct in memory to undo stat changes to
 * returns:
 * - SUCCESS for successful completion
 * - FAILURE for unsuccessful completion
 */
int stat_changes_undo(stat_changes_t *sc, combatant_t *c);

/* Appends a node to the end of a stat_changes struct
 * Parameters:
 * - base: a pointer to a stat_changes struct in memory to be appended to
 * - sc: a pointer to a stat_changes struct in memory to append
 * returns:
 * - SUCCESS for successful completion
 * - FAILURE for unsuccessful completion
 */
int stat_changes_append_node(stat_changes_t *base, stat_changes_t *sc);
#endif
