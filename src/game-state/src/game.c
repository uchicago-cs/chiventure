#include "game.h"

/* see game.h */
game_t *init_game(FILE *f) {
    game_t *game = malloc(sizeof(game_t));
    game->all_players = NULL; //helper fxn to get list of players
    game->all_rooms = NULL;


    /* read from the file using interface from WDL team */


    return game;
}

/* See game.h */
int save_game(game_t *game, FILE *f) {
    int check = 0;

    //helpers to take game states and save them


    return check;
}

/* See game.h */
void move_room(game_t *game, room_t *new_room) {
    if(game != NULL && new_room != NULL) {
        game->curr_room = new_room;
    }
}

/* See game.h */
void exit_game(game_t *game) {
    if (game != NULL) free_game(game);
    exit(0);
    //printf("THIS SHOULD NOT BE EXECUTED");
}

void free_game(game_t *game) {
    //assuming we have the given free fxns
    delete_all_rooms(game->all_rooms);
    delete_all_players(game->all_players);
    free(game);
}


