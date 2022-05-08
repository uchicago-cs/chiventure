#ifndef _NPC_ACTION_H
#define _NPC_ACTION_H

#include "game-state/game_state_common.h"
#include "game-state/item.h"
#include "npc/npc.h"
#include "common/utlist.h"

// NPC ACTION STRUCTURE DEFINITION --------------------------------------------

/* An enumeration of all supported npc actions. Inspired by, but not directly
 * related to, actions KIND 1, 2, 3, in action management code.
 * 
 * KIND 4 ACTIONS - ACTION <npc>
 * KIND 5 ACTIONS - ACTION <npc> <item>
 * KIND 6 ACTIONS - ACTION <npc> <item> <item>
 */
typedef enum npc_actions {
    // KIND 4 ACTIONS
    TALK_TO,
    IGNORE,
    // ATTACK,
    
    // KIND 5 ACTIONS
    GIVE,
    STEAL,

    // KIND 6 ACTIONS
    TRADE,
    BUY
} npc_actions_t;

/* Each enum corresponds to a different "KIND" of npc action */
enum npc_action_kind {
    NPC = 4,
    NPC_ITEM = 5,
    NPC_ITEM_ITEM = 6
};

/* An npc action struct that contains the following:
 * - c_name: the 'canonical' string that should call the enum
 * - kind: an enumeration of the kind of action
 */
typedef struct npc_action {
    char *c_name; // e.g. "ignore"
    npc_actions_t action;
} npc_action_t;

/* A linked list struct that contains the following:
 * - action: the NPC action at the head of the list
 * - next: the next item in the linked list
 */
typedef struct list_npc_action {
    npc_action_t *npc_action;
    struct list_npc_action *next;
} list_npc_action_t;

// STRUCT FUNCTIONS -----------------------------------------------------------

/*
 * Allocates a new npc_action in the heap.
 *
 * Parameters:
 *    - c_name: The name of the npc action e.g ignore,give
 *    - kind: whether the action involves just the NPC, an NPC and an item, or
 *            an NPC and two items
 *
 * Returns:
 *    - A pointer to the npc_action, or NULL if an npc_action
 *      cannot be allocated
 */
npc_action_t *npc_action_new(char *c_name, npc_actions_t action);

/*
 * Initializes the constituents of an npc_action
 *
 * Parameters:
 *    - a: An npc_action pointer. Must point to already allocated memory.
 *    - c_name: The name of the npc_action
 *    - kind: the kind of npc-action involved ie just NPC, or NPC and items to   
 *            be given or taken
 * Returns:
 *    - 0 on success, 1 if an error occurs.
 */
int npc_action_init(npc_action_t *a, char *c_name, npc_actions_t action);

/*
 * Frees the resources associated with an npc_action
 *
 * Parameters:
 *    - a: An npc_action. Must point to an npc_action allocated with
 *         npc_action_new
 *
 * Returns:
 *    - Always returns 0.
 */
int npc_action_free(npc_action_t *a);

/*
 * A function that returns a linked list of all supported NPC actions
 *
 * Parameters:
 *  - none
 *
 * Returns:
 *  - a linked list of all NPC actions
 */
list_npc_action_t *get_npc_actions();

/* A function that executes KIND 4 actions (ACTION <npc>)
 *
 * Parameters:
 * - c: A context struct encapsulating the shared state in chiventure
 * - a: An NPC action type struct
 * - npc: An npc struct
 * - 7 if an effect for the action wasn't applied, failure string as an out 
 *   parameter
 * - 7 if an effect for the action wasn't applied, failure string as an out
 *   parameter
 * - ret_string: A pointer to a string describing the result of the function
 *   - NOTE: THIS STRING IS MALLOCED AND MUST BE FREED BY USERS OF THIS 
 *           FUNCTION
 *
 * Returns:
 * - 0 upon success, success string as an out parameter
 * - WRONG_KIND if the action type has the wrong kind, failure string as an out
 *   parameter
 * - NOT_ALLOWED_DIRECT if the action can't be done on the NPC, failure string
 *   as an out parameter
 */
int do_npc_action(chiventure_ctx_t *c, npc_action_t *a, npc_t *npc,
                  char **ret_string);

/* A function that executes KIND 5 actions (ACTION <npc> <item>)
 *
 * Parameters:
 * - c: A context struct encapsulating the shared state in chiventure
 * - a: An NPC action type struct
 * - npc: An npc struct
 * - i: An item struct
 * - ret_string: A pointer to a string describing the result of the function
 *   - NOTE: THIS STRING IS MALLOCED AND MUST BE FREED BY USERS OF THIS
 *           FUNCTION
 *
 * Returns:
 * - 0 upon success, success string as an out parameter
 * - WRONG_KIND if the action type has the wrong kind, failure string as an out
 *   parameter
 * - NOT_ALLOWED_DIRECT if the action can't be done on the NPC, failure string
 *   as an out parameter
 * - 6 if conditions for the action haven't been met, failure string as an out
 *   parameter
 * - 7 if an effect for the action wasn't applied, failure string as an out
 *   parameter  
 */
int do_npc_item_action(chiventure_ctx_t *c, npc_action_t *a, npc_t *npc,
                       item_t *i, char **ret_string);

/* 
 * A function that executes KIND 6 actions (ACTION <npc> <item> <item>)
 * 
 * Parameters:
 *  - c: A context struct encapsulating the shared state in chiventure
 *  - a: An NPC action type struct
 *  - npc: An npc struct
 *  - direct: An item struct containing the direct object (the "actor")
 *  - indirect: An item struct containing the indirect object (the "actee")
 *  - ret_string: A pointer to a string describing the result of the function
 *  - NOTE: THIS STRING IS MALLOCED AND MUST BE FREED BY USERS OF THIS FUNCTION
 */
int do_npc_item_item_action(chiventure_ctx_t *c, npc_action_t *a, npc_t *npc,
                            item_t *direct, item_t *indirect,
                            char **ret_string);

#endif
