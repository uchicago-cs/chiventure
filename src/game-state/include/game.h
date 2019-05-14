#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utlist.h"
#include "uthash.h"
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
    room_t *curr_player;

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
void move_to_room(game_t *game, room_t *new_room);

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
 *  1 if successful, 0 if failed
 */
int game_free(game_t *game);





#endif
