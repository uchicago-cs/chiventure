#include "game.h"


/* see game.h */ 

//loads game. If given file is empty start new game, else load
game_t *init_game(FILE *f) {

game_t *game = malloc(sizeof(game_t));
    game->players = NULL; //helper fxn to get list of players
    game->Rooms = NULL; 
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
    if(game->Rooms->curr != NULL) {
    game->Rooms->curr = new_room;
    }
}

//exit game
//echo "ctrl-g"
//troll post pls dont 
void exit_game(game_t *game) {
   printf("THIS IS NOT A TROLL");
}

void free_game(game_t *game) {
    //assuming we have the given free fxns
    free_player(game->players);
    while(game->Rooms->curr != NULL) {
        free_room(game->Rooms->curr);
        game->Rooms->curr = game->Rooms->list->curr; 
    }
    free(game);
}


//helper function to find all rooms

