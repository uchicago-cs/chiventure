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
    room_t* design_room = room_new("Design Room", "", "Any responsible software"
                                   " project devotes ample time to its design "
                                   "phase.");
    room_t* implementation_room = room_new("Implementation Room", "", "Your "
                                           "users eagerly await a demo of your "
                                           "final product, so get to work!");
    room_t* demo_room = room_new("Demo Room", "", "Your demo was a success!");

    // Add example rooms to example game
    add_room_to_game(game, design_room);
    add_room_to_game(game, implementation_room);
    add_room_to_game(game, demo_room);

    // Set initial room and create room connections
    game->curr_room = design_room;
    create_connection(game, "Design Room", "Implementation Room", "NORTH");
    create_connection(game, "Implementation Room", "Design Room", "SOUTH");
    create_connection(game, "Implementation Room", "Demo Room", "NORTH");
    create_connection(game, "Demo Room", "Implementation Room", "SOUTH");

    // Create room items


    // Associate action with item in room1

    // Create example chiventure context
    chiventure_ctx_t* ctx = chiventure_ctx_new(game);

    return ctx;
}

char* effect_design(char* args) {
    return "Good progress on your modules! Keep going!";
}

char* design_operation(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t* ctx) {
    skill_t* design_skill = skill_new(0, ACTIVE, "Design Skill", "Your software design skill", 4, 1, &effect_design);
    return skill_execute(design_skill, "");
}

int main(int argc, char **argv) {
    // Create example chiventure context
    chiventure_ctx_t* ctx = create_example_ctx();

    // Create example skills

    // Add DESIGN operation
    add_entry("DESIGN", design_operation, NULL, ctx->table);

    // Start UI for example chiventure context
    start_ui(ctx, banner);

    // Free example game
    game_free(ctx->game);

    return 0;
}
