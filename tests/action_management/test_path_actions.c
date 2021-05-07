#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_management/actionmanagement.h"
#include "action_management/action_structs.h"
#include "game-state/item.h"
#include "game-state/player.h"
#include "common/ctx.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (2)
#define NOT_ALLOWED_PATH (5)

void check_do_path(chiventure_ctx_t *c, action_type_t *a, path_t *p, room_t *room_expected, int rc_expected)
{
    int rc;
    char *ret_string;
    room_t *room_output;

    rc = do_path_action(c, a, p, &ret_string);
    room_output = c->game->curr_room;
    cr_expect_eq(room_expected, room_output,
                 "The room expected, %s, did not match the actual room output, %s.",
                 room_expected->room_id, room_output->room_id);
    cr_assert_eq(rc_expected, rc,
                 "The expected return code was %d, but the actual return code was %d.\n"
                 "The return string given: %s.",
                 rc_expected, rc, ret_string);
    free(ret_string);
}

Test(path_actions, validate_path)
{
    /* INITIALIZE VARIABLES */
    chiventure_ctx_t *ctx_test;
    game_t *game_test;
    player_t *player_test;
    room_t *room_north, *room_origin;
    path_t *path_north, *path_origin;
    action_type_t *action_go, *action_walk, *action_invalid;

    /* CREATE VARIABLE CONTENTS */
    ctx_test = chiventure_ctx_new(NULL);
    game_test = game_new("This is a test game!");
    player_test = player_new("player");
    room_origin = room_new("room_o", "origin room", "This is the room the player starts in.");
    room_north = room_new("room_n", "room north of origin", "This is the room north of the spawn.");
    action_go = action_type_new("GO", PATH);
    action_walk = action_type_new("WALK", PATH);
    action_invalid = action_type_new("OPEN", ITEM);

    /* FILL VARIABLE CONTENTS */
    add_player_to_game(game_test, player_test);
    set_curr_player(game_test, player_test);
    add_room_to_game(game_test, room_origin);
    add_room_to_game(game_test, room_north);
    create_connection(game_test, room_origin->room_id, room_north->room_id, "north");
    create_connection(game_test, room_north->room_id, room_origin->room_id, "origin");
    path_north = path_search(room_origin, "north");
    path_origin = path_search(room_north, "origin");
    game_test->curr_room = room_origin;
    ctx_test->game = game_test;

    /* SUCCESS TEST */
    check_do_path(ctx_test, action_go, path_north, room_north, SUCCESS);
    // player should be in room_north
    check_do_path(ctx_test, action_go, path_origin, room_origin, SUCCESS);
    // player should be in room_origin

    check_do_path(ctx_test, action_walk, path_north, room_north, SUCCESS);
    // player should be in room_north
    check_do_path(ctx_test, action_walk, path_origin, room_origin, SUCCESS);
    // player should be in room_origin

    /* FAIL TESTS */
    check_do_path(ctx_test, action_invalid, path_north, room_origin, WRONG_KIND);
    check_do_path(ctx_test, action_go, path_origin, room_origin, NOT_ALLOWED_PATH);
    check_do_path(ctx_test, action_walk, path_origin, room_origin, NOT_ALLOWED_PATH);

    /* FREE VARIABLES */
    chiventure_ctx_free(ctx_test);
    game_free(game_test);
    action_type_free(action_go);
    action_type_free(action_walk);
    action_type_free(action_invalid);
}
