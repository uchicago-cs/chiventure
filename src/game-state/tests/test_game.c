#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game.h"
/*
void setup(void) {
    game_t *game = game_new();
    player_t *plyr = player_new(100);
    room_t *room1 = room_new("vroom", )
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

need to figure out how to feed in test struct into criterion
//assuming that is completed
Test(game, init) 
{
    game_t *game = //test struct

}

Test(game, save) 
{
    game_t *game = //test struct
    int rc = 0;
    rc = save_game(game, f);
    cr_assert_eq(rc, 1, "file not saved");
}

Test(game, move room) 
{
    game_t *game = //teststruct
    game->curr_room = curr;
    room_t *new_room = //add new room?
    move_room(game, new_room);
    int strcheck = strcmp(curr->room_id, game->curr_room->room_id);
    int chk = 0;
    if(strcheck != 1)
        chk = 1;
    
    cr_assert_eq(chk, 1, "failed to move to new room");

}

Test(game, free)
{
//tbd? 
}
*/
