#ifndef _ROOMS_NPC_H
#define _ROOMS_NPC_H

#include "game_state_common.h"
#include "item.h"
#include "room.h"
#include "npc.h"


/* Struct for adding and handling npcs in rooms */
typedef struct npcs_in_room {
    UT_hash_handle hh;
    char* room_id;
    npc_hash_t *npc_list; //hash table storing the npcs in the room
    int num_of_npcs; //number of npcs in the room
} npcs_in_room_t;

/* To make the struct hashable */
typedef struct npcs_in_room npcs_in_room_hash_t;

/* Struct to encapsulate the time an NPC should stay in that particular room and the room details */
typedef struct time_in_room {
    UT_hash_handle hh;
    char* room_id;
    int time; //time in seconds the NPC will stay in this particular room
} time_in_room_t;

/* To make the struct hashable */
typedef struct time_in_room time_in_room_hash_t;


/* 
 * Struct for the definite path movement for npcs 
 * Definite path: when the NPC has a certain start and end with a 
 * role to play in the destination room
 */
typedef struct mov_def {
    room_list_t *npc_path;
} mov_def_t;


/* 
 * Struct for the indefinite path movement for npcs 
 *  Inefinite path: this is the second case when an
 * npc is simply moving through the map but without
 * a definite end point.
 */
typedef struct mov_indef {
    room_list_t *npc_path;
    time_in_room_hash_t *room_time;
} mov_indef_t;


/* Union that holds the definite and indefinite movement structs */
typedef union npc_mov_type {
    mov_def_t *mov_def;
    mov_indef_t *mov_indef;
} npc_mov_type_u;

/* Enum to define NPC movement type - to simplify implementation */
enum mov_type { MOV_DEF, MOV_INDEF }; //def is 0, indef is 1

typedef enum mov_type npc_mov_type_e;


/* Struct that deals with NPC movement for both types of npc movements */
typedef struct npc_mov {
    char *npc_id; //the NPC being considered
    npc_mov_type_u *npc_mov_type; //union with the structs for both mov types
    npc_mov_type_e mov_type; //enum type of movement
    char* track; //tracker variable that returns current room id
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
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, room_t *room);


/*
 * Initializes the struct that handles the movement of an npc
 *
 * Parameters:
 *  npc_mov: the id of the npc that is being addressed; must point to already
 *            allocated memory
 *  npc_id: the npc that is being referred to; must ppint to allocated
 *          memory
 *  mov_type: the tpye of movement that the npc will have
 *  room: the room that the npc will start in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npc_mov_init(npc_mov_t *npc_mov, char* npc_id, npc_mov_type_e mov_type, room_t *room);


/*
 * Allocates a new npcs_in_room struct in the heap
 *
 * Parameters:
 *  room_id: the unique id of the room
 *
 * Returns:
 *  pointer to allocated npcs_in_room struct
 */
npcs_in_room_t *npcs_in_room_new(char* room_id);


/*
 * Allocates a new npc_mov struct in the heap
 *
 * Parameters:
 *  npc_id:  the id of the npc that is being referred to; must ppint to allocated
 *          memory
 *  mov_type: the tpye of movement that the npc will have
 *  room: the room that the npc will begin in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
npc_mov_t *npc_mov_new(char* npc_id, npc_mov_type_e mov_type, room_t *room);


/*
 * Frees resources associated with an npcs_in_room struct
 *
 * Parameters:
 * npcs_in_room: the npcs_in_room struct to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs.
 */
int npcs_in_room_free(npcs_in_roomt_t *npcs_in_room);


/*
 * Frees resources associated with an npc_mov struct
 *
 * Parameters:
 * npc_mov: the npc_mov struct to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs.
 */
int npc_mov_free(npc_mov_t *npc_mov);


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
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc);


/* 
 * Registers a time spent in a specific room in the hash table,
 *  - if the room is not yet in the hash table it will create a new entry
 * 
 * Parameters:
 *  npc_mov: the npc_mov struct
 *  room: the room  to be  registered
 *  time: the time to be spent in that room in seconds
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int register_time_in_room(npc_mov_t *npc_mov, room_t *room, int time);


/* 
 * Adds a room to the path of definite NPC movement - changes destination of the NPC
 * 
 * Parameters:
 *  npc_mov: the NPC movement struct
 *  room_to_add: the room that has to be added to the path
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int extend_path_def(npc_mov_t *npc_mov, room_t *room_to_add);


/* 
 * Adds a room to the path of indefinite NPC movement (not the corresponding time)
    - changes destination of the NPC
 * 
 * Parameters:
 *  npc_mov: the NPC movement struct
 *  room_to_add: the room that has to be added to the path
 *  time: the time the NPC has to stay in that room
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time);


/* 
 * Returns the room that the npc is currently in 
 *
 * Parameters:
 *  npc_mov: the NPC movement struct
 *
 * Returns:
 *  The room the NPC is in as a char*, NULL if error.
 */
char* track_room(npc_mov_t *npc_mov);


/* 
 * Reverses the path, so that the npc goes back to where it started
 *  - this is only for definite  movement paths, because indef will naturally
 *    move back and forth
 * 
 * Parameters:
 *  npc_mov: the NPC movement struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occured.
 */
int reverse_path(npt_mov_t *npc_mov);


#endif