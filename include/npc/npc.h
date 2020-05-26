#ifndef _NPC_H
#define _NPC_H

#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "game-state/room.h"
//TODO-#include "dialogue.h"

// NPC STRUCTURE DEFINITION + BASIC FUNCTIONS ---------------------------------

/* A non-playable character in game */
typedef struct npc {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *npc_id;
    int health;
    // convo_t *dialogue;  placeholder for incoming dialogue module
    item_hash_t *inventory;
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
 *          from npc_new 
 *  TODO-dialogue: pointer to a convo struct for the npc
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs
 */
int npc_init(npc_t *npc, char *npc_id, int health);


/*
 * Allocates a new npc in the heap.
 *
 * Parameters:
 *  npc_id: the unique string ID of the npc
 *  health: the starting health of the npc
 *  TODO-dialogue: pointer to convo struct for the npc
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  pointer to allocated npc
 */
 npc_t* npc_new(char *npc_id, int health);


/*
 * Frees resources associated with an npc.
 *
 * Parameters:
 *  npc: the npc to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs
 */
int npc_free(npc_t *npc);


/*
 * Returns the health of an npc.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  the npc's health
 */
int get_npc_health(npc_t *npc);


/*
 * Changes the health of the npc. 
 *
 * Parameters:
 *  npc: the npc
 *  change: the positive or negative change to be made to the health points
 *  max: the maximum health the npc can achieve
 * 
 * Returns:
 *  int, updated health
 */
int change_npc_health(npc_t *npc, int change, int max);


/* 
 * Adds the given item to the given npc.
 *
 * Parameters:
 *  npc: the npc to receive the item
 *  item: the item
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurred.
 */
int add_item_to_npc(npc_t *npc, item_t *item);


/*
 * Function to get a hashtable (uthash) of all items in the npc's inventory.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t* get_npc_inv_hash(npc_t *npc);


/*
 * Function to get a linked list (utlist) of all items in the npc's inventory.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t* get_npc_inv_list(npc_t *npc);


// NPCS IN ROOM STRUCTURE DEFINITION + BASIC FUNCTIONS ------------------------

/* Struct for adding npcs to rooms */
typedef struct npcs_in_room {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    long room_id;
    char *room_name;
    npc_hash_t *npc_list; //hash table storing the npcs that are in the room
    int num_of_npcs; //number of npcs in the room
} npcs_in_room_t;

/* This typedef is to distinguish between npcs_in_room_t pointers which are
 * used to point to the npcs_in_room_t structs in the traditional sense,
 * and those which are used to hash npcs_in_room_t structs with the
 * UTHASH macros as specified in src/common/include */
typedef struct npcs_in_room npcs_in_room_hash_t;

/*
 * Initializes the struct that holds the npcs inside a certain room.
 *
 * Parameters:
 *  npcs_in_room: the npcs in a certain room; must point to already 
 *                allocated memory
 *  room_id: the id of the room you are referring to
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, long room_id,
                      char *room_name);


/*
 * Allocates a new npcs_in_room struct in the heap.
 *
 * Parameters:
 *  room_id: the unique id of the room
 *
 * Returns:
 *  pointer to allocated npcs_in_room struct
 */
 npcs_in_room_t* npcs_in_room_new(long room_id, char *room_name);


/*
 * Frees resources associated with an npcs_in_room struct.
 *
 * Parameters:
 * npcs_in_room: the npcs_in_room struct to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs.
 */
int npcs_in_room_free(npcs_in_room_t *npcs_in_room);


/*
 * Returns the number of npcs in a room
 *
 * Parameters:
 *  npcs_in_room: the struct holding the npcs in the room
 *
 * Returns:
 *  int, the number of npcs in the room
 */
int npcs_in_room_get_number(npcs_in_room_t *npcs_in_room);


/* Adds an npc to the given npcs_in_room
 *
 * Parameters:
 *  npcs_in_room_t: pointer to the npcs_in_room struct
 *  npc_t: pointer to an npc
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurred.
 */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc);


#endif