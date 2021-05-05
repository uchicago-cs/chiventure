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
 * - class: pointer to the player class struct 
 * - stats: pointer to the stats of the combatant(stub)
 * - moves: pointer to the linked list of moves for the combatant (stub)
 * - items: pointer to the linked list of items for the combatant (stub)
 * - ai: combatant's ai move strategy
 * returns: a pointer to the new character
 */
combatant_t *combatant_new(char *name, bool is_friendly, class_t *class,
             stat_t *stats, move_t *moves, battle_item_t *items, difficulty_t ai);

/* Creates a new combatant struct
 * Parameters:
 * - c: a pointer to combatant in memory
 * - name: name string
 * - is_friendly: bool indicating character type
 * - class: pointer to the player class struct 
 * - stats: a pointer to the stats of the combatant (stub)
 * - moves: a pointer to the linked list of moves for the combatant (stub)
 * - items: a pointer to the linked list of items for the combatant (stub)
 * - ai: combatant's ai move strategy
 * returns:
 * - SUCCESS for successful init
 * - FAILURE for unsuccessful init
 */
int combatant_init(combatant_t *c, char *name, bool is_friendly, class_t *class,
     stat_t *stats, move_t *moves, battle_item_t *items, difficulty_t ai);

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
#endif
