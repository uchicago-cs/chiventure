#ifndef _ROOMS_NPC_H
#define _ROOMS_NPC_H

#include "npc/npc.h"

/* 
 * Struct for adding and handling npcs in rooms 
 * 
 * Components:
 *  room_id: The name of the room
 *  npc_list: Hash table storing the npcs in the room
 *  num_of_npcs: Number of npcs in the room
 */
typedef struct npcs_in_room {
    UT_hash_handle hh;
    char* room_id;
    npc_hash_t *npc_list;
    int num_of_npcs;
} npcs_in_room_t;

/* To make the struct hashable */
typedef struct npcs_in_room npcs_in_room_hash_t;


/*
 * Initializes the struct that holds the npcs inside a certain room
 *
 * Parameters:
 *  npcs_in_room: the npcs in a certain room; must point to already
 *                allocated memory
 *  room: the room that the npc will start in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, char *room_id);

/*
 * Allocates a new npcs_in_room struct in the heap
 *
 * Parameters:
 *  room_id: The unique id of the room
 *
 * Returns:
 *  Pointer to allocated npcs_in_room struct
 */
npcs_in_room_t *npcs_in_room_new(char* room_id);

/*
 * Frees resources associated with an npcs_in_room struct
 * Deletes npc_list hashtable, but does not free npcs in hash table
 *
 * Parameters:
 *  npcs_in_room: The npcs_in_room struct to be freed
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npcs_in_room_free(npcs_in_room_t *npcs_in_room);

/*
 * Returns the number of npcs in a room
 *
 * Parameters:
 *  npcs_in_room: The struct holding the npcs in the room
 *
 * Returns:
 *  The number of NPCs in the room as an int
 */
int npcs_in_room_get_number(npcs_in_room_t *npcs_in_room);

/* Adds an npc to the given npcs_in_room
 *
 * Parameters:
 *  npcs_in_room_t: Pointer to the npcs_in_room struct
 *  npc_t: Pointer to an NPC
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs or if NPC is already in the
 *      respective room.
 */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc);

/* Removes an npc in a given npcs_in_room
 *
 * Parameters:
 *  npcs_in_room_t: Pointer to the npcs_in_room struct
 *  npc_t: Pointer to an NPC
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs or if NPC is not
 *      in the room
 */
int delete_npc_from_room(npcs_in_room_t *npcs_in_room, npc_t *npc);

#endif
