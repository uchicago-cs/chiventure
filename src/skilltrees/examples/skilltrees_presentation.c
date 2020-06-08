#include <stdio.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "cli/operations.h"

const char* banner =
    "    ________________________________________________________________________________________\n"
    "  / \\                                                                                       \\\n"
    " |   |                                                                                      |\n"
    "  \\_ |     ███████╗██╗  ██╗██╗██╗     ██╗  ████████╗██████╗ ███████╗███████╗███████╗        |\n"
    "     |      ██╔════╝██║ ██╔╝██║██║     ██║  ╚══██╔══╝██╔══██╗██╔════╝██╔════╝██╔════╝       |\n"
    "     |      ███████╗█████╔╝ ██║██║     ██║     ██║   ██████╔╝█████╗  █████╗  ███████╗       |\n"
    "     |      ╚════██║██╔═██╗ ██║██║     ██║     ██║   ██╔══██╗██╔══╝  ██╔══╝  ╚════██║       |\n"
    "     |      ███████║██║  ██╗██║███████╗███████╗██║   ██║  ██║███████╗███████╗███████║       |\n"
    "     |      ╚══════╝╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝       |\n"
    "     |   ___________________________________________________________________________________|___\n"
    "     |  /                                                                                      /\n"
    "     \\_/______________________________________________________________________________________/\n";

chiventure_ctx_t* create_example_ctx() {
    // Create example game
    game_t* game = game_new("Welcome to the skilltrees team's presentation!");

    // Create example rooms
    // room_t* room1 = room_new("room1", "Room 1 short description", "Room 1 long description");
    // room_t* room1 = room_new("room2", "Room 2 short description", "Room 2 long description");

    // Add example rooms to example game
    // add_room_to_game(game, room1);
    // add_room_to_game(game, room2);

    // Set initial room and create connection to second room
    // game->curr_room = room1;
    // create_connection(game, "room1", "room2", "NORTH");

    // Create item in room1

    // Associate action with item in room1

    // Create example chiventure context
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    return ctx;
}

int main(int argc, char **argv) {
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free example game
    game_free(ctx->game);

    return 0;
}
