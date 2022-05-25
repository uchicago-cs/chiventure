#ifndef _NPC_MOVE_H
#define _NPC_MOVE_H

#include "game-state/game_state_common.h"
#include "common/utlist.h"
#include "common/uthash.h"

/* Doubly-Linked List of Room IDs Struct
 *
 * Components:
 * room_id: The name of the room
 * prev: the pointer to the previous entry in the list
 * next: the pointer to the next entry in the list
 */
typedef struct room_id_dll {
    char *room_id;
    struct room_id_dll *prev;
    struct room_id_dll *next;
} room_id_dll_t;

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
    char *room_id;
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
    room_id_dll_t *npc_path;
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
    room_id_dll_t *npc_path;
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

/* Enum to define NPC movement direction (along its path)
 * Original direction is 0, Reversed direction is 1
 */
 typedef enum npc_path_direction {
     NPC_MOV_ORIGINAL, NPC_MOV_REVERSED
  } npc_path_direction_t;


/*
 * Struct that deals with NPC movement for both types of npc movements
 *
 * Components:
 *  npc_id: The NPC being considered
 *  npc_mov_type: Union with the structs for both mov types
 *  mov_type: Enum type of movement
 *  track: tracker variable that returns current room id
 *  npc_path_pos: index of the current location of the npc within
 *      its movement path
 *  npc_path_direction: keeps track of whether the path of the NPC's
 *      movement is in the original direction or reversed.
 *      0 or NPC_MOV_ORIGINAL indicates original direction, 
 *      1 or NPC_MOV_REVERSED indicates the path is in
 *      the opposite direction
 */
typedef struct npc_mov {
    npc_mov_type_t npc_mov_type;
    npc_mov_enum_t mov_type;
    npc_path_direction_t npc_path_direction;
    unsigned int npc_path_pos;
    char *track;
} npc_mov_t;


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
int npc_mov_init(npc_mov_t *npc_mov, npc_mov_enum_t mov_type, char *room_id);


/*
 * Returns newly heap allocated npc_mov struct on success, 
 * and NULL if an error occurs
 *
 * Parameters:
 *  npc_id: The ID of the NPC that is being referred to; must point to
 *          allocated memory
 *  mov_type: The type of movement that the npc will have
 *  room_id: The room_id that the npc will begin in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
npc_mov_t *npc_mov_new(npc_mov_enum_t mov_type, char *room_id);


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
int register_npc_room_time(npc_mov_t *npc_mov, char *room_id, int time);


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
int extend_path_definite(npc_mov_t *npc_mov, char *room_id_to_add);


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
int extend_path_indefinite(npc_mov_t *npc_mov, char *room_id_to_add, int time);


/*
 * Returns the room that the npc is currently in
 *
 * Parameters:
 *  npc_mov: The NPC movement struct
 *
 * Returns:
 *  The room the NPC is in as a char*, NULL if error.
 */
char *get_npc_curr_room_id(npc_mov_t *npc_mov);

/*
 * Returns the room id of the room that 
 *  the npc will move to next if/when it is called to
 *
 * Parameters:
 *  npc_mov: The NPC movement struct
 *
 * Returns:
 *  The room id of the room that the npc 
 *  will move to next if/when it is called to
 */
char *get_next_npc_room_id(npc_mov_t *npc_mov);

/* 
* Returns the index position of the room that the npc is currently in
*
* Parameters: npc_mov: The NPC movement struct
*
* Returns:
* The integer index of the step of the movement path that the NPC is currently in
*/
unsigned int get_npc_path_pos(npc_mov_t *npc_mov);

/*
* Returns whether an NPCs path is in the original direction or reversed
*
* Parameters: npc_mov: the NPC movement struct
*
* Returns:
* 0 if the path is in the original direction, 1 if the path is in the reverse direction
*/
unsigned int get_npc_path_direction(npc_mov_t *npc_mov);

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
int flip_npc_path_direction(npc_mov_t *npc_mov);

/*
 * Gets the number of rooms in an NPC's path
 *
 * Parameters:
 *  - npc_mov: The NPC movement struct
 *
 *  Returns:
 *  - number of rooms in an NPC's path, represented as an int
 */
int get_npc_num_rooms(npc_mov_t *npc_mov);

/* Compares the room_id of the current rooms between two
 *   room_id_dll_t structs
 *
 * Parameters:
 * room1, room2: Two room_list structs
 * 
 * Returns:
 * The strcmp(room1_id, room2_id), so
 * 0 if the room_id of the current rooms in both
 *   room_id_dll_t structs are the same, otherwise it
 *   will return a non-zero number
 */
int room_id_cmp(room_id_dll_t *room1, room_id_dll_t *room2);

/*
 * Moves the npc to the next room for npcs with definite movement
 *
 * Parameters:
 * npc_mov: The NPC movement struct
 *
 * Returns:
 * 0 if move in unsuccessful
 * 1 npc has reached the end of the path, flip_npc_path_direction is called, but
 *   the move is not implemented
 * 2 successful move to the next room
 * 3 npc has nowhere to move
*/
int move_npc_definite(npc_mov_t *npc_mov);

/*
 * Moves the npc to the next room for npcs with indefinite movement
 *
 * Parameters:
 * npc_mov: The NPC movement struct
 *
 * Returns:
 * 0 if move in unsuccessful
 * 1 npc has reached the end of the path, flip_npc_path_direction is called, but
 *   the move is not implemented
 * 2 successful move to the next room
 * 3 npc has nowhere to move
 */
int move_npc_indefinite(npc_mov_t *npc_mov);

/*
 * Moves an npc to the next room
 *
 * Parameters:
 * npc_mov: The NPC movement struct
 *
 * Returns:
 * 0 if move is unsuccessful
 * 1 npc has reached the end of the path, reverse_path is called, but
 *   the move is not implemented
 * 2 successful move to the next room
 * 3 npc has nowhere to move
 */
int move_npc_mov(npc_mov_t *npc_mov);

/*
 * Function to delete a doubly-linked list (utlist)
 *
 * Parameters:
 *  doubly-linked list of pointers to room_ids
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_room_id_dll(room_id_dll_t *head);

#endif