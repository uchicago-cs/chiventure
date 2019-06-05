#include "sample_game.h"

/* See sample_game.h */
game_t* create_sample_game()
{
    game_t *game = game_new("Welcome to sample game 1.0!\n");

    room_t *room1 = room_new("room1", "A room", "A room");
    room_t *room2 = room_new("room2", "A room", "A room");
    create_connection(game, "room1", "room2", "right");
    create_connection(game, "room2", "room1", "left");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;

    player_t player1 = player_new("player1", 10);
    add_player_to_game(game, player1);
    game->curr_player = player1;

    return game;
}
