#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_management/actionmanagement.h"
#include "ui/gui.h"
#include "raylib.h"
#include "game-state/game.h"
#include "game-state/room.h"



chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    room_t *room3 = room_new("room3", "This is room 3", "Wow, this is the final room.");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);

    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");
    create_connection(game, "room2", "room3", "EAST");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
} 

int main() {
    chiventure_ctx_t *ctx = create_sample_ctx();

    run_gui(ctx);
}