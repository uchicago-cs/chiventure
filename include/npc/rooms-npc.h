#ifndef _ROOMS_NPC_H
#define _ROOMS_NPC_H

#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "game-state/room.h"
#include "npc/npc.h"
#include "custom-scripts/custom_type.h"

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
   /*Object_t Description: object_t is the generic custom scripts struct that 
   can hold a variety of different types including "char*".*/
   /*Changes to Room_ID: We are using this struct to modify the room_id 
   which will enable custom scripts and lua files to be loaded*/
    object_t* room_id;
    npc_hash_t *npc_list;
    int num_of_npcs;
} npcs_in_room_t;

/* To make the struct hashable */
typedef struct npcs_in_room npcs_in_room_hash_t;

/* 
 * Struct to encapsulate the time an NPC should stay in that particular room 
 *  and the room details
 * 
 * Components:
 *  room_id: The name of the room
 *  time: Time in miliseconds the NPC will stay in this particular room
 */
typedef struct npc_room_time {
    UT_hash_handle hh;
    char* room_id;
    int time; 
} npc_room_time_t;

/* To make the struct hashable */
typedef struct npc_room_time npc_room_time_hash_t;


/* 
 * Struct for the definite path movement for npcs 
 *  Definite path: when the NPC has a certain start and end with a 
 *      role to play in the destination room
 * 
 * Component:
 *  npc_path: The list of rooms that the NPC will go through
 */
typedef struct npc_mov_definite {
    room_list_t *npc_path;
} npc_mov_definite_t;


/* 
 * Struct for the indefinite path movement for NPCs 
 *  Indefinite path: this is the second case when an NPC is simply moving 
 *      through the map but without a definite end point.
 * 
 * Components:
 *  npc_path: The list of rooms that the NPC will go through
 *  room_time: Time in miliseconds for the NPC corresponding to each room
 */
typedef struct npc_mov_indefinite {
    room_list_t *npc_path;
    npc_room_time_hash_t *room_time;
} npc_mov_indefinite_t;


/* Union that holds the definite and indefinite movement structs */
typedef union npc_mov_type {
    npc_mov_definite_t *npc_mov_definite;
    npc_mov_indefinite_t *npc_mov_indefinite;
} npc_mov_type_t;

/* 
 * Enum to define NPC movement type - to simplify implementation 
 * Definite movement is 0, Indefinite movement is 1
 */
enum mov_type { NPC_MOV_DEFINITE, NPC_MOV_INDEFINITE };

typedef enum mov_type npc_mov_enum_t;


/* 
 * Struct that deals with NPC movement for both types of npc movements 
 * 
 * Components:
 *  npc_id: The NPC being considered
 *  npc_mov_type: Union with the structs for both mov types
 *  mov_type: Enum type of movement
 *  track: tracker variable that returns current room id
 */
typedef struct npc_mov {
 /*Changes to npc_ID: We are using this struct to modify the room_id 
   which will enable custom scripts and lua files to be loaded*/
    object_t *npc_id;
    npc_mov_type_t npc_mov_type;
    npc_mov_enum_t mov_type;
     /*Changes to npc_ID: We are using this struct to modify the room_id 
   which will enable custom scripts and lua files to be loaded*/
    object_t *track;
} npc_mov_t;


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
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, object_t *room_id);


/*
 * Initializes the struct that handles the movement of an npc
 *
 * Parameters:
 *  npc_mov: The id of the npc that is being addressed; must point to already
 *          allocated memory
 *  npc_id: The npc that is being referred to; must ppint to allocated
 *          memory
 *  mov_type: The tpye of movement that the npc will have
 *  room: The room that the npc will start in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npc_mov_init(npc_mov_t *npc_mov, objec_t* npc_id, npc_mov_enum_t mov_type, room_t *room);


/*
 * Allocates a new npcs_in_room struct in the heap
 *
 * Parameters:
 *  room_id: The unique id of the room
 *
 * Returns:
 *  Pointer to allocated npcs_in_room struct
 */
npcs_in_room_t *npcs_in_room_new(object_t *room_id);


/*
 * Allocates a new npc_mov struct in the heap
 *
 * Parameters:
 *  npc_id: The ID of the NPC that is being referred to; must ppint to 
 *          allocated memory
 *  mov_type: The tpye of movement that the npc will have
 *  room: The room that the npc will begin in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
npc_mov_t *npc_mov_new(object_t* npc_id, npc_mov_enum_t mov_type, room_t *room);


/*
 * Frees resources associated with an npcs_in_room struct
 *
 * Parameters:
 *  npcs_in_room: The npcs_in_room struct to be freed
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npcs_in_room_free(npcs_in_room_t *npcs_in_room);


/*
 * Frees resources associated with an npc_mov struct
 *
 * Parameters:
 *  npc_mov: The npc_mov struct to be freed
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npc_mov_free(npc_mov_t *npc_mov);


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


/* 
 * Registers a time spent in a specific room in the hash table, if the room is 
 *  not yet in the hash table it will create a new entry
 * 
 * Parameters:
 *  npc_mov: The npc_mov struct
 *  room: The room to be registered
 *  time: The time to be spent in the room by that NPC in miliseconds
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int register_npc_room_time(npc_mov_t *npc_mov, room_t *room, int time);


/* 
 * Adds a room to the path of definite NPC movement - changes destination of the NPC
 * 
 * Parameters:
 *  npc_mov: The NPC movement struct
 *  room_to_add: The room that has to be added to the path
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int extend_path_def(npc_mov_t *npc_mov, room_t *room_to_add);


/* 
 * Adds a room to the path of indefinite NPC movement (not the corresponding 
 *  time); changes destination of the NPC
 * 
 * Parameters:
 *  npc_mov: The NPC movement struct
 *  room_to_add: The room that has to be added to the path
 *  time: The time the NPC has to stay in that room in miliseconds
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time);


/* 
 * Returns the room that the npc is currently in 
 *
 * Parameters:
 *  npc_mov: The NPC movement struct
 *
 * Returns:
 *  The room the NPC is in as a char*, NULL if error.
 */
char* track_room(npc_mov_t *npc_mov);


/* 
 * Reverses the path, so that the npc goes back to where it started
 *  (this is only for definite movement paths, because indef will naturally 
 *  move back and forth)
 * 
 * Parameters:
 *  npc_mov: The NPC movement struct
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int reverse_path(npc_mov_t *npc_mov);


#endif
