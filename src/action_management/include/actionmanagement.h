#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include <stdio.h>
#include <stdlib.h>


/* An enumeration of all supported actions.
 * TYPE 1 ACTIONS - ACTION <item>
 * TYPE 2 ACTIONS - ACTION <direction>
 * TYPE 3 ACTIONS - ACTION <npc>
 * TYPE 4 ACTIONS - ACTION <item> <npc> */
enum actions {

/* TYPE 1 ACTIONS */
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

/* TYPE 2 ACTIONS */
	GO, 	 // synonyms: "walk" "enter"

/* TYPE 3 ACTIONS */
	TALK_TO,

/* TYPE 4 ACTIONS */
	GIVE_TO,
	USE_ON
};

/* Outlines the three different objects that can be action'd upon */
enum object_type {
	ITEM_OBJ, 	   // e.g. door, potion
	DIRECTION_OBJ, // e.g. north, east
	NPC_OBJ 	   // e.g. Borja, wizard
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
	list_t *parameters; // e.g. ITEM_OBJ -> NPC_OBJ
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
  list_t *synonyms, list_t *parameters);


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
  list_t *synonyms, list_t *parameters);


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


/* A function that returns all supported actions
 * Returns:
 * a linked list of action_t structs */
list_t *get_supported_actions();

// ===========================================================

/* A function that executes TYPE 1 actions (ACTION <item>)
 * Returns 0 on success, 1 on failure. */
int action_type1(game_t *g, action_t *a, item_t *i);


/* A function that executes TYPE 2 actions (ACTION <direction>)
 * Returns 0 on success, 1 on failure. */
int action_type2(game_t *g, action_t *a, direction_t *d);


/* A function that executes TYPE 3 actions (ACTION <npc>)
 * Returns 0 on success, 1 on failure. */
int action_type3(game_t *g, action_t *a, npc_t *n);


/* A function that executes TYPE 4 actions (ACTION <item> <npc>)
 * Returns 0 on success, 1 on failure. */
int action_type4(game_t *g, action_t *a, item_t *i, npc_t *n);

// ===========================================================

/* TYPE 1 ACTIONS */

/* Changes item state to opened
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_open(game_t *g, item_t *i);


/* Changes item state to closed
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_close(game_t *g, item_t *i);


/* Changes item state to pushed
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_push(game_t *g, item_t *i);

/* Changes item state to pulled
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_pull(game_t *g, item_t *i);

/* Prints a description of an item
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_examine(game_t *g, item_t *i);

/* Changes item state to turned on
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_turn_on(game_t *g, item_t *i);

/* Changes item state to turned off
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_turn_off(game_t *g, item_t *i);

/* Picks up an item, removing it from world and adding to inventory
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_take(game_t *g, item_t *i);

/* Drops an item, removing it from inventory
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_drop(game_t *g, item_t *i);

/* Consumes an item, removing it from inventory
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * Output:
 * - 0 if success, 1 if error */
int act_consume(game_t *g, item_t *i);

/* TYPE 2 ACTIONS */

/* Moves the player to the given direction
 * Paramters:
 * - g: the game struct
 * - d: the direction struct
 * Output:
 * - 0 if success, 1 if error */
int act_go(game_t *g, direction_t *d);

/* TYPE 3 ACTIONS */

/* Prints dialogue from an npc
 * Paramters:
 * - g: the game struct
 * - n: the npc struct
 * Output:
 * - 0 if success, 1 if error */
int act_talk_to(game_t *g, npc_t *n);

/* TYPE 4 ACTIONS */

/* Gives item to an npc, removing it from inventory and changing npc state
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * - n: the npc struct
 * Output:
 * - 0 if success, 1 if error */
int act_give_to(game_t *g, item_t *i, npc_t *n);

/* Uses item on npc, removing it from inventory and changing npc state
 * Paramters:
 * - g: the game struct
 * - i: the item struct
 * - n: the npc struct
 * Output:
 * - 0 if success, 1 if error */
int act_use_on(game_t *g, item_t *i, npc_t *n);


#endif
