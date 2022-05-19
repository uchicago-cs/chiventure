#ifndef _NPC_MOVE_H
#define _NPC_MOVE_H

#include "game-state/game_state_common.h"
#include "common/utlist.h"
#include "common/uthash.h"

/* Struct for containing the start time of a certain phenomenon
 * and the number of seconds that phenomenon is supposed to last,
 * used in NPC movement for keeping track of when an (indefinite) moving
 * NPC entered a room and how long it is supposed to be in that room.
 */
typedef struct time_ray {
    time_t start;
    double assigned_time;
} time_ray_t;

/* Doubly-Linked List of an NPCs path Struct
 *
 * Components:
 * room_id: The name of the room
 * room_time: pointer to a struct that holds the start time of when an NPC
 * enters a room, and the number of seconds that the NPC has been in that room
 * prev: the pointer to the previous entry in the list
 * next: the pointer to the next entry in the list
 */
typedef struct npc_path_dll {
    char *room_id;
    time_ray_t *room_time;
    struct npc_path_dll *prev;
    struct npc_path_dll *next;
} npc_path_dll_t;

/*
 * Enum to define NPC movement type - to simplify implementation
 * Definite movement is 0, Indefinite movement is 1
 */
typedef enum mov_type { 
    NPC_MOV_DEFINITE, NPC_MOV_INDEFINITE
} npc_mov_enum_t;

/* Enum to define NPC movement direction (along its room path)
 * Original direction is 0, Reversed direction is 1
 */
typedef enum npc_path_direction {
    NPC_MOV_ORIGINAL, NPC_MOV_REVERSED
} npc_path_direction_t;

/*
 * Struct that deals with NPC movement for both types of npc movements
 *
 * Components:
 *  mov_type: Enum type of movement
 *  npc_path_pos: index of the current location of the npc within
 *      its movement path
 *  npc_path_direction: keeps track of whether the path of the NPC's
 *      movement is in the original direction or reversed.
 *      0 or NPC_MOV_ORIGINAL indicates original direction, 
 *      1 or NPC_MOV_REVERSED indicates the path is in
 *      the opposite direction
 *  track: tracker variable that returns current room id
 *  path: DLL of room_ids and (for indefinite moving NPCs) room_times
 */
typedef struct npc_mov {
    npc_mov_enum_t mov_type;
    npc_path_direction_t npc_path_direction;
    unsigned int npc_path_pos;
    char *track;
    npc_path_dll_t *path;
} npc_mov_t;


// STRUCT FUNCTIONS -----------------------------------------------------------
int time_ray_init(time_ray_t *time_ray, double assigned_time);

time_ray_t *time_ray_new(double assigned_time);

int time_ray_free(time_ray_t *time_ray);

int npc_path_dll_init(npc_path_dll_t *head, npc_mov_enum_t mov_type,
                      char *room_id, double room_time);

npc_path_dll_t *npc_path_dll_new(npc_mov_enum_t mov_type, char *room_id,
                                 double room_time);

/*
 * Function to delete a doubly-linked list (utlist)
 *
 * Parameters:
 *  doubly-linked list of pointers to room_ids
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npc_path_dll_free(npc_path_dll_t *head);

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
int npc_mov_init(npc_mov_t *npc_mov, npc_mov_enum_t mov_type, char *room_id,
                 double room_time);

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
npc_mov_t *npc_mov_new(npc_mov_enum_t mov_type, char *room_id, double room_time);

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

// FUNCTIONS TO EXTEND PATHS --------------------------------------------------
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
 * Adds a room to the path of indefinite NPC movement (and the corresponding
 *  time); changes destination of the NPC
 *
 * Parameters:
 *  npc_mov: The NPC movement struct
 *  room_to_add: The room that has to be added to the path
 *  room_time: The time the NPC has to stay in that room in seconds
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int extend_path_indefinite(npc_mov_t *npc_mov, char *room_id_to_add, double room_time);

// "GET" FUNCTIONS ------------------------------------------------------------
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
 * Gets the number of rooms in an NPC's path
 *
 * Parameters:
 *  - npc_mov: The NPC movement struct
 *
 *  Returns:
 *  - number of rooms in an NPC's path, represented as an int
 */
int get_npc_num_rooms(npc_mov_t *npc_mov);

// COMPARISON FUNCTIONS -------------------------------------------------------
/* Compares the room_id of the current rooms between two
 *   npc_path_dll_t structs
 *
 * Parameters:
 * room1, room2: Two room_list structs
 * 
 * Returns:
 * The strcmp(room1_id, room2_id), so
 * 0 if the room_id of the current rooms in both
 *   npc_path_dll_t structs are the same, otherwise it
 *   will return a non-zero number
 */
int room_id_cmp(npc_path_dll_t *room1, npc_path_dll_t *room2);

// DO SOMETHING FUNCTIONS -----------------------------------------------------
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
 * Moves an npc to the next room
 *
 * Parameters:
 * npc_mov: The NPC movement struct
 *
 * Returns:
 * 0: if move is unsuccessful
 * 1: if npc has reached the end of the path, reverse_path is called
 *  (only for indefinite NPCs), but the move is not implemented
 * 2: if successful move to the next room
 * 3: if npc has nowhere to move (only one room in path)
 */
int move_npc_mov(npc_mov_t *npc_mov);

#endif