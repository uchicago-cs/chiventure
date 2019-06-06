#include "sample_game.h"

/* See sample_game.h */
game_t* create_sample_game()
{
    game_t *game = game_new("Welcome to sample game 1.0!\n");

    /* initialize sample rooms */
    room_t *room1 = room_new("room1", "A room", "room 1 used for the sample game");
    room_t *room2 = room_new("room2", "A room", "room 2 used for the sample game");
    create_connection(game, "room1", "room2", "right");
    create_connection(game, "room2", "room1", "left");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;

    /* initialize player */
    player_t player1 = player_new("player1", 10);
    add_player_to_game(game, player1);
    game->curr_player = player1;

    /* initialize items */
    item_t *item_orb = item_new("orb", "magical orb", "an orb that can be held, placed, or tossed");
    item_t *item_table = item_new("table", "a regular table", "this table can have things placed on it");

    /* add items to room */
    add_item_to_room(room1, item_orb);
    add_item_to_room(room2, item_table);

    return game;
}
