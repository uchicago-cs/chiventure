#ifndef _NPC_BATTLE_H
#define _NPC_BATTLE_H

#include "battle/battle_common.h"
#include "battle/battle_structs.h"
#include "battle/battle_moves.h"

// NPC_BATTLE STRUCTURE DEFINITION --------------------------------------------

/* Hostility level options */
typedef enum hostility {
    FRIENDLY = 0,
    CONDITIONAL_FRIENDLY = 1,
    HOSTILE = 2
} hostility_t;

/* Info used for battles with NPCs */
typedef struct npc_battle {
    /* pointer to an existing stat struct */
    stat_t *stats;

    /* pointer to an existing move struct */
    move_t *moves;

    /* difficulty of the NPC's ai */
    difficulty_t ai;
    
    /* hostility level of the npc */
    hostility_t hostility_level;

    /* class of the npc */
    class_t *class_type;

    /* An inventory of items that can be used in battle */
    battle_item_t *items;

    /* armor that an npc can equip*/ 
    battle_equipment_t *armor;

    /* an accessory that an npc can equip*/ 
    battle_equipment_t *accessory;

    /* weapon that an npc can equip*/ 
    battle_equipment_t *weapon;
} npc_battle_t;

// STRUCT FUNCTIONS -----------------------------------------------------------

/*
 * Initializes an npc's battle info (npc_battle) with the given parameters.
 *
 * Parameters:
 *  npc_battle: an npc_battle struct; must point to already allocated memory
 *  stats: a pointer to an existing stat_t struct defining the npc's battle 
           stats (see /include/battle/battle_structs.h)
 *  moves: a pointer to an existing move_t struct defining the npc's battle 
           moves (see /include/battle/battle_structs.h)
 *  ai: the npc's difficulty level (see /include/battle/battle_common.h)
 *  hostility_level: the npc's hostility level 
 *  class_type: the class struct of the npc
 *  items: a doubly linked list of items that the npc can use during battle
 * - weapon: the weapon equiped to the npc during battle
 * - accessory: the accessory equiped to the npc during battle
 * - armor: the armor equiped to the npc during battle
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs
 */
int npc_battle_init(npc_battle_t *npc_battle, stat_t* stats,
                    move_t* moves, difficulty_t ai, hostility_t hostility_level,
                    class_t *class_type, battle_item_t *items,
                    battle_equipment_t *armor, battle_equipment_t *accessory, 
                    battle_equipment_t *weapon);

/*
 * Allocates a new npc_battle struct in the heap.
 *
 * Parameters:
 *  stats: a pointer to an existing stat_t struct defining the npc's battle 
           stats (see /include/battle/battle_structs.h)
 *  moves: a pointer to an existing move_t struct defining the npc's battle 
           moves (see /include/battle/battle_structs.h)
 *  ai: the npc's difficulty level (see /include/battle/battle_common.h)
 *  hostility_level: the npc's hostility level 
 *  class_type: the class struct of the npc
 *  items: a doubly linked list of items that the npc can use during battle
 * - weapon: the weapon equiped to the npc during battle
 * - accessory: the accessory equiped to the npc during battle
 * - armor: the armor equiped to the npc during battle
 *
 * Returns:
 *  pointer to allocated npc_battle
 */
npc_battle_t *npc_battle_new(stat_t* stats, move_t* moves, 
		                     difficulty_t ai, hostility_t hostility_level, 
			                 class_t *class_type, battle_item_t *items,
                             battle_equipment_t *armor, battle_equipment_t *accessory, 
                             battle_equipment_t *weapon);

/*
 * Frees resources associated with an npc_battle struct.
 *
 * Parameters:
 *  npc_battle: the npc_battle struct to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs
 */
int npc_battle_free(npc_battle_t *npc_battle);

#endif
