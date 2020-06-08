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
    room_t* design_room = room_new("Design Room", "", "This is the design room."
                                   "Any responsible software project devotes"
                                   "ample time to its design phase.");
    room_t* implementation_room = room_new("Implementation Room", "", "This is"
                                           "the implementation room. Your users"
                                           "eagerly await a demo of your final "
                                           "product, so get to work!");
    room_t* demo_room = room_new("Demo Room", "", "Your demo was a success!");

    // Add example rooms to example game
    add_room_to_game(game, design_room);
    add_room_to_game(game, implementation_room);
    add_room_to_game(game, demo_room);

    // Set initial room and create connection to second room
    game->curr_room = design_room;
    create_connection(game, "design_room", "implementation_room", "NORTH");
    create_connection(game, "implementation_room", "design_room", "SOUTH");
    create_connection(game, "implementation_room", "demo_room", "NORTH");
    create_connection(game, "demo_room", "implementation_room", "SOUTH");

    // Create item in room1

    // Associate action with item in room1

    // Create example chiventure context
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    return ctx;
}

/*char* skill_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    if (tokens[])
}*/

int main(int argc, char **argv) {
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free example game
    game_free(ctx->game);

    return 0;
}
