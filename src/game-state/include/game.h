#ifndef _GAME_H
#define _GAME_H

#include "game_state_common.h"
#include "player.h"
#include "room.h"
#include "item.h"

#define ITER_ALL_ROOMS(game, curr_room) room_t *ITTMP_ROOM;\
HASH_ITER(hh, (game)->all_rooms, (curr_room), ITTMP_ROOM)
#define ITER_ALL_PLAYERS(game, curr_player) player_t *ITTMP_PLAYER; HASH_ITER(hh, (game)->all_players, (curr_player), ITTMP_PLAYER)

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

    /* starting string description to be presented at beginning of game */
    char *start_desc;

    /* time when game started */
    //int time_start;
} game_t;


/* Malloc space for a new game struct
 * This only takes in the beginning string description and
 * creates a new game without rooms and players
 *
 * Parameters:
 *  string description
 *
 * Returns:
 *  a new game struct
 */
game_t *game_new(char *start_desc);

/* Given the pointer to another room, changes the current room in game-state
 * This function does NOT check if the move is legal
 *
 * Parameters:
 *  game struct
 *  room that we're changing to
 *
 * Returns:
 *  0 for success
 *  1 for failure
 */
int move_room(game_t *game, room_t *new_room);

/* Exits game safely (frees all memory)
 * Future easter egg :) :) :)
 * pls dont hate
 *
 * Parameters:
 *  game struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
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
* Function to connect two rooms
* Parameters:
* game, Source room_id, destination room_id, direction
*
* Returns:
* SUCCESS if all okay, exit(1) if src room_id not found,
* exit(2) if dest not found
*
* WARNING: CREATES PATH BUT DOES NOT FILL PATH CONDITIONS
* AT THE MOMENT AS PARAMETERS NOT GIVEN
*/
int create_connection(game_t *game, char* src_room, char* dest_room,
    char* direction);


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
* player struct or NULL if not found
*/
player_t *get_player(game_t *game, char *player_id);

/*
* Function to find room from all_rooms
* Parameters:
* Game, room_id
*
* Returns:
* pointer to room or NULL if not found
*/
room_t *find_room(game_t *game, char* room_id);

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
int delete_room_llist(room_list_t *list);

#endif
