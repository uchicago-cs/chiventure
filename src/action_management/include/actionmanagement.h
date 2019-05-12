#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include <stdio.h>
#include <stdlib.h>


/* An enumeration of all supported actions.
 * KIND 1 ACTIONS - ACTION <item>
 * KIND 2 ACTIONS - ACTION <direction>
 * KIND 3 ACTIONS - ACTION <npc>
 * KIND 4 ACTIONS - ACTION <item> <npc> 
 * KIND 5 ACTIONS - ACTION <item> <item> 
 */
enum actions {

/* KIND 1 ACTIONS */
	OPEN,
	CLOSE,
	PUSH,
	PULL,
	EXAMINE,
	TURN_ON,
	TURN_OFF,
	TAKE,    // synonyms: "pick up"
	DROP,
	CONSUME, // synonyms: "use" "drink" "eat"

/* KIND 2 ACTIONS */
	GO, 	 // synonyms: "walk"

/* KIND 3 ACTIONS */
	TALK_TO,

/* KIND 4 ACTIONS */
	GIVE_TO,

/* KIND 5 ACTIONS */
    USE_ON
};


/* Each enum corresponds to a different "KIND" of action */
enum action_kind {
    ITEM = 1, // ACTION <item>
    DIRECTION = 2, // ACTION <direction
    NPC = 3, // ACTION <npc>
    ITEM_NPC = 4, // ACTION <item> <npc>
    ITEM_ITEM = 5 // ACTION <item> <item>
};


/* An action struct that contains the following:
 * - act: the encoded enum name for this action
 * - c_name: the 'canonical' string that should call the enum
 * - synonyms: the synonyms that would also be allowed to call action
 * - parameters: an order-sensitive linked list of object_type enums
*/
typedef struct {
	enum actions act;   // e.g. CONSUME
	char *c_name;  // e.g. "eat"
	list_t *synonyms;   // e.g. "drink" -> "use"
	enum action_kind *kind; // e.g. KIND_1
} action_t;


// ===========================================================

/*
 * Allocates a new action on the heap, calling action_init
 *
 * Parameters:
 * - act: an enumeration of the action
 *
 * Returns:
 * - a pointer to a new action struct
 */
action_t *action_new(enum actions act, char *c_name,
                     list_t *synonyms, enum action_kind *kind);


/*
 * A function that initializes an action
 * Will determine the action_type, depending on what action is given
 *
 * Parameters:
 * - a: a pointer to an empty action_t
 * - act: an enumeration of the action
 *
 * Returns:
 * - 0 if success, 1 if an error occurs
 * - an error message in stderr if the action struct is not initialized
 */
int action_init(action_t *a, enum actions act, char *c_name,
                list_t *synonyms, enum action_kind *kind);


/*
 * A function that frees the resources associated with an action struct
 *
 * Parameters:
 * - a: An action struct. Must point to action struct allocated by action_new
 *
 * Returns:
 * - Always returns 0.
 */
int action_free(action_t *a);


// ===========================================================

/* 
 * A function that returns all supported actions
 *
 * Parameters:
 * - kind: The enumerated value of KIND, specifying which action KIND necessary
 * 
 * Returns:
 * - a linked list of action_t structs 
 */
list_t *get_supported_actions(enum action_kind *kind);


/* 
 * A function that returns the canonical name of an action as a string 
 * 
 * Parameters:
 * - a: An action struct
 * 
 * Returns:
 * - the canonical name of the action as a string
*/
char *get_action_cname(action_t *a);


/* 
 * A function that returns the synonyms of an action as a list of enums 
 * 
 * Parameters:
 * - a: An action struct
 * 
 * Returns:
 * - a list of the synonyms of the action
*/
list_t *get_action_synonyms(action_t *a);


/* A function that returns the KIND of an action as an integer 
 * 
 * Parameters:
 * - a: An action struct
 * 
 * Returns: 
 * - 1 for KIND 1
 * - 2 for KIND 2
 * - 3 for KIND 3
 * - 4 for KIND 4
 * - 5 for KIND 5
 */
int *get_action_kind(action_t *a);


// ===========================================================

/* A function that executes KIND 1 actions (ACTION <item>)
 * 
 * Parameters:
 * - g: A game struct consisting of the game state
 * - a: An action struct
 * - i: An item struct
 * 
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int action_item(game_t *g, action_t *a, item_t *i);


/* A function that executes KIND 2 actions (ACTION <direction>)
 * 
 * Parameters:
 * - g: A game struct consisting of the game state
 * - a: An action struct
 * - d: A direction struct
 * 
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int action_direction(game_t *g, action_t *a, direction_t *d);


/* A function that executes KIND 3 actions (ACTION <npc>)
 * 
 * Parameters:
 * - g: A game struct consisting of the game state
 * - a: An action struct
 * - n: An npc struct
 * 
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int action_npc(game_t *g, action_t *a, npc_t *n);


/* A function that executes KIND 4 actions (ACTION <item> <npc>)
 * 
 * Parameters:
 * - g: A game struct consisting of the game state
 * - a: An action struct
 * - i: An item struct
 * - n: An npc struct
 * 
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int action_item_npc(game_t *g, action_t *a, item_t *i, npc_t *n);


/* A function that executes KIND 5 actions (ACTION <item> <item>)
 * 
 * Parameters:
 * - g: A game struct consisting of the game state
 * - a: An action struct
 * - direct: An item struct containing the direct object (the "actor")
 * - indirect: An item struct containing the indirect object (the "actee")
 * 
 * Returns
 * - 0 on success
 * - 1 on failure
 */
int action_item_item(game_t *g, action_t *a, item_t *direct, item_t *indirect);



#endif
