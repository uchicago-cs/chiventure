#ifndef BATTLE_FLOW_STRUCTS_H
#define BATTLE_FLOW_STRUCTS_H

#include <stdbool.h>
#include <string.h>
#include "battle/battle_common.h"
#include "battle/battle_state.h"
#include "battle/battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"
#include "common/utlist.h"
#include "playerclass/class.h"

/* Stub for the player struct in game-state */
typedef struct battle_player {
    // Other fields: hash handle, inventory, other stats
    char *player_id; // the user's ID
    class_t *class_type; // the class of the user
    stat_t *stats; // the stats the user has
    move_t *moves; // the moves the user had
    battle_item_t *items; // the items the user holds
    battle_equipment_t *weapon;  // the weapon the user holds
    battle_equipment_t *accessory; // the accessory the user holds
    battle_equipment_t *armor; // the armor the user holds
} battle_player_t;

/* Stub for the game_t struct in game-state */
typedef struct battle_game {
    // Would have other fields (eg hash tables for players, rooms, battle_items)
    battle_player_t *player;
    battle_t *battle;
} battle_game_t;

/* A turn component lets the player and system know what a player can do at
 * a certain point of the turn
 * If the int is 1, then the player can use that action at the turn component
 * Ex: if the move and item ints are 1, then the player can choose to either 
 * use a move or consume an item.
 */
typedef struct turn_component {
    int move;
    int item;
    int pass;
} turn_component_t;

/* A linked list of turn_components. Is a full turn */
typedef struct turn_component_list {
    turn_component_t *current;
    struct turn_component_list *next;
} turn_component_list_t;

/* Stub, similar to chiventure_ctx_t except adding status, which
 * is an enum that gives the current status of the battle_game 
 * (see logic.h for details)
 */
typedef struct battle_ctx {
    // would have UI context here
    battle_game_t *game;
    // would have lookup table here
    battle_status_t status;
    // turn component list that the game designer creates
    turn_component_list_t *tcl;
} battle_ctx_t;

/* Allocates a new battle ctx in the heap
 *
 * Parameters:
 *     - game: the battle game
 *     - status: status of the battle
 *     - tcl: turn component list that makes up a turn
 *
 * Returns: a newly allocated battle_ctx_t with game, status, tcl
 * or NULL if it cannot be allocated
 */
battle_ctx_t *new_battle_ctx(battle_game_t *game, battle_status_t status, 
                            turn_component_list_t *tcl);

/* Initializes a battle ctx struct
 *
 * Parameters:
 *     - ctx: the battle ctx, should already be allocated in heap
 *     - game: the battle game
 *     - status: status of the battle
 *     - tcl: turn component list that makes up a turn
 *
 * Returns: 0 on success, 1 if an error occurs
 */
int battle_ctx_init(battle_ctx_t *ctx, battle_game_t *game, battle_status_t status,
                    turn_component_list_t *tcl);

/*
 * Frees the resources associated with a battle ctx
 *
 * Parameters:
 *  - ctx: A battle ctx. Must point to already allocated memory.
 *
 * Returns:
 *  - Always returns 0.
 */
int battle_ctx_free(battle_ctx_t *ctx);

/*
 * Frees the resources associated with a battle game
 *
 * Parameters:
 *  - game: A battle game. Must point to already allocated memory.
 *
 * Returns:
 *  - Always returns 0.
 */
int battle_game_free(battle_game_t *game);

/*
 * Frees the resources associated with a battle player
 *
 * Parameters:
 *  - player: A battle player. Must point to already allocated memory.
 *
 * Returns:
 *  - Always returns 0.
 */
int battle_player_free(battle_player_t *player);

/*
 * Frees the resources associated with a battle equipment
 *
 * Parameters:
 *  - equip: A battle equipment. Must point to already allocated memory.
 *
 * Returns:
 *  - Always returns 0.
 */
int battle_equipment_free(battle_equipment_t *equip);

/*
 * Frees the resources associated with a battle item
 *
 * Parameters:
 *  - item: A battle item. Must point to already allocated memory.
 *
 * Returns:
 *  - Always returns 0.
 */
int battle_item_free(battle_item_t *item);

/*
 * Frees the resources associated with a struct change
 *
 * Parameters:
 *  - changes: A stat change struct. Must point to already allocated memory.
 *
 * Returns:
 *  - Always returns 0.
 */
int stat_changes_free(stat_changes_t *changes);

/* Stub for the player_new function in player.h game-state module
 *
 * Parameters:
 *     - p_id: player id
 *     - class_type: pointer to player class struct
 *     - stats: player stats stub
 *     - moves: player moves stub
 *     - items: player battle_items stub
 *     - weapon: the player's equiped weapon
 *     - accessory: the player's equiped accessory
 *     - armor: the player's equiped armor
 *
 * Returns: a newly allocated battle_player_t with p_id, stats, moves, battle_items
 */
battle_player_t *new_ctx_player(char* p_id, class_t *class, stat_t *stats, 
                                move_t *moves, battle_item_t* items,
                                battle_equipment_t *weapon, 
                                battle_equipment_t *accessory, 
                                battle_equipment_t *armor);

/* Stub for the game_new function in game.h game-state module
 *
 * Parameters: None
 *
 * Returns: a newly allocated game_t with no current player
 */
battle_game_t *new_battle_game();

/*
 * Initializes a turn_component
 *
 * Parameters:
 *  - tc: A turn component.
 *  - move: determines whether a move can be used or not. Will be 1 or 0.
 *  - item: determines whether an item can be used or not. Will be 1 or 0.
 *  - pass: determines whether a pass can be used or not. Will be 1 or 0.
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
turn_component_t *init_turn_component(turn_component_t tc, int move, int item, int pass);

/*
 * Allocates a new turn component list in the heap.
 *
 * Parameters:
 *  - t: a turn_component
 *  - r: the rest of the turn components
 *
 * Returns:
 *  - A pointer to the turn, or NULL if a turn
 *    cannot be allocated
 */
turn_component_list_t *new_turn_component_list(turn_component_t *t, turn_component_list_t *r);

/*
 * Initializes the current and next turn components of a turn of a list
 *
 * Parameters:
 *  - turn: A turn. Must point to already allocated memory
 *  - r: the rest of the turn components
 *  - c: the current turn component
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
turn_component_list_t *init_turn_component_list(turn_component_list_t *turn, 
                                                turn_component_list_t *r, 
                                                turn_component_t c);

/*
 * Frees the resources associated with a turn component list
 *
 * Parameters:
 *  - turn: A turn. Must point to already allocated memory.
 *
 * Returns:
 *  - Always returns 0.
 */
int turn_component_list_free(turn_component_list_t *turn);

#endif
