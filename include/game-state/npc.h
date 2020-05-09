#ifndef _NPC_H
#define _NPC_H

#include "game_state_common.h"
#include "item.h"

/* A non-playable character in game */
typedef struct npc {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *npc_id;
    int health;
    char **dialogue_trees; //placeholder for now
    item_hash_t *inventory;
} npc_t;

/* This typedef is to distinguish between npc_t pointers which are
* used to point to the npc_t structs in the traditional sense,
* and those which are used to hash npc_t structs with the
* UTHASH macros as specified in src/common/include */
 typedef struct npc npc_hash_t;


/*
 * Allocates a new npc in the heap.
 *
 * Parameters:
 *  npc_id: the unique string ID of the npc
 *  health: the starting health of the npc
 *  dialogue_trees: pointer to directed graphs of dialogue for the npc
 *   // currently a placeholder until dialogue_trees module is made
 *
 * Returns:
 *  pointer to allocated npc
 */
 npc_t *npc_new(char* npc_id, int health, char** dialogue_trees);


 /*
 * Initializes an npc with given health.
 *
 * Parameters:
 *  npc: an npc; must point to already allocated memory
 *  health: the starting health of the npc
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
npc_t *npc_init(npc_t *npc, int health);


/*
 * Frees resources associated with an npc.
 *
 * Parameters:
 *  npc: the npc to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs.
 */
int npc_free(npc_t *npc);


/*
 * Returns the health of an npc
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  int, the npc's health
 */
int get_npc_health(npc_t *npc);

/*
 * Changes the health of the player
 *
 * Parameters:
 *  plyr: the player
 *
 * Returns:
 *  int, remaining health
 */
int change_npc_health(npc_t *npc, int change, int max);


/*
 * Returns the inventory list
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t* get_npc_inventory(npc_t *npc);


/* Adds an item to the given npc
 *
 * Parameters:
 *  npc struct
 *  item struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int add_item_to_npc(npc_t *npc, item_t *item);

/*
 * Function to get a linked list (utlist) of all the items in the player's inventory
 *
 * Parameters:
 *  player
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_inv_npc(npc_t *npc);
#endif