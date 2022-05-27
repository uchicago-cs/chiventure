#include <criterion/criterion.h>
#include <string.h>
#include <ui/ui.h>
#include "game-state/game.h"
#include "ui/print_functions.h"
#include "common/ctx.h"

/* Creates a chiventure context with a sample game
 *
 * Parameters: None
 *
 * Returns: a chiventure context
 */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}


/* CLI callback that compares the produced output with an expected value
 *
 * Parameters:
 *  - ctx: chiventure context
 *  - outstr: The string printed out by the CLI
 *  - args: The expected string
 *
 * Returns:
 *  - An assertion will fail if outstr is not equal to args.
 *    Otherwise, always returns CLI_CMD_SUCCESS.
 */
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
    cmd **cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");

    do_cmd(cmd[0], test_callback, "Verily, this is the first room.", ctx);

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}


/* Creates a sample game, runs the GO command and verifies that
 * the player moved to a different room */
Test(game, go)
{
    int quit;
    chiventure_ctx_t *ctx = create_sample_ctx();

    room_t *room1 = find_room_from_game(ctx->game, "room1");
    cr_assert_not_null(room1, "Could not fetch room1 from game");
    room_t *room2 = find_room_from_game(ctx->game, "room2");
    cr_assert_not_null(room2, "Could not fetch room2 from game");

    /* Check that the game is in the initial room */
    cr_assert_eq(ctx->game->curr_room, room1);

    char *cmd_str = strdup("GO north");
    cmd **cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");
    do_cmd(cmd[0], NULL, NULL, ctx);

    /* Check that current room has changed */
    cr_assert_eq(ctx->game->curr_room, room2,
                 "GO NORTH did not change the current room as expected");

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}

/* Creates a sample game and runs the LOOK and GO north commands toghether */
Test(game,mult_cmds)
{ 
    chiventure_ctx_t *ctx = create_sample_ctx();

    char *cmd_str = strdup("LOOK AND GO NORTH");
    cmd **cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");

    do_cmd(cmd[0], test_callback, "Verily, this is the first room.", ctx);
    do_cmd(cmd[1], test_callback, "Moved into room2. Truly, this is the second room.", ctx);

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}

/* Creates a sample game and runs the LOOK and command */
Test(game,cmd_with_end_and)
{ 
    int quit;
    chiventure_ctx_t *ctx = create_sample_ctx();

    char *cmd_str = strdup("LOOK AND");
    cmd **cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");

    do_cmd(cmd[0], test_callback, "Verily, this is the first room.", ctx);

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}

/* Creates a sample game and runs the "LOOK" and GO north commands toghether */
Test(game,mult_cmds_start_quotes)
{ 
    int quit;
    chiventure_ctx_t *ctx = create_sample_ctx();

    char *cmd_str = strdup("\"LOOK\" AND GO north");
    cmd **cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");

    do_cmd(cmd[0], test_callback, "Verily, this is the first room.", ctx);
    do_cmd(cmd[1], test_callback, "Moved into room2. Truly, this is the second room.", ctx);

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}

/* Creates a sample game and runs the        LOOK    and    GO     north commands toghether */
Test(game, extra_spaces)
{ 
    int quit;
    chiventure_ctx_t *ctx = create_sample_ctx();

    char *cmd_str = strdup("LOOK    AND    GO          north");
    cmd **cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");

    do_cmd(cmd[0], test_callback, "Verily, this is the first room.", ctx);
    do_cmd(cmd[1], test_callback, "Moved into room2. Truly, this is the second room.", ctx);

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}


/* Creates a sample game and runs the LOOK and LOOK commands toghether */
Test(game, same_cmds)
{ 
    int quit;
    chiventure_ctx_t *ctx = create_sample_ctx();

    char *cmd_str = strdup("LOOK AND LOOK");
    cmd **cmd = cmd_from_string(cmd_str, ctx);
    cr_assert_not_null(cmd, "cmd_from_string failed");

    do_cmd(cmd[0], test_callback, "Verily, this is the first room.", ctx);
    do_cmd(cmd[1], test_callback, "Verily, this is the first room.", ctx);

    free(cmd_str);
    game_free(ctx->game);
    chiventure_ctx_free(ctx);
}
