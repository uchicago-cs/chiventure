#include <stdio.h>
#include <../cli/operations.h>
#include "../common/ctx.h"
#include "../ui/ui.h"
#include "../sound/sound.h"

const char *banner = "THIS IS A SOUND EXAMPLE PROGRAM";

// check loaded game
char *check_game(char *tokens[TOKEN_LIST_SIZE], chiventure_ctx_t *ctx)
{
    game_t *game = ctx->game;
    if (game == NULL || game->curr_room == NULL) {
        return "Error\n";
    }
    if (tokens[1] != NULL) {
        return "What?\n";
    }
}

// load audio
// this is where the implementation of adding sound will go

// create sample game
chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");

    load_normal_mode(game);

    // make room
    room_t *room1 = room_new("room1", "Room One","Welcome.");
    add_room_to_game(game, room1);
    game->curr_room = room1;

    ctx->game = game;

    return ctx;
}

int main() {
    chiventure_ctx_t *ctx = create_sample_ctx();

    // sound operations
    // this is where sound will be

    start_ui(ctx, banner);

    game_free(ctx->game);

    return 0;
}