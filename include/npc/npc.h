#ifndef _NPC_H
#define _NPC_H

#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "playerclass/class_structs.h"
#include "playerclass/class.h"
#include "npc/dialogue.h"
#include "npc/npc_battle.h"
#include "npc/npc_move.h"
#include "cli/util.h"

/* Forward declaration. Full typedef can be found in npc.h */
typedef struct npc_battle npc_battle_t;
typedef enum hostility hostility_t;

// NPC STRUCTURE DEFINITION ---------------------------------------------------

/* Forward declaration */
typedef struct npc_mov npc_mov_t;
typedef struct convo convo_t;


/* A non-playable character in game */
typedef struct npc {
    /* hh is used for hashtable, as provided in uthash.h */
    /* Second hash handle is for storing npcs in specific rooms */
    UT_hash_handle hh, hh_room;

    /* NPC identifier */
    char *npc_id;

    /* short description of the NPC, <51 chars */
    char *short_desc;

    /* long description of the NPC, <301 chars */
    char *long_desc;

    /* pointer to an existing convo struct */
    convo_t *dialogue;

    /* pointer to inventory hashtable */
    item_hash_t *inventory;

    /* pointer to an existing class struct */
    class_t *class;

    /* pointer to an exisitng npc_move struct */
    npc_mov_t *movement;

     /* boolean representing whether or not the NPC will engage in battles */
    bool will_fight;

    /* either NULL or a pointer to an existing npc_battle struct */
    npc_battle_t *npc_battle;
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
 *  dialogue: a pointer to an existing convo_t struct defining the npc's
              conversations (see /include/npc/dialogue.h)
 *  inventory: a pointer to an existing item_hash_t struct defining the npc's
 *             inventory (see /include/game-state/item.h)
 *  class: a pointer to an existing class_t struct defining the npc's class
           (see /include/playerclass/class_structs.h)
 *  will_fight: a boolean describing whether the npc will engage in battle
 * 
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs
 */
int npc_init(npc_t *npc, char *npc_id, char *short_desc, char *long_desc,
             class_t *class, npc_mov_t *movement, bool will_fight);

/*
 * Allocates a new npc in the heap.
 *
 * Parameters:
 *  npc_id: unique string ID of npc
 *  short_desc: description of npc <51 chars
 *  long_desc: description of npc <301 chars
 *  dialogue: a pointer to an existing convo_t struct defining the npc's 
              conversations (see /include/npc/dialogue.h)
 *  inventory: a pointer to an existing item_hash_t struct defining the npc's
 *             inventory (see /include/game-state/item.h)
 *  class: a pointer to an existing class_t struct defining the npc's class
           (see /include/playerclass/class_structs.h)
 *  will_fight: a boolean describing whether the npc will engage in battle
 *
 * Returns:
 *  pointer to allocated npc
 */
npc_t *npc_new(char *npc_id, char *short_desc, char *long_desc,
               class_t *class, npc_mov_t *movement, bool will_fight);

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

// "CHECK" FUNCTIONS ----------------------------------------------------------

/*
 * Checks if an npc's npc_battle struct is set correctly.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  true if:
 *   - the npc's will_fight is true and it's npc_battle isn't NULL
 *   - the npc's will_fight is false
 *  and false otherwise
 */
bool check_npc_battle(npc_t *npc);

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

/*
 * Function to get an npc's npc_battle struct if it isn't NULL.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  a pointer to the npc's npc_battle struct or NULL
 */
item_list_t *get_npc_inv_list(npc_t *npc);

/*
 * Checks if an item is in the NPC's inventory.
 *
 * Parameters:
 *  npc: the npc
 *  item_id: the item's ID
 *
 * Returns:
 *  true if the item is in the NPC's inventory, false otherwise
 */
bool item_in_npc_inventory(npc_t *npc, char *item_id);


// "SET" FUNCTIONS ------------------------------------------------------------
npc_battle_t *get_npc_battle(npc_t *npc);

/*
 * Returns the health of an npc.
 *
 * Parameters:
 *  npc: the npc
 *
 * Returns:
 *  the npc's health or -1 if its npc_battle field is NULL
 */
int get_npc_health(npc_t *npc);

// "SET" FUNCTIONS ------------------------------------------------------------

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

/*
 * Adds an npc_battle struct to a given npc.
 *
 * Parameters:
 *  npc: the npc to receive the npc_battle struct
 *  health: an int with the npc's starting health level
 *  stats: a pointer to an existing stat_t struct defining the npc's battle
           stats (see /include/battle/battle_structs.h)
 *  moves: a pointer to an existing move_t struct defining the npc's battle
           moves (see /include/battle/battle_structs.h)
 *  ai: the npc's difficulty level (see /include/battle/battle_common.h)
 *  hostility_level: the npc's hostility level
 *  surrender_level: the level of health at which the npc surrenders the battle
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurred.
 */
int add_battle_to_npc(npc_t *npc, int health, stat_t *stats, move_t *moves,
                      difficulty_t ai, hostility_t hostility_level,
                      int surrender_level);

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
 *  the npc's new health
 */
int change_npc_health(npc_t *npc, int change, int max);

// HASH TABLE FUNCTIONS ---------------------------------------------------

/*
 * Deletes and frees the elements of a hashtable of NPCs.
 * Implemented with macros provided by uthash.h
 * 
 * Parameters:
 *  npcs: a hashtable of npcs to be deleted
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if an error occurred.
 */
int delete_all_npcs(npc_hash_t *npcs);

#endif
