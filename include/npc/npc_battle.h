#ifndef _NPC_BATTLE_H
#define _NPC_BATTLE_H

#include "battle/battle_common.h"
#include "battle/battle_structs.h"
#include "battle/battle_moves.h"
#include "npc/npc.h"

/* Forward declaration. Full typedef can be found in npc.h */
typedef struct npc npc_t;

// NPC_BATTLE STRUCTURE DEFINITION --------------------------------------------

/* Hostility level options */
typedef enum hostility {
    FRIENDLY = 0,
    CONDITIONAL_FRIENDLY = 1,
    HOSTILE = 2
} hostility_t;

/* Info used for battles with NPCs */
typedef struct npc_battle {
    /* NPC health level */
    int health;

    /* pointer to an existing stat struct */
    stat_t *stats;

    /* pointer to an existing move struct */
    move_t *moves;

    /* difficulty of the NPC's ai */
    difficulty_t ai;
    
    /* hostility level of the npc */
    hostility_t hostility_level;

    /* health level at which the NPC will surrender */
    int surrender_level;
} npc_battle_t;

// STRUCT FUNCTIONS -----------------------------------------------------------

/*
 * Initializes an npc's battle info (npc_battle) with the given parameters.
 *
 * Parameters:
 *  npc_battle: an npc_battle struct; must point to already allocated memory
 *  health: an int with the npc's starting health level
 *  stats: a pointer to an existing stat_t struct defining the npc's battle 
           stats (see /include/battle/battle_structs.h)
 *  moves: a pointer to an existing move_t struct defining the npc's battle 
           moves (see /include/battle/battle_structs.h)
 *  ai: the npc's difficulty level (see /include/battle/battle_common.h)
 *  hostility_level: the npc's hostility level 
 *  surrender_level: the level of health at which the npc surrenders the battle
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs
 */
int npc_battle_init(npc_battle_t *npc_battle, int health, stat_t* stats, 
                    move_t* moves, difficulty_t ai, hostility_t hostility_level,
                    int surrender_level);
/*
 * Allocates a new npc_battle struct in the heap.
 *
 * Parameters:
 *  health: an int with the npc's starting health level
 *  stats: a pointer to an existing stat_t struct defining the npc's battle 
           stats (see /include/battle/battle_structs.h)
 *  moves: a pointer to an existing move_t struct defining the npc's battle 
           moves (see /include/battle/battle_structs.h)
 *  ai: the npc's difficulty level (see /include/battle/battle_common.h)
 *  hostility_level: the npc's hostility level 
 *  surrender_level: the level of health at which the npc surrenders the battle
 *
 * Returns:
 *  pointer to allocated npc_battle
 */
npc_battle_t *npc_battle_new(int health, stat_t* stats, move_t* moves, 
		             difficulty_t ai, hostility_t hostility_level, 
			     int surrender_level);

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


// "SET" FUNCTIONS ------------------------------------------------------------
/*
 * Deletes all items from npc inventory and adds them to the room struct.
 *
 * Parameters:
 *  npc: the npc whose items are being transferred
 *  room: the room that the items are being tranferred to
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs
 */
int transfer_all_npc_items(npc_t *npc, room_t *room);

#endif
