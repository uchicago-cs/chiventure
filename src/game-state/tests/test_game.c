#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game.h"

void setup(void) {
    puts("Ready to go!");
}

void teardown(void) {
    puts("Runs after the test");
}

/*
game_t *start_test() {
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
    return game;
}
*/

Test(game, new_free)
{
    game_t *game = game_new();
    cr_assert_not_null(game, "game_new() failed");
    cr_assert_eq(game_free(game), SUCCESS, "game_free() failed");
}

/*
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

*/

Test(game, add_room_to_game) 
{
    game_t *game = game_new();
    room_t *room1 = room_new("vroom", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    
    cr_assert_not_null(room1, "room 1 not initialized");
    cr_assert_not_null(room2, "room 2 not initialized");

    room_t *r1 = find_room(game, room1->room_id);
    room_t *r2 = find_room(game, room2->room_id);
    //room_t *r3 = find_room(game, "boiiii");
    int r1chk = strncmp(r1->room_id, room1->room_id, 256);
    int r2chk = strncmp(r2->room_id, room2->room_id, 256);
    cr_assert_not_null(r1, "room 1 not added");
    cr_assert_not_null(r2, "room 2 not added");

    cr_assert_eq(r1chk, 0, "found wrong room1");
    cr_assert_eq(r2chk, 0, "found wrong room2");
    //cr_assert_eq(r3, NULL, "found bad room");

}
Test(game, move_room)
{
    game_t *game = game_new();
    room_t *room1 = room_new("vroom", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    path_t *path = path_new(room2,"north");
    add_path_to_room(room1, path);
    room_t *curr = game->curr_room;

    
    move_room(game, room2);
    int strcheck = strcmp(curr->room_id, game->curr_room->room_id);
    int chk = 0;
    if(strcheck != 1)
        chk = 1;

    cr_assert_eq(chk, 1, "failed to move to new room");

}

/*
Test(game, add_player_to_game) 
{
    game_t *game = game_new();
    player_t *plyr = player_new(100);
    add_player_to_game(game, plyr);
    game->curr_player = plyr;

}
*/
