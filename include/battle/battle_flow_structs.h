#ifndef BATTLE_FLOW_STRUCTS_H
#define BATTLE_FLOW_STRUCTS_H

#include <stdbool.h>
#include <string.h>
#include "battle/battle_common.h"
#include "battle/battle_state.h"
#include "battle/battle_structs.h"
#include "common/common.h"
#include "common/utlist.h"

/* Stub for the player struct in game-state */
typedef struct battle_player {
    // Other fields: hash handle, inventory, other stats
    char *player_id;
    class_t *class_type;
    stat_t *stats;
    move_t *moves;
    battle_item_t *items;
} battle_player_t;

/* Stub for the game_t struct in game-state */
typedef struct battle_game {
    // Would have other fields (eg hash tables for players, rooms, battle_items)
    battle_player_t *player;
    battle_t *battle;
} battle_game_t;

/* A turn component lets the player and system know what a player can do at
 * a certain point of the turn
 */
typedef struct turn_component {
    int move;
    int item;
    int pass;
} turn_component_t;

/* A linked list of turn_components. Is a full turn */
typedef struct turn_component_list {
    turn_component_t current;
    struct turn_component_list *rest;
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
} battle_ctx_t;

/* Stub for the player_new function in player.h game-state module
 *
 * Parameters:
 *     - p_id: player id
 *     - class_type: pointer to player class struct
 *     - stats: player stats stub
 *     - moves: player moves stub
 *     - items: player battle_items stub
 *
 * Returns: a newly allocated battle_player_t with p_id, stats, moves, battle_items
 */
battle_player_t *new_ctx_player(char* p_id, class_t *class, stat_t *stats, move_t *moves, battle_item_t* items);

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
turn_component_list_t *new_turn_component_list(turn_component_t t, turn_component_list_t *r);

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
turn_component_list_t *init_turn_component_list(turn_component_list_t *turn, turn_component_list_t *r, turn_component_t c);

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
