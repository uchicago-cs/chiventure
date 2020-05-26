#ifndef _NPC_H
#define _NPC_H

<<<<<<< HEAD
#include "game_state/game_state_common.h"
#include "game-state/item.h"
//TODO-#include "dialogue.h"
#include "game-state/stats.h"
=======
#include "game_state_common.h"
#include "item.h"
#include "dialogue.h"
#include "room.h"
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c

/* A non-playable character in game */
typedef struct npc 
{
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *npc_id;
    int health;
<<<<<<< HEAD
    // convo_t *dialogue;  placeholder for incoming dialogue module
    item_hash_t *inventory;
    stats_hash_t *stats;
=======
    convo_t *dialogue; // placeholder for incoming dialogue module
    item_hash_t *inventory;
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
} npc_t;

/* This typedef is to distinguish between npc_t pointers which are
* used to point to the npc_t structs in the traditional sense,
* and those which are used to hash npc_t structs with the
* UTHASH macros as specified in src/common/include */
 typedef struct npc npc_hash_t;

<<<<<<< HEAD

 /*
=======
/* Struct for addings npcs to rooms */
typedef struct npcs_in_room {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    long room_id;
    char *room_name;
    npc_hash_t *npc_list; //hash table storing the npcs that are in the room
    int num_of_npcs; //number of npcs in the room
} npcs_in_room_t;

typedef struct npcs_in_room npcs_in_room_hash_t;

/*
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
 * Initializes an npc with given health.
 *
 * Parameters:
 *  npc: an npc; must point to already allocated memory
 *  health: the starting health of the npc
 *  npc_id: string referring to npc id; passed implicitly
<<<<<<< HEAD
            from npc_new
 *  stats: pointer to the stats hash table for the NPC
 *  TODO-dialogue: pointer to a convo struct for the npc
=======
            from npc_new 
 *  dialogue: pointer to a convo struct for the npc
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
 *   // placeholder for incoming dialogue module
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
<<<<<<< HEAD
int npc_init(npc_t *npc, char *npc_id, int health, stats_hash_t *stats);
=======
int npc_init(npc_t *npc, char *npc_id, int health, convo_t *dialogue);


/*
 * Initializes the struct that holds the npcs inside a certain room
 *
 * Parameters:
 *  npcs_in_room: the npcs in a certain room; must point to already allocated memory
 *  room_id: the id of the room you are referring to
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, long room_id,
                      char* room_name);
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c


/*
 * Allocates a new npc in the heap.
 *
 * Parameters:
 *  npc_id: the unique string ID of the npc
 *  health: the starting health of the npc
 *  dialogue: pointer to convo struct for the npc
<<<<<<< HEAD
 *  TODO-dialogue: pointer to convo struct for the npc
 *   // placeholder for incoming dialogue module
 *  stats: pointer to the stats hash table for the NPC
=======
 *   // placeholder for incoming dialogue module
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
 *
 * Returns:
 *  pointer to allocated npc
 */
<<<<<<< HEAD
 npc_t *npc_new(char *npc_id, int health, stats_hash_t *stats);
 
 /*
=======
 npc_t *npc_new(char *npc_id, int health, convo_t *dialogue);


/*
 * Allocates a new npcs_in_room struct in the heap
 *
 * Parameters:
 *  room_id: the unique id of the room
 *
 * Returns:
 *  pointer to allocated npcs_in_room struct
 */
 npcs_in_room_t *npcs_in_room_new(long room_id, char* room_name);


/*
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
 * Frees resources associated with an npc.
 *
 * Parameters:
 *  npc: the npc to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurs.
 */
int npc_free(npc_t *npc);

<<<<<<< HEAD
=======

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


>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
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
<<<<<<< HEAD
 
 /*
=======


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

/*
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
 * Changes the health of the npc. 
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  int, updated health
 */
int change_npc_health(npc_t *npc, int change, int max);

<<<<<<< HEAD
=======

>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
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
 *  npc: the npc
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_inv_npc(npc_t *npc);

<<<<<<< HEAD
 #endif
=======

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

#endif
>>>>>>> 0b4d69f5aa0164f82845e43acd9dceaf6347047c
