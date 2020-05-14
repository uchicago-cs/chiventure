#include <criterion/criterion.h>
#include <string.h>
#include <ui/ui.h>
#include "game-state/game.h"
#include "common/ctx.h"

chiventure_ctx_t *create_sample_ctx()
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);

    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "north");

    /* Free default game and replace it with ours */
    game_free(ctx->game);
    ctx->game = game;

    return ctx;
}

int test_callback(chiventure_ctx_t *ctx, char *outstr, void* args)
{
    char *expected = (char*) args;

    cr_assert_str_eq(outstr, expected);

    return CLI_CMD_SUCCESS;
}

/* Creates a sample game and runs the LOOK command */
Test(game, look)
{
    int quit;
    chiventure_ctx_t *ctx = create_sample_ctx();

    char *cmd_str = strdup("LOOK");
    cmd *cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");

    do_cmd(cmd, test_callback, "Verily, this is the first room.", ctx);

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}
