#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utlist.h"
#include "uthash.h"
#include "player.h"
#include "room.h"

/* The game struct is built to contain all the relevant information
 * for anyone who needs to work the game
 */

typedef struct game {
    /* list of players */
    /* the expected size is 1 for single player games but this can change */
    all_players_t all_players;

    //rooms: rooms should be a graph struct w/ directed edges
    //assuming rooms form a network/graphs we can just store the current room
    //store graph of rooms

    //pointer to all rooms struct (current room + list of all rooms)
    //use the hashtable macro provided by uthash.h
    all_rooms_t all_rooms;

    //pointer to current room struct
    room_t *curr_room;

    //TIME STARTED
    int time_start;
} game_t;


/* Loads game from given file.
 * If given file is empty, start a new game, else load the saved game
 */
game_t *init_game(FILE *f);

/* Saves game to file
 * Parameters: *game struct, file location
 * (SHOULD be able to select new save location - depends on CLI)
 * Returns: boolean if save was success
 */
int save_game(game_t *game, FILE *f);

/* Given a new room, changes the current room in game-state
 * Parameters: *game struct, *room that we're changing to
 * This should only check if the room is in the list of adjacent rooms
 * and is expecting a legal move
 * Returns: void
 */
void move_room(game_t *game, room_t *new_room);

/* Exit game
 * Parameters: *game struct
 * Frees game and checks if freed
 * Future easter egg :) :) :)
 * pls dont hate
 * Returns: void
 */
void exit_game(game_t *game);

/* Frees game struct
 * Parameters: *game struct
 * Returns: Void
 */
void free_game(game_t *game);





#endif

