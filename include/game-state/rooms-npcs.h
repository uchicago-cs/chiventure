#ifndef _ROOMS_NPCS_H
#define _ROOMS_NPCS_H

#include "game_state_common.h"
#include "custom-scripts/custom_type.h"
#include "item.h"
#include "room.h"
#include "npc.h"


/* Struct for adding and handling npcs in rooms */
typedef struct npcs_in_room {
    UT_hash_handle hh;
    /*Object_t Description: object_t is the generic custom scripts struct that 
   can hold a variety of different types including "char*".*/
   /*Changes to Room_ID: We are using this struct to modify the room_id 
   which will enable custom scripts and lua files to be loaded*/
    object_t *room_id;    
    npc_hash_t *npc_list; //hash table storing the npcs in the room
    int num_of_npcs; //number of npcs in the room
} npcs_in_room_t;

/* To make the struct hashable */
typedef struct npcs_in_room npcs_in_room_hash_t;

/* Struct to encapsulate the time an NPC should stay in that particular room and the room details */
typedef struct time_in_room {
    UT_hash_handle hh;
    long room_id;
    int sec; //time the NPC shoudl stay in this particular room
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
    /*Changes to npc_ID: We are using this struct to modify the room_id 
   which will enable custom scripts and lua files to be loaded*/
    object_t *npc_id; //the NPC being considered
    npc_mov_type_u *npc_mov_type; //union with the structs for both mov types
    npc_mov_type_e mov_type; //enum type of movement
    /*Changes to track: We are using this struct to modify the track 
   which will enable custom scripts and lua files to be loaded*/
    object_t *track; //tracker variable that returns current room id
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
 *  npc_id:  the npc that is being referred to; must ppint to allocated
 *          memory
 *  mov_type: the tpye of movement that the npc will have
 *  room: the room that the npc will start in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
/*Changes to npc_ID: We are using this struct to modify the npc_id 
   which will enable custom scripts and lua files to be loaded*/
int npc_mov_init(npc_mov_t *npc_mov, object_t *npc_id, npc_mov_type_e mov_type,
                room_t *room);


/*
 * Allocates a new npcs_in_room struct in the heap
 *
 * Parameters:
 *  room_id: the unique id of the room
 *
 * Returns:
 *  pointer to allocated npcs_in_room struct
 */
/*Changes to room_id: We are using this struct to modify the room_id 
   which will enable custom scripts and lua files to be loaded*/
npcs_in_room_t *npcs_in_room_new(object_t *room_id);


/*
 * Allocates a new npc_mov struct in the heap
 *
 * Parameters:
 *  npc_id:  the id of the npc that is being referred to; must ppint to allocated
 *          memory
 *  mov_type: the tpye of movement that the npc will have
 *  room_id: the room that the npc will begin in
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
/*Changes to npc_ID: We are using this struct to modify the npc_id 
   which will enable custom scripts and lua files to be loaded*/
/*Changes to room_id: We are using this struct to modify the room_id 
   which will enable custom scripts and lua files to be loaded*/
npc_mov_t *npc_mov_new(object_t *npc_id, npc_mov_type_e mov_type, object_t *room_id);


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
int get_num_of_npcs(npcs_in_room_t *npcs_in_room);


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
 * Adds a room to the path of definite NPC movement - changes destination of the NPC
 * 
 * Parameters:
 *  npc_mov: the NPC movement struct
 *  room_to_add: the room that has to be added to the path
 * 
 * Returns:
 *  1 for success, 0 for error.failure
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
 *  1 for success, 0 for error.failure
 */
room_list_t* extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time);

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
