#include <criterion/criterion.h>
#include <string.h>
#include <ui/ui.h>
#include "game-state/game.h"
#include "common/ctx.h"
#include "cli/operations.h"
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


//===========================================
//     kind4_action_operation testing
//===========================================

/* White-Box testing for game struct being null on kind4_operation*/
Test(operation, kind4_game_null)
{
    chiventure_ctx_t *ctx = maketest_ctx();
    char **tokens = (char**)calloc(TOKEN_LIST_SIZE,sizeof(char*));
    tokens[0] = "VIEW";
    tokens[1] = "STATS";

    ctx->game = NULL;
    char *return_string = kind4_action_operation(tokens,ctx);
    cr_assert_str_eq(return_string,"No game found!\n","game null flow was not matched when game was null");
}

/* White-Box testing for there not being a second string in token array */
Test(operation, kind4_missing_arg)
{
    chiventure_ctx_t *ctx = maketest_ctx();
    printf("\n\nGETTING PAST MAKETEST FINAL FINAL FINAL\n\n");
    char **tokens = (char**)calloc(TOKEN_LIST_SIZE,sizeof(char*));
    tokens[0] = "VIEW";
    tokens[1] = NULL;

    char *return_string = kind4_action_operation(tokens,ctx);
    cr_assert_str_eq(return_string,"Second argument needed.\n","arg2 was not null but kind4 didn't match to that control flow\n");
}

/* White-Box testing for there being more than 1 argument after the action
 *
 * Currently (5/23/2022), action management has not implemented a control 
 * flow to handle view stats with extra parameters, 
 * so we've left it as expecting an empty string
 * */
/*
Test(operation, kind4_three_args)
{
    printf("\n\n========================================\n\t\tENTERING MAKETEST IN THREE\n========================================\n\n");
    chiventure_ctx_t *ctx = maketest_ctx();
    char **tokens = (char**)calloc(TOKEN_LIST_SIZE,sizeof(char*));
    tokens[0] = "VIEW";
    tokens[1] = "STATS";
    tokens[2] = "NOW";

    char *return_string = kind4_action_operation(tokens,ctx);
    printf("\n\nreturn_string = %s\n\n",return_string);
    //cr_expect_str_empty(return_string,"arg3 was not null, but did not match that control flow\n");
}
*/


/* White-Box testing for there being 4 args specifically, 
 * should fall under same control flow as the kind4_three_arg test*/
Test(operation, kind4_four_args)
{
    chiventure_ctx_t *ctx = maketest_ctx();
    char **tokens = (char**)calloc(TOKEN_LIST_SIZE,sizeof(char*));
    tokens[0] = "VIEW";
    tokens[1] = "STATS";
    tokens[2] = "NOW";
    tokens[3] = "PLEASE";

    char *return_string = kind4_action_operation(tokens,ctx);
    cr_assert_str_eq(return_string,"This action only supports two arguments\n","kind4 was given 4 arguments and did not match the correct control flow\n");
}

/* White-Box testing for the normal control flow
 * this test DOES work, the control flow matches, however with the 
 * implementation of display_stats we cannot directly test it with the below test*/
/*
Test(operation, kind4_normal_flow1)
{
    chiventure_ctx_t *ctx = maketest_ctx();
    char **tokens = (char**)calloc(TOKEN_LIST_SIZE,sizeof(char*));
    tokens[0] = "VIEW";
    tokens[1] = "STATS";

    char *return_string = kind4_action_operation(tokens,ctx);
    cr_expect_str_eq(return_string,"","normal control flow (VIEW STATS) did not match normal control flow\n");
}
*/
