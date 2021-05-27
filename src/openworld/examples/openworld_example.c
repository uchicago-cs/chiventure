/*
 * This example program runs a full instance of chiventure with an in-memory game.
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "openworld/autogenerate.h"


const char *banner = "THIS IS AN OPENWORLD EXAMPLE PROGRAM";


/* Creates a sample in-memory game */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");

    /* Create room1, the initial room */
    room_t *room1 = room_new("room1", "This is room 1", "This is the first room.");
    add_room_to_game(game, room1);
    game->curr_room = room1;
    
    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}


int main(int argc, char **argv)
{
    chiventure_ctx_t *ctx = create_sample_ctx();
    
    /* Start chiventure */
    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}