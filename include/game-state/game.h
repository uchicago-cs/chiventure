#ifndef _GAME_H
#define _GAME_H

#include "game_state_common.h"
#include "player.h"
#include "room.h"
#include "item.h"
#include "quests/quests_state.h"
#include "npc/dialogue.h"
#include "condition.h"
#include "game_action.h"
#include "stats.h"
#include "mode.h"
#include "npc/npc.h"
#include "battle/battle_flow_structs.h"

#define ITER_ALL_ROOMS(game, curr_room) room_t *ITTMP_ROOM;\
HASH_ITER(hh, (game)->all_rooms, (curr_room), ITTMP_ROOM)
#define ITER_ALL_PLAYERS(game, curr_player) player_t *ITTMP_PLAYER; \
HASH_ITER(hh, (game)->all_players, (curr_player), ITTMP_PLAYER)

// Forward declaration
typedef struct game_mode game_mode_t;
typedef struct stats_global stats_global_t;
typedef struct stats_global stats_global_hash_t;
typedef struct effects_global effects_global_t;
typedef struct effects_global effects_global_hash_t;
typedef struct room room_hash_t;
typedef struct room_wrapped_for_llist room_list_t;
typedef struct npc npc_t;
typedef struct npc npc_hash_t;
typedef struct quest quest_t;
typedef struct quest quest_hash_t;
typedef struct path path_t;
typedef struct gencontext gencontext_t;
typedef struct levelspec levelspec_t;

/* The game struct is built to contain all the relevant information
 * for anyone who needs to work the game
 */

typedef struct game {
    /* an iteratable hashtable of players */
    /* using the macros provided in uthash.h */
    /* the expected size is 1 for single player games but this can change */
    player_hash_t *all_players;

    /* an iteratable hashtable of rooms */
    /* using the macros provided in uthash.h */
    room_hash_t *all_rooms;

    /* an iteratable hashtable of items */
    /* using the macros provided in uthash.h */
    item_hash_t *all_items;

    /* an iterable hashtable of quests */
    /* using the macros provided in uthash.h */
    quest_hash_t *all_quests;
 
    /* an interatable hashtable of npcs */
    /* using the macros provided in uthash.h */
    npc_hash_t *all_npcs;

    /* pointer to current room struct */
    room_t *curr_room;

    /* pointer to room that, when entered, ends the game */
    room_t *final_room;
    
    /* list of end conditions that, when all are met, ends the game */
    condition_list_t *end_conditions;

    /* pointer to current player struct */
    player_t *curr_player;

    /* pointer to game's mode struct */
    game_mode_t *mode;

    /* pointer to global stats hashtable*/
    stats_global_hash_t *curr_stats;
    
    /* an iteratable hashtable of effects */
    effects_global_hash_t *all_effects;

    /* pointer to all classes in the game */
    class_hash_t *all_classes;

    /* starting string description to be presented at beginning of game */
    char *start_desc;

    /* pointer to gencontext struct used for autogeneration module */
    gencontext_t *genctx;

    /* pointer to levelspec struct used for level-oriented generation */
    levelspec_t *levelspec;

    /* time when game started */
    //int time_start;

    /* pointer to the current battle context */
    battle_ctx_t *battle_ctx;
} game_t;


/* Malloc space for a new game struct
 * This only takes in the beginning string description and
 * creates a new game without rooms and players
 *
 * Parameters:
 *  string description
 *
 * Returns:
 *  pointer to a new game struct
 */
game_t *game_new(char *start_desc);

/* Given the pointer to another room, changes the current room in game-state
 * This function does NOT check if the move is legal
 *
 * Parameters:
 *  pointer to a game struct
 *  pointer to room that we're changing to
 *
 * Returns:
 *  SUCCESS for success
 *  FAILURE for failure
 *  GAME_NULL if game null
 *  ROOM_NULL if new_room is null
 *  FINAL_ROOM if new_room is the final_room
 */
int move_room(game_t *game, room_t *new_room);

/* Exits game safely (frees all memory)
 * Future easter egg :) :) :)
 * pls dont hate
 *
 * Parameters:
 *  pointer to game struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int game_quit(game_t *game);

/* Frees everything in the game struct safely
 *
 * Parameters:
 *  pointer to game struct that needs to be freed
 *
 * Returns:
 *  SUCCESS if successful
 */
int game_free(game_t *game);

/* Adds a player to the given game
 *
 * Parameters:
 *  pointer to game struct
 *  pointer to player struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_player_to_game(game_t *game, player_t *player);

/* Adds a room to the given game
 *
 * Parameters:
 *  pointer to game struct
 *  pointer to room struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_room_to_game(game_t *game, room_t *room);

/* Adds an item to the given game
 *
 * Parameters:
 *  pointer to game struct
 *  pointer to item struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_item_to_game(game_t *game, item_t *item);

/* Adds an npc to the given game
 *
 * Parameters:
 *  pointer to game struct
 *  pointer to npc struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_npc_to_game(game_t *game, npc_t *npc);

/* Adds the final room to the given game
 *
 * Parameters:
 *  game struct
 *  final room struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_final_room_to_game(game_t *game, room_t *final_room);

/* Gets a quest from the all_quests hash table
 *
 * Parameters:
 *  game struct
 *  quest id
 *
 * Returns:
 *  quest struct if successful, NULL if quest is not found
 */
quest_t *get_quest(game_t* game, char *quest_id);

/* Adds a quest to the given game
 *
 * Parameters:
 *  pointer to game struct
 *  pointer to quest struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_quest_to_game(game_t *game, quest_t *quest);

/* Adds an end condition to the given game
 * 
 * Parameters:
 *  game struct
 *  end condition struct
 * 
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 */ 
int add_end_condition_to_game(game_t *game, condition_t *end_condition);

/* Adds a global stat to the given game
 * 
 * Parameters:
 *  pointer to game struct
 *  pointer to global stat struct
 * 
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 */ 
int add_stat_to_game(game_t *game, stats_global_t *gs);

/* Adds a global effect to the given game
 * 
 * Parameters:
 *  game struct
 *  global effect struct
 * 
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 */ 
int add_effect_to_game(game_t *game, effects_global_t *effect);

/* Adds a battle context to the given game
 * 
 * Parameters:
 *  game struct
 *  battle context struct
 * 
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 */ 
int add_battle_ctx_to_game(game_t *game, battle_ctx_t *battle_ctx);

/* Checks if all end conditions in a given game have been met
 * 
 * Parameters:
 *  game struct
 * 
 * Returns: 
 *  true if all end conditions have attributes with expected values
 *  false either if the attribute of at least one end condition is not expected value
 *  or if no end conditions exist
 */ 
bool end_conditions_met(game_t *game);

/* Checks if a chiventure game is over
 * 
 * Parameters:
 *   game struct
 * 
 * Returns:
 *   true if one of the following cases is true:
 *    1. a final room is entered and all end conditions are met
 *    2. no end conditions exist, but a final room is entered
 *    3. no final room exists, but all end conditions are met
 *   false under all other cases
 */
bool is_game_over(game_t *game);

/*
* Function to connect two rooms
* Parameters:
*  pointer to a game
*  source room_id (a string, i.e. char*)
*  destination room_id (a string, i.e. char*)
*  string direction
*  list of conditions
*
* Returns:
*  SUCCESS upon success, FAILURE upon add_path failure
*  ROOM_SRC_NULL if src room_id not found,
*  ROOM_DEST_NULL if dest not found
*
* WARNING: CREATES PATH BUT DOES NOT FILL PATH CONDITIONS
* AT THE MOMENT AS PARAMETERS NOT GIVEN
*/
int create_connection(game_t *game, char *src_room, char *dest_room,
    			char *direction);

/*
*
* Set current player in game
*
* Parameters:
*  pointer to game
*  pointer to player to add
*
* Returns:
*  SUCCESS if the game->curr_player != NULL, FAILURE if NULL
*/
int set_curr_player(game_t *game, player_t *player);

/*
* Function to find player given game and player id
* Parameters:
*  pointer to game
*  player id (a string, i.e. char*)
*
* Returns
*  pointer to player struct or NULL if not found
*/
player_t *get_player(game_t *game, char *player_id);

/*
* Function to find room from all_rooms
* Parameters:
*  pointer to game
*  room id (a string, i.e. char*)
*
* Returns:
*  pointer to room or NULL if not found
*/
room_t *find_room_from_game(game_t *game, char* room_id);

/*
 * Function to get item from all_items
 * Parameters:
 *  pointer to game
 *  item id (a string, i.e. char*)
 *
 * Returns:
 *  pointer to item or NULL if not found
 */
item_t *get_item_from_game(game_t *game, char *item_id);

/*
* Function to find npc from all_npcs
* Parameters:
*  pointer to game
*  npc id (a string, i.e. char*)
*
* Returns
*  pointer to npc or NULL if not found
*/
npc_t *get_npc(game_t *game, char *npc_id);

/*
 * Function to get a linked list (utlist) of all the rooms in the game
 *
 * Parameters:
 *  pointer to game
 *
 * Returns:
 *  linked list of pointers to rooms (the head element)
 */
room_list_t *get_all_rooms(game_t *game);

/*
 * Function to delete a linked list (utlist) retrieved from get_all_rooms()
 *
 * Parameters:
 *  linked list of pointers to rooms
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_room_llist(room_list_t *head);

/*
 * Function to get a linked list (utlist) of all the items in the game
 * THIS WORKS ONLY IF THERE ARE NO SHARED ITEMS
 *
 * Parameters:
 *  pointer to game
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_game(game_t *game);

/* Adds an item to the given player
 *
 * Parameters:
 *  player struct
 *  item struct
 *  game struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_item_to_player(player_t *player, item_t *item, game_t *game);

/* add_effect creates a game_action_effect_t struct and adds it to the action pointed to
* Parameters:
* - game_t *game
* - char* action
* - char* item_src (item_id of item with action)
* - char* item_modify (item_id of item to modify)
* - char* attribute_name
* - attribute_value_t of value to be set
*
* Returns:
* - SUCCESS upon success
* - FAILURE if add_action_effect fails
* - ITEM_SRC_NULL if item src is null
* - ITEM_MODIFY_NULL if item to modify is null
* - ACTION_NULL if action is null
* - ATTRIBUTE_NULL if attribute is null
*/
int add_effect(game_t *game, char *action_name, char *item_src_name,
           char *item_modify_name, char *attribute_name, attribute_value_t *new_value);

/* add_condition adds the given condition struct to the action pointed to
 * Parameters:
 * - game_t *game
 * - game_action_t *action
 * - the condition to add to the action
 *
 * Returns:
 * - SUCCESS upon success
 * - FAILURE if add_action_condition fails
 * - ITEM_MODIFY_NULL if item is null
 * - ACTION_NULL if action is null
 * - ATTRIBUTE_NULL if attribute is null
 * - PLAYER_NULL if player is null
 * - CONDITION_NULL if condition is null
 */
int add_condition(game_t *game, game_action_t *action, condition_t *condition);

/**********************************************
 *       DIALOGUE EXECUTION FUNCTIONS         *
 **********************************************/

/* Starts a conversation.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - rc: return code
 *  - game: the Chiventure game being run
 *
 * Returns:
 *  - A string of NPC dialogue and dialogue options that can be directly
 *    printed by the CLI.
 *  - An RC of: 1 if the conversation has ended (i.e. we have arrived at a
 *    leaf node), 0 if the conversation is still ongoing, and -1 if an error
 *    occured.
 */
char *start_conversation(convo_t *c, int *rc, game_t *game);

/* Runs a step of the conversation.
 *
 * Parameters:
 *  - c: pointer to a convo
 *  - input: integer (1, 2, ..., c->cur_node->num_available_edges)
 *  - rc: return code
 *  - game: the Chiventure game being run
 *
 * Returns:
 *  - A string of NPC dialogue and dialogue options that can be directly
 *    printed by the CLI.
 *  - An RC of: 1 if the conversation has ended (i.e. we have arrived at a
 *    leaf node), 0 if the conversation is still ongoing, and -1 if an error
 *    occured.
 */
char *run_conversation_step(convo_t *c, int input, int *rc, game_t *game);

#endif