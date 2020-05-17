#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_generation.h"

/* Tests the functions in sample_generation.h */

Test(sample_generation, enter_new_room1)
{
    room_t *sampleRoom1 = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom1, "sampleRoom1 is NULL");

    room_t *sampleRoom2 = room_new("another string1", "another string2", "another string3");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    cr_assert_eq(enter_new_room(sampleRoom1, sampleRoom2), true, 
    "enter_new_room() interpreted two different rooms as the same");
}

Test(sample_generation, enter_new_room2)
{
    room_t *sampleRoom = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom, "sampleRoom is NULL");

    cr_assert_eq(enter_new_room(sampleRoom, sampleRoom), false, 
    "enter_new_room() interpreted two same rooms as different");
}

Test(sample_generation, room_generate1)
{
    room_t *sampleRoom = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom, "sampleRoom is NULL");

    room_t *sampleRoom2 = room_new("another string1", "another string2", "another string3");
    cr_assert_not_null(sampleRoom2, "sampleRoom2 is NULL");

    game_t *game = game_new("desc");
    cr_assert_not_null(game, "game is NULL");

    game->curr_room = sampleRoom2;

    cr_assert_eq(room_generate(game->curr_room, game, sampleRoom), 0, 
    "room_generate: Could not add room to game");

    int not_eq = (game->curr_room == sampleRoom); // We want these to be different

    // game->curr_room is sampleRoom2
    cr_assert_eq(not_eq, 0, "Rooms should be different");
}

Test(sample_generation, room_generate2)
{
    room_t *sampleRoom = room_new("string1", "string2", "string3");
    cr_assert_not_null(sampleRoom, "sampleRoom is NULL");

    game_t *game = game_new("desc");
    cr_assert_not_null(game, "game is NULL");

    game->curr_room = sampleRoom;

    cr_assert_eq(room_generate(game->curr_room, game, sampleRoom), 1, 
    "room_generate: Should not have added room to game");

    int eq = (game->curr_room != sampleRoom); // We want these to be different

    // game->curr_room is sampleRoom2
    cr_assert_eq(eq, 0, "Rooms should be the same");
}