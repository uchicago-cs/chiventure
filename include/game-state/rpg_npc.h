#ifndef _RPG_NPC_H
#define _RPG_NPC_H

#include "game_state_common.h"
#include "item.h"
#include "dialogue.h"
#include "stats.h"

/* A non-playable character in game */
typedef struct npc 
{
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *npc_id;
    int health;
    convo_t *dialogue; // placeholder for incoming dialogue module
    item_hash_t *inventory;
    stats_hash_t *stats;
} npc_t;

/* This typedef is to distinguish between npc_t pointers which are
* used to point to the npc_t structs in the traditional sense,
* and those which are used to hash npc_t structs with the
* UTHASH macros as specified in src/common/include */
 typedef struct npc npc_hash_t;


 /*
 * Initializes an npc with given health.
 *
 * Parameters:
 *  npc: an npc; must point to already allocated memory
 *  health: the starting health of the npc
 *  npc_id: string referring to npc id; passed implicitly
            from npc_new 
 *  dialogue: pointer to a convo struct for the npc
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npc_init(npc_t *npc, char *npc_id, int health, convo_t *dialogue, stats_hash_t *stats);


/*
 * Allocates a new npc in the heap.
 *
 * Parameters:
 *  npc_id: the unique string ID of the npc
 *  health: the starting health of the npc
 *  dialogue: pointer to convo struct for the npc
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  pointer to allocated npc
 */
 npc_t *npc_new(char *npc_id, int health, convo_t *dialogue, stats_hash_t *stats);
 
 
 #endif