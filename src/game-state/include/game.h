#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include "player.h"
#include "object.h"
#include "room.h"

/* The game struct is built to contain all the relevant information
for anyone who needs to work the game
*/

// // This detailed implementation of this struct is in the small modules.
// // Once small_modules.h is finished, we will change the implementation to the following:
// // typedef **name_used_in_small_modules.h** room_t;
// typedef struct room {
//     int id;
//     UT_hash_handle hh;
//     // room;
// } room_t;

typedef room_t* all_rooms_t;

// typedef struct player {
//     int id;
//     UT_hash_handle hh;
//     //holds levels
//     //health
//     //inventory
//     //experience
//     //objectives : 1 or 0 if complete
// } player_t;

typedef player_t* all_players_t;

typedef struct game {
    // list of players, the expected value is 1 but this can change
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

//loads game. If given file is empty start new game, else load
game_t *init_game(FILE *f);

//saves game, bool if success
//(SHOULD be able to select new save location - depends on CLI)
int save_game(game_t *game, FILE *f);

//given a new room, changes the current room in game-state
//this should only check if the room is in the list of adjacent rooms
//expecting a legal move
void move_room(game_t *game, room_t *new_room);

//exit game
//echo "ctrl-g"
//troll post pls dont hate
void exit_game(game_t *game);

//free game
//assuming fxnalities being x-built
void free_game(game_t *game);





#endif

