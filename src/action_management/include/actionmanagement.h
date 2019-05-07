#ifndef _ACTIONS_H_
#define _ACTIONS_H_ 

#include <stdio.h>
#include <stdlib.h>


/* An enumeration of all supported actions. */
/* All synonyms will be provided to CLI. */
enum actions {
  OPEN, /* world action */
  CLOSE, /* world action */
  PUSH, /* world action */
  PULL, /* world action */
  EXAMINE, /* synonymous to "look at", is a world action */
  TURN_ON, /* world action */
  TURN_OFF, /* world action */
  TALK_TO, /* NPC action */
  GIVE, /* requires 2 arguments separated by 'to',  NPC action */
  GO, /* world action */
  TAKE, /* synonymous with "pick up", is an inventory action */
  DROP, /* inventory action */
  CONSUME, /* synonymous with "use", "drink", "eat", is an inventory action */
  USE_ON, /* requires two arguments separated by 'on', world and NPC action  */
  MEDLY /* NPC action */
};


/* An enumeration of all possible action types. */
enum action_type {
  ACT_NPC, /* includes "give", "talk to" */
  ACT_WORLD, /* includes "look at", "examine", "open", "close", "push", "pull", 
		"turn on", "turn off", and "go" */
  ACT_INVENTORY /* includes "take", "drop", "consume" */
};
  

/* An action struct that contains the following: 
 * act: A tag corresponding to the action 
 * type: A tag describing the type of action
 * num_arg: the number of actions required for the action to be valid
 * success: a string indicating the action was a success
 * failure: a string indicating the action was a failure
*/
struct action_struct {
  enum actions act;
  enum action_type type;
  int num_arg; 
  char *success;
  char *failure;
};


/* A type declaration of the action struct to action_t. */
typedef struct action_struct action_t;


/* 
 * Allocates a new action on the heap
 * 
 * Parameters:
 * - act: an enumeration of the action
 * - type: an enumeration of the type of action
 * - success: a success string for the action
 * - failure: a failure string for the action
 *
 * Returns: 
 * - a pointer to a new action struct
 */
action_t *action_new(enum actions act, enum action_type type, 
		     char *success, char *failure);


/* 
 * A function that initializes an action
 * Parameters:
 * - a: a pointer to an empty action_t
 * - act: an enumeration of the action
 * - type: an enumeration of the type of action
 * - success: a success string for the action
 * - failure: a failure string for the action
 * 
 * Returns:
 * - 0 if success, 1 if an error occurs
 * - an error message in stderr if the action struct is not initialized
 */
int action_init(action_t *a, enum actions act, enum action_type type,
		char *success, char *failure);


/*
 * A function that frees the resources associated with a piece
 * 
 * Parameters:
 * - a: An action struct. Must point to action struct allocated by action_new
 * 
 * Returns:
 * - Always returns 0.
 */
int action_free(action_t *a);


/*
 * A function that redirects inventory actions to their own action functions
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * - p: a pointer to a player struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 */
int act_inventory(action_struct *a, object_struct *o, 
		   room_struct *r, player_struct *p);


/*
 * A function that redirects npc actions to their own action functions
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - p: a pointer to a player struct given by game state
 * - n: a pointer to an npc struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 */
int act_NPC(action_struct *a, object_struct *o, player_struct *p, npc_struct *n);


/*
 * A function that redirects world actions to their own action functions
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 */
int act_world(action_struct *a, object_struct *o, room_struct *r);


/* each individual function will check for validity before implementation */


/*
 * A function that alters the game state according to an open or close action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_w_open_close(action_struct *a, object_struct *o, room_struct *r);


/*
 * A function that alters the game state according to a push or pull action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_w_push_pull(action_struct *a, object_struct *o, room_struct *r);


/*
 * A function that gives the description associated with a given object
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr describing the object
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_w_examine(action_struct *a, object_struct *o);


/*
 * A function that alters the game state according to a turn on or off action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_w_turn_on_off(action_struct *a, object_struct *o, room_struct *r);


/*
 * A function that gives information provided by a npc
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - n: a pointer to an npc struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - messages to stderr providing information held by the npc
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_n_talk_to(action_struct *a, object_struct *o, npc_struct *n);


/*
 * A function that alters the game state according to a give action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - p: a pointer to a player struct given by game state
 * - n: a pointer to an npc struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_n_give(action_struct *a, object_struct *o, player_struct *p, npc_struct *n);


/*
 * A function that alters the game state according to a go action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct designating a direction given by game state
 * - r: a pointer to a room struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_w_go(action_struct *a, object_struct *o, room_struct *r);


/*
 * A function that alters inventory and the game state according to a take action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * - p: a pointer to a player struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_i_take(action_struct *a, object_struct *o, 
	       room_struct *r, player_struct *p);


/*
 * A function that alters inventory and the game state according to a drop action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * - p: a pointer to a player struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_i_drop(action_struct *a, object_struct *o, 
	       room_struct *r, player_struct *p);


/*
 * A function that alters inventory and the game state according to a consume action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * - p: a pointer to a player struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_i_consume(action_struct *a, object_struct *o, 
		  room_struct *r, player_struct *p);


/*
 * A function that alters inventory and the game state according to a use on action
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - o: a pointer to an object struct given by game state
 * - r: a pointer to a room struct given by game state
 * - p: a pointer to a player struct given by game state
 * 
 * Returns: 
 * - 0 if success, 1 if failure
 * - a message to stderr indicating whether the action was a success or failure
 */ 
int act_i_use_on(action_struct *a, object_struct *o, 
		 room_struct *r, player_struct *p);


/*
 * An easter egg function that gives the player an instant win
 * Consists of our Initials: M(elinda)E(lly)D(ante)L(ucy)Y(oon)
 * 
 * Parameters:
 * - a: a pointer to an action struct allocated by action_new
 * - p: a pointer to a player struct given by game state
 * 
 * Returns: 
 * - A message to stderr indicating a successful end to the game
 */ 
int act_n_medly(action_struct *a, player_struct *p);


#endif
