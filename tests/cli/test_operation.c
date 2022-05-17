#include <criterion/criterion.h>
#include <string.h>
#include <ui/ui.h>
#include "game-state/game.h"
#include "common/ctx.h"
#include "cli/parser.h"
/* the parser include is for the TOKEN_LIST_SIZE constant */


/* Creates a chiventure context with a sample game
 * also tests whether basic information has been populated properly
 * this includes if the rooms are not null
 *
 * Parameters: None
 *
 * Returns: a chiventure context
 */
chiventure_ctx_t *maketest_ctx()
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

    room1 = find_room_from_game(ctx->game, "room1");
    cr_assert_not_null(room1, "Could not fetch room1 from game");
    room2 = find_room_from_game(ctx->game, "room2");
    cr_assert_not_null(room2, "Could not fetch room2 from game");
    /* Check that the game is in the initial room */
    cr_assert_eq(ctx->game->curr_room, room1);

    return ctx;
}

/* function declaration for reference:
 *
 * char *kind4_action_operation(
 *				    char *tokens[TOKEN_LIST_SIZE],
 *				    chiventure_ctx_t *ctx)
 * */





/* filler test */
Test(operation, kind4_game_null)
{
    int quit;
    chiventure_ctx_t *ctx = maketest_ctx();
    char **tokens = (char**)calloc(TOKEN_LIST_SIZE,sizeof(char*));
    tokens[0] = "VIEW";
    tokens[1] = "STATS";

    ctx->game = NULL;


}

///* Creates a chiventure context with a sample game
// *
// * Parameters: None
// *
// * Returns: a chiventure context
// */
//chiventure_ctx_t *create_sample_ctx()
//{
//    game_t *game = game_new("Welcome to Chiventure!");
//    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
//    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
//    add_room_to_game(game, room1);
//    add_room_to_game(game, room2);
//    game->curr_room = room1;
//    create_connection(game, "room1", "room2", "NORTH");
//
//    /* Create context */
//    chiventure_ctx_t *ctx = chiventure_ctx_new(game);
//
//    return ctx;
//}
//
//
///* CLI callback that compares the produced output with an expected value
// *
// * Parameters:
// *  - ctx: chiventure context
// *  - outstr: The string printed out by the CLI
// *  - args: The expected string
// *
// * Returns:
// *  - An assertion will fail if outstr is not equal to args.
// *    Otherwise, always returns CLI_CMD_SUCCESS.
// */
//int test_callback(chiventure_ctx_t *ctx, char *outstr, void* args)
//{
//    char *expected = (char*) args;
//
//    cr_assert_str_eq(outstr, expected);
//
//    return CLI_CMD_SUCCESS;
//}
//
//
///* Creates a sample game and runs the LOOK command */
//Test(game, look)
//{
//    int quit;
//    chiventure_ctx_t *ctx = create_sample_ctx();
//
//    char *cmd_str = strdup("LOOK");
//    cmd *cmd = cmd_from_string(cmd_str, ctx);
//    cr_assert_not_null(cmd, "cmd_from_string failed");
//
//    do_cmd(cmd, test_callback, "Verily, this is the first room.", ctx);
//
//    free(cmd_str);
//    game_free(ctx->game);
//    chiventure_ctx_free(ctx);
//}
//
//
///* Creates a sample game, runs the GO command and verifies that
// * the player moved to a different room */
//Test(game, go)
//{
//    int quit;
//    chiventure_ctx_t *ctx = create_sample_ctx();
//
//    room_t *room1 = find_room_from_game(ctx->game, "room1");
//    cr_assert_not_null(room1, "Could not fetch room1 from game");
//    room_t *room2 = find_room_from_game(ctx->game, "room2");
//    cr_assert_not_null(room2, "Could not fetch room2 from game");
//
//    /* Check that the game is in the initial room */
//    cr_assert_eq(ctx->game->curr_room, room1);
//
//    char *cmd_str = strdup("GO NORTH");
//    cmd *cmd = cmd_from_string(cmd_str, ctx);
//    cr_assert_not_null(cmd, "cmd_from_string failed");
//
//    do_cmd(cmd, NULL, NULL, ctx);
//
//    /* Check that current room has changed */
//    cr_assert_eq(ctx->game->curr_room, room2,
//                 "GO NORTH did not change the current room as expected");
//
//    free(cmd_str);
//    game_free(ctx->game);
//    chiventure_ctx_free(ctx);
//}
