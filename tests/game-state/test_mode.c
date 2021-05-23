#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "game-state/mode.h"
#include "game-state/game.h"


/* A function of the mode_operation type for testing mode functions */
int test_operation(char *str, cli_callback callback_func,
                   void *callback_args, chiventure_ctx_t *ctx)
{
    return SUCCESS;
}

/* Checks the creation of mode struct */
Test(mode, new)
{
    game_mode_t *new_mode = game_mode_new(NORMAL, NULL, "test context");

    cr_assert_not_null(new_mode, "game_mode_new() test has failed!");

    game_mode_free(new_mode);
}

/* Checks the initialization of a mode struct */
Test(mode, init)
{
    game_mode_t *mode = game_mode_new(NORMAL, NULL, "normal");

    int rc = game_mode_init(mode, NORMAL, test_operation, "test context");

    cr_assert_eq(rc, SUCCESS, "game_mode_init() has failed!");

    cr_assert_eq(mode->curr_mode, NORMAL, 
                 "game_mode_init() didn't set curr_mode");
    cr_assert_eq(strncmp(mode->mode_ctx, "test context", MAX_ID_LEN), 0,
                 "game_mode_init() didn't set mode_ctx");
    cr_assert_eq((*(mode->run_mode))("test", NULL, NULL, NULL), SUCCESS,
                 "game_mode_init() didn't set run_mode");

    game_mode_free(mode);
}

/* Checks the freeing a mode struct */
Test(mode, free)
{
    game_mode_t *new_mode = game_mode_new(NORMAL, test_operation, 
                                          "test context");
    int rc = game_mode_free(new_mode);

    cr_assert_not_null(new_mode, "game_mode_new() test has failed!");
    cr_assert_eq(rc, SUCCESS, "game_mode_free() has failed!");
}

/* Checks that normal mode is loaded correctly */
Test(mode, load_normal)
{
    game_t g;

    int rc = load_normal_mode(&g);

    cr_assert_eq(rc, SUCCESS, "load_normal_mode() has failed!");

    cr_assert_not_null(g.mode, "load_normal_mode() has failed!");
    cr_assert_eq(g.mode->curr_mode, NORMAL, 
                 "load_normal_mode() didn't set curr_mode");
    cr_assert_eq(strncmp(g.mode->mode_ctx, "normal", MAX_ID_LEN), 0,
                 "load_normal_mode() didn't set mode_ctx");

    game_mode_free(g.mode);
}

/* Check that set_game_mode correctly sets the game's mode */
Test(mode, set_game)
{
    game_t g;
    
    int rc = load_normal_mode(&g);
    cr_assert_eq(rc, SUCCESS, "load_normal_mode() has failed!");
    cr_assert_not_null(g.mode, "load_normal_mode() has failed!");

    //Testing set to conversation mode
    rc = set_game_mode(&g, CONVERSATION, "STEVE");
    cr_assert_eq(rc, SUCCESS, "set_game_mode() has failed!");
    cr_assert_eq(g.mode->curr_mode, CONVERSATION, 
                 "set_game_mode() didn't set CONVERSATION mode");
    cr_assert_eq(strncmp(g.mode->mode_ctx, "STEVE", MAX_ID_LEN), 0,
                 "set_game_mode() didn't set mode_ctx");

    //Testing set to normal mode
    rc = set_game_mode(&g, NORMAL, NULL);
    cr_assert_eq(rc, SUCCESS, "set_game_mode() has failed!");
    cr_assert_eq(g.mode->curr_mode, NORMAL, 
                 "set_game_mode() didn't set NORMAL");
    cr_assert_eq(strncmp(g.mode->mode_ctx, "normal", MAX_ID_LEN), 0,
                 "set_game_mode() didn't set mode_ctx");
}
