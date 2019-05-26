#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game.h"

/*
void setup(void) {
    game_t *game = game_new();
    player_t *plyr = player_new(100);
    room_t *room1 = room_new("vroom", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    add_room_to_game(game, room1);
    add_player_to_game(game, plyr);
    game->curr_player = plyr;
    game->curr_room = room1;
    path_t *path = path_new(room2,"north");
    add_path_to_room(room1, path);
}

void teardown(void) {
    puts("Runs after the test");

}

Test(game, new_free)
{
    game_t *game = game_new();
    cr_assert_not_null(game, "game_new() failed");
    cr_assert_eq(game_free(game), SUCCESS, "game_free() failed");
}


Test(game, init)
{
    game_t *game_test = game_new();

}


Test(game, save)
{
    game_t *game = //test struct
    int rc = 0;
    rc = save_game(game, f);
    cr_assert_eq(rc, 1, "file not saved");
}


Test(game, move_room, .init = setup)
{
    room_t *curr = game->curr_room;
    move_room(game, nroom);
    int strcheck = strcmp(curr->room_id, game->curr_room->room_id);
    int chk = 0;
    if(strcheck != 1)
        chk = 1;

    cr_assert_eq(chk, 1, "failed to move to new room");

}

*/
