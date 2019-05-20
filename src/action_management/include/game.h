#ifndef _GAME_H_
#define _GAME_H_


#include "action_structs.h"


/* In the absence of the Game State team's code,
 * here are some theoretical structs containing the minimum of what we need.
 * We use these structs in our implementation of basic action commands.
   =========================================================================== */


/* A NPC struct containing:
 * - dialogue: a line of dialogue NPC will say when spoken to
 */
typedef struct {
    char *dialogue;
} npc_t;


/* An item struct containing:
 * - allowed_actions: an integer array that contains enumerated "actions"
 * - num_allowed_actions: the number of elements in the allowed_actions array
 * - change: the effect an item has on a player's health
 * - status_change: a string notifying the player of the status change
 */
typedef struct {
    int *allowed_actions;
    int num_allowed_actions;
    int change;
    char *status_change;
} item_t;


// forward declaration of inventory struct
typedef struct inventory_struct inventory_t;


// forward declaration of a path struct
typedef struct path_struct path_t;


/* A player struct containing:
 * - inventory: a pointer to an inventory struct containing all inventory items
 * - max_health: an int representing the maximum health a player can have
 */
typedef struct {
    inventory_t *inventory;
    int max_health;
} player_t;


/* A game struct containing:
 * - current_player: a pointer to the player struct containing the current player
 */
typedef struct {
    player_t *current_player;
} game_t;


/* In the absence of the Game State team's code,
 * here are some functions we assume are available for our implementation.
 * We use these structs in our implementation of basic action commands.
   =========================================================================== */


/* changes item conditon from on to off, open to closed, etc. and vice versa
 * returns SUCCESS = 0 or FAILURE = 1 */
int toggle_condition(game_t *g, action_type_t *a, item_t *i);


/* prints item description to stderr (already included by game state)
 * returns SUCCESS = 0 or FAILURE = 1 */
int get_long_desc(item_t *i);


/* removes an item from a player's inventory
 * returns SUCCESS = 0 or FAILURE = 1 */
int remove_inventory_item(player_t *play, item_t *i);


/* checks if an item can be taken (already included by game state)
 * returns SUCCESS = 0 or FAILURE = 1 */
int take_object(item_t *i);


/* adds an item to a player's inventory
 * returns SUCCESS = 0 or FAILURE = 1 */
int add_inventory_item(player_t *play, item_t *i);


/* changes a player's health (already included by game state)
 * returns SUCCESS = 0 or FAILURE = 1 */
int change_health(player_t *play, int change, int max_health);


/* moves a player through the game based on a given path
 * returns SUCCESS = 0 or FAILURE = 1 */
int player_move(game_t *g, path_t *p);


/* determines if an npc can be found in the room
 * returns SUCCESS = 0 or FAILURE = 1 */
int found_in_room(game_t *g, npc_t *n);


/* prints a conversation with npc to stderr
 * returns SUCCESS = 0 or FAILURE = 1 */
int npc_talk(player_t *play, npc_t *n);


#endif
