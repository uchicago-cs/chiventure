#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "actionmanagement.h"
#include "action_structs.h"
#include "item.h"
#include "player.h"
#include "ctx.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (1)
#define NOT_ALLOWED_PATH (4)

void check_do_path_action(chiventure_ctx_t *c, action_type_t *a, path_t *p, room_t *room_expected, int rc_expected)
{
    char *ret_string;
    room_t *room_ouput;
    rc = do_path_action(c, a, p, &ret_string);

    room_output = c->game->curr_room;
    cr_assert_eq(room_output, room_expected,
                 "The room expected, %s, did not match the room output, %s.",
                 room_expected->room_id, room_output->room_id);
    cr_assert_eq(rc, rc_expected,
                 "The expected return code was %d, but the actual return code was %d.",
                 rc_expected, rc);
}

Test(path_actions, validate_path)
{
    /* INITIALIZE VARIABLES */
    chiventure_ctx_t *ctx_test;
    game_t *game_test;
    room_t *room_north, *room_origin;
    player_t *player_test;
    path_t *path_north, *path_origin;
    action_type_t *action_enter;

    /* CREATE VARIABLE CONTENTS */
    ctx_test = chiventure_ctx_new();
    game_test = game_new("This is the test game!");
    player_test = player_new("player", 1);
    room_origin = room_new("room_o","origin room", "This is the room the player starts in.");
    room_north = room_new("room_n", "room north of origin", "This is the room north of the spawn.");
    path_north = path_new(room_north, "north");
    path_origin = path_new(room_origin, "origin");
    action_enter = action_type_new("ENTER", PATH);
    action_invalid = action_type_new("OPEN", ITEM);

    /* FILL VARIABLE CONTENTS */
    ctx_test->game = game_test;
    add_player_to_game(game_test, player_test);
    set_curr_player(game_test, player_test);
    add_path_to_room(path_north, room_origin);
    add_path_to_room(path_origin, room_north);

    /* SUCCESS TEST */
    execute_do_path_action(ctx_test, action_enter, path_north, room_north, SUCCESS);
    // player should be in room_north
    execute_do_path_action(ctx_test, action_enter, path_origin, room_origin, SUCCESS);
    // player should be in room_origin

    /* FAIL TESTS */
    execute_do_path_action(ctx_test, action_invalid, path_north, room_origin, WRONG_KIND);
    execute_do_path_action(ctx_test, action_enter, path_origin, room_origin, NOT_ALLOWED_PATH);

    /* FREE VARIABLES */
    chiventure_ctx_free(ctx_test);
    action_type_free(action_enter);
    action_type_free(action_invalid);
}
