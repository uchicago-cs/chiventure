#include <stdlib.h>
#include "game.h"

/* see game.h */

//loads game. If given file is empty start new game, else load
game_t *init_game(FILE *f) {
    game_t *game = malloc(sizeof(game_t));
    game->all_players = NULL; //helper fxn to get list of players
    game->all_rooms = NULL;


    /* read from the file using interface from WDL team */


    return game;
}

//saves game, bool if success
//(SHOULD be able to select new save location - depends on CLI)
int save_game(game_t *game, FILE *f) {
    int check = 0;

    //helpers to take game states and save them


    return check;
}

//given a new room, changes the current room in game-state
//this should only check if the room is in the list of adjacent rooms
//expecting a legal move
void move_room(game_t *game, room_t *new_room) {
    if(game != NULL && new_room != NULL) {
        game->curr_room = new_room;
    }
}

//exit game
//echo "ctrl-g"
//troll post pls dont
void exit_game(game_t *game) {
    if (game != NULL) free_game(game);
    exit(0);
    //printf("THIS SHOULD NOT BE EXECUTED");
}

//helper function that deletes all the rooms using macros provided in uthash.h
void delete_all_rooms(all_rooms_t rooms) {
    room_t *current_room, *tmp;
    HASH_ITER(hh, rooms, current_room, tmp) {
        HASH_DEL(rooms, current_room);  /* delete it (rooms advances to next) */
// ** SHOULD CHANGE THIS TO FUNCTIONS IN SMALL MODULES **
        free(current_room);             /* free it */
    }
}

//helper function that deletes all the players using macros provided in uthash.h
void delete_all_players(all_players_t players) {
    player_t *current_player, *tmp;
    HASH_ITER(hh, players, current_player, tmp) {
        HASH_DEL(players, current_player);  /* delete it (players advances to next) */
// ** SHOULD CHANGE THIS TO FUNCTIONS IN SMALL MODULES **
        free(current_player);             /* free it */
    }
}

void free_game(game_t *game) {
    //assuming we have the given free fxns
    delete_all_rooms(game->all_rooms);
    delete_all_players(game->all_players);
    free(game);
}


