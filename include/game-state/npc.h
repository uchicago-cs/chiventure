#ifndef _NPC_H
#define _NPC_H

#include "game_state_common.h"
#include "item.h"
#include "dialogue.h"
#include "room.h"

/* A non-playable character in game */
typedef struct npc 
{
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *npc_id;
    int health;
    convo_t *dialogue; // placeholder for incoming dialogue module
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
            from npc_new 
 *  dialogue: pointer to a convo struct for the npc
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npc_init(npc_t *npc, char *npc_id, int health, convo_t *dialogue);


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
 npc_t *npc_new(char *npc_id, int health, convo_t *dialogue);


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
 * Returns the health of an npc.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  int, the npc's health
 */
int get_npc_health(npc_t *npc);


/*
 * Returns the number of npcs in a room
 *
 * Parameters:
 *  npcs_in_room: the struct holding the npcs in the room
 *
 * Returns:
 *  int, the number of npcs in the room
 */
int get_num_of_npcs(npcs_in_room_t *npcs_in_room);

/*
 * Changes the health of the npc. 
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  int, updated health
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


/* Function to get a linked list (utlist) of all the items in the player's inventory
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_inv_npc(npc_t *npc);


/* 
 * Adds a room to the path of definite NPC movement - changes destination of the NPC
 * 
 * Parameters:
 *  npc_mov: the NPC movement struct
 *  room_to_add: the room that has to be added to the path
 * 
 * Returns:
 *  SUCCESS (1) if successful, FAILURE (0) if error occured.
 */
int extend_path_def(npc_mov_t *npc_mov, room_t *room_to_add);

/* extend_path_indef()
 * adds a room to the path that the npc will travel through, ONLY when the npc is has a indefinite path
 * returns SUCCESS or FAILURE
 */
int extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time);

/* reverse_path()
 * reverses the path, so that the npc goes back to where it started
 * returns SUCCESS or FAILURE
 */
int reverse_path(npt_mov_t  *npc_mov);

/* change_time_in_room()
 * changes the time spent in a certain room by and npc, ONLY Possible when the npc has an indeinfite path
 * returns SUCCESS or FAILURE
 */
int change_time_in_room(npc_mov_t  *npc_mov, room_t *room_to_change, int time);

/* track_room()
 * returns the room_id of the room that the npc is currently in
 */
char* track_room(npc_mov_t *npc_mov);

/* auto_gen_movement()
 * automatically allows npcs to randomly move through adjacent rooms,
 * while spending an arbitrary time in each room
 */
npc_mov_t *auto_gen_movement(npc_t *npc, room_t *starting_room);

#endif