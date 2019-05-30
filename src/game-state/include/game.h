#ifndef _GAME_H
#define _GAME_H

#include "game_state_common.h"
#include "player.h"
#include "room.h"
#include "item.h"

/* The game struct is built to contain all the relevant information
 * for anyone who needs to work the game
 */

typedef struct game {
    /* an iteratable hashtable of players */
    /* using the macros provided in uthash.h */
    /* the expected size is 1 for single player games but this can change */
    player_hash_t all_players;

    /* an iteratable hashtable of rooms */
    /* using the macros provided in uthash.h */
    room_hash_t all_rooms;

    /* pointer to current room struct */
    room_t *curr_room;

    /* pointer to current player struct */
    player_t *curr_player;

    /* time when game started */
    //int time_start;
} game_t;


/* Malloc space for a new game struct
 * This does not take any arguments and creates a new game without rooms and players
 *
 * Parameters:
 *  none
 *
 * Returns:
 *  a new game struct
 */
game_t *game_new();

/* Given the pointer to another room, changes the current room in game-state
 * This function does NOT check if the move is legal
 *
 * Parameters:
 *  game struct
 *  room that we're changing to
 *
 * Returns:
 *  none
 */
void move_room(game_t *game, room_t *new_room);

/* Exits game safely (frees all memory)
 * Future easter egg :) :) :)
 * pls dont hate
 *
 * Parameters:
 *  game struct
 *
 * Returns:
 *  none
 */
void game_quit(game_t *game);

/* Frees everything in the game struct safely
 *
 * Parameters:
 *  game struct that needs to be freed
 *
 * Returns:
 *  SUCCESS if successful
 */
int game_free(game_t *game);

/* Adds a player to the given game
 *
 * Parameters:
 *  game struct
 *  player struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_player_to_game(game_t *game, player_t *player);

/* Adds a room to the given game
 *
 * Parameters:
 *  game struct
 *  room struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_room_to_game(game_t *game, room_t *room);


/*
*
* Set current player in game
*
* Parameters:
* game, player
*
* Returns:
*  SUCCESS if the game->curr_player != NULL, FAILURE if NULL
*/
int set_curr_player(game_t *game, player_t *player);


/*
* Function to find player given game and player id
* Parameters:
* Game, player id
*
* Returns
* player struct
*/
player_t *get_player(game_t *game, char *player_id);

/*
 * Function to get a linked list (utlist) of all the rooms in the game
 *
 * Parameters:
 *  game
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
 *  game
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_game(game_t *game);

#endif
