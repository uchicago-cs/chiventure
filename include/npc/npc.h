#ifndef _NPC_H
#define _NPC_H

#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "npc/dialogue.h"
#include "playerclass/class_structs.h"
#include "custom-scripts/custom_type.h"
#include "playerclass/class.h"

// NPC STRUCTURE DEFINITION ---------------------------------------------------

/* A non-playable character in game */
typedef struct npc {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;

    /* an object_t struct that contains either a lua file that returns string identifier of the npc
    or the underlying string identifier itself, <21 chars */
    object_t *npc_id;

    /* short description of the npc, <51 chars */
    char *short_desc;

    /* long description of the npc, <301 chars */
    char *long_desc;

    /* the npcs class */
    class_t *npc_class;

    int health;

    /* pointer to an existing convo struct */
    convo_t *dialogue;

    /* pointer to inventory hashtable */
    item_hash_t *inventory;

    /* pointer to an existing class struct */
    class_t *class; 
} npc_t;

/* This typedef is to distinguish between npc_t pointers which are
 * used to point to the npc_t structs in the traditional sense,
 * and those which are used to hash npc_t structs with the
 * UTHASH macros as specified in src/common/include */
typedef struct npc npc_hash_t;


// STRUCT FUNCTIONS -----------------------------------------------------------

/*
 * Initializes an npc with the given parameters.
 *
 * Parameters:
 *  npc: an npc; must point to already allocated memory
 *  npc_id: unique string ID of npc
 *  short_desc: description of npc <51 chars
 *  long_desc: description of npc <301 chars
 *  health: the starting health of the npc
 *  class: a pointer to an existing class_t struct defining the class of the npc
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs
 */
int npc_init(npc_t *npc, object_t *npc_id, char *short_desc, char *long_desc,
             int health, class_t *class);

/*
 * Allocates a new npc in the heap.
 *
 * Parameters:
 *  npc_id: unique string ID of npc
 *  short_desc: description of npc <51 chars
 *  long_desc: description of npc <301 chars
 *  health: the starting health of the npc
 *  class: a pointer to an existing class_t struct defining the class of the npc
 *
 * Returns:
 *  pointer to allocated npc
 */
npc_t *npc_new(object_t *npc_id, char *short_desc, char *long_desc, 
               int health, class_t *class);

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


// "GET" FUNCTIONS ------------------------------------------------------------
/* 
 * Gets short description of npc.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  short description string, NULL if npc is NULL
 */
char *get_sdesc_npc(npc_t *npc);

/* 
 * Gets long description of npc.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  long description string, NULL if npc is NULL
 */
char *get_ldesc_npc(npc_t *npc);

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
 * Function to get a hashtable (uthash) of all items in the npc's inventory.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  hashtable of items, the inventory
 */
item_hash_t *get_npc_inv_hash(npc_t *npc);

/*
 * Function to get a linked list (utlist) of all items in the npc's inventory.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_npc_inv_list(npc_t *npc);


// "SET" FUNCTIONS ------------------------------------------------------------

/*
 * Changes the health of the npc. 
 *
 * Parameters:
 *  npc: the npc
 *  change: the positive or negative change to be made to the health points
 *  max: the maximum health the npc can achieve
 *  
 *  The change has a minimum value of 0  
 *  The change has a maximum value of max
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
 * Removes the given item from the given npc.
 * Note that the memory associated with this item is not freed
 * 
 * Parameters:
 *  npc: the npc from whom to remove the item
 *  item: the item
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurred.
 */
int remove_item_from_npc(npc_t *npc, item_t *item);

/*
 * Adds the given convo to the given npc.
 * 
 * Parameters:
 *  npc: the npc to receive the convo
 *  convo: the convo
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurred.
 */
int add_convo_to_npc(npc_t *npc, convo_t *c); 

#endif
