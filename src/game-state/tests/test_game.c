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

/* Checks that game_new() mallocs memory for a game struct
and initializes it with a starting string */
Test(game_start, new)
{
    game_t *game = game_new("hello and welcome to this awesome game");
    cr_assert_not_null(game, "game_new() failed");
    cr_assert_eq(strncmp(game->start_desc,
        "hello and welcome to this awesome game", MAX_START_DESC_LEN), 0,
        "game_new() failed to set the starting description");
}

/* Checks that game_free() frees a game struct successfully */
Test(game_start, free)
{
    game_t *game = game_new("hello and welcome to this awesome game");
    cr_assert_not_null(game, "game_new() failed");
    cr_assert_eq(game_free(game), SUCCESS, "game_free() failed");
}

/* Checks that add_room_to_game() adds a room to the game struct's room hash
* Adds two rooms
*/
Test(game_room, add_room_to_game)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    cr_assert_not_null(room1, "room 1 not initialized");
    cr_assert_not_null(room2, "room 2 not initialized");

    int r1 = add_room_to_game(game, room1);
    int r2 = add_room_to_game(game, room2);

    cr_assert_eq(r1, SUCCESS, "add_room_to_game: room1 failed");
    cr_assert_eq(r2, SUCCESS, "add_room_to_game: room2 failed");
}

/* Checks that find_room() returns the desired room pointer from a game
* Also tests for a room that was not added (supposed to return NULL)
*/
Test(game_room, find_room)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    cr_assert_not_null(room1, "room 1 not initialized");
    cr_assert_not_null(room2, "room 2 not initialized");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);

    room_t *r1 = find_room(game, room1->room_id);
    room_t *r2 = find_room(game, room2->room_id);
    room_t *r3 = find_room(game, "boiiii");
    int r1chk = strncmp(r1->room_id, room1->room_id, 256);
    int r2chk = strncmp(r2->room_id, room2->room_id, 256);
    cr_assert_not_null(r1, "room 1 not added");
    cr_assert_not_null(r2, "room 2 not added");

    cr_assert_eq(r1chk, 0, "found wrong room1");
    cr_assert_eq(r2chk, 0, "found wrong room2");
    cr_assert_eq(r3, NULL, "found bad room");

}

/* Checks that create_connection() creates a path from
* one existing room to another
*/
Test(game_room, create_connection_0)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    int north = create_connection(game, "vroom1", "nroom", "north");
    cr_assert_eq(north, SUCCESS, "create_connection: failed to exit successfully");

}

/* Checks that create_connection() fails if source room is not found
*/
Test(game_room, create_connection_1)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;

    int south = create_connection(game, "vroom", "nroom", "south");
    cr_assert_eq(south, FAILURE, "create_connection: should have failed");

}

/* Checks that create_connection() fails if dest room is not found
*/
Test(game_room, create_connection_2)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;

    int west = create_connection(game, "vroom1", "nrom", "west");
    cr_assert_eq(west, FAILURE, "create_connection: should have failed");
}

/* Checks that move_room() switches the current room stored in game
* tests failed move and successful move
* failed move takes in NULL room (mv_fail)
* another failed move takes in NULL game (mv_gfail)
*/
Test(game_room, move_room)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "vroom1", "nroom", "north");

    room_t *curr = game->curr_room;
    room_t *room3 = NULL;
    game_t *game_fake = NULL;
    int mv_check = move_room(game, room2);
    int strcheck = strncmp(curr->room_id, game->curr_room->room_id, MAX_ID_LEN);
    int mv_fail = move_room(game, room3);
    int mv_gfail = move_room(game_fake, room2);

    cr_assert_eq(mv_check, SUCCESS, "failed to move room");
    cr_assert_eq(strcheck, SUCCESS, "failed to move to new room");
    cr_assert_eq(mv_fail, FAILURE, "moved to NULL room");
    cr_assert_eq(mv_gfail, FAILURE, "moved in null game");


}

/* Checks that add_player_to_game() adds a player to the
game struct's player hash table */
Test(game_player, add_player_to_game)
{
    game_t *game = game_new("Welcome to Chiventure!");
    player_t *plyr = player_new("player_one", 100);
    add_player_to_game(game, plyr);
    set_curr_player(game, plyr);

    cr_assert_not_null(plyr, "player 1 not initialized");
    player_t *p1 = get_player(game, "player_one");
    int p1chk = strncmp(p1->player_id, plyr->player_id, 256);
    cr_assert_not_null(p1, "player 1 not added to all_players");

    cr_assert_eq(p1chk, 0, "found wrong player1");
}

/* Checks that set_curr_player() sets the current player field of game struct
* tests set to player_one
* tests set to player_two
* tests set to NULL
*/
Test(game_player, set_curr_player)
{
    game_t *game = game_new("Welcome to Chiventure!");
    player_t *plyr1 = player_new("player_one", 100);
    player_t *plyr2 = player_new("player_two", 100);
    add_player_to_game(game, plyr1);
    add_player_to_game(game, plyr2);
    set_curr_player(game, plyr1);

    int check = strncmp(game->curr_player->player_id, plyr1->player_id,
        MAX_ID_LEN);
    set_curr_player(game, plyr2);
    int check2 = strncmp(game->curr_player->player_id, plyr2->player_id,
        MAX_ID_LEN);
    int chk_fail = set_curr_player(game, NULL);
    cr_assert_eq(check, SUCCESS, "set_curr_player to player_one failed");
    cr_assert_eq(check2, SUCCESS, "set_curr_player to player_two failed");
    cr_assert_eq(chk_fail, FAILURE, "set NULL player");
}

/* Checks that get_player() returns the desired player from the game struct */
Test(game_player, get_player)
{
    game_t *game = game_new("Welcome to Chiventure!");
    player_t *plyr1 = player_new("player_one", 100);
    player_t *plyr2 = player_new("player_two", 100);
    add_player_to_game(game, plyr1);
    add_player_to_game(game, plyr2);

    player_t *test1 = get_player(game, "player_one");
    player_t *test2 = get_player(game, "player_two");

    int check1 = strncmp(test1->player_id, plyr1->player_id, MAX_ID_LEN);
    int check2 = strncmp(test2->player_id, plyr2->player_id, MAX_ID_LEN);

    cr_assert_eq(check1, 0, "get_player: failed plyr1");
    cr_assert_eq(check2, 0, "get_player: failed plyr2");
}

Test(iter_macro, iter_rooms)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "room1 short", "room1 long long long");
    room_t *room2 = room_new("room2", "room2 short", "room2 long long long");
    room_t *room3 = room_new("room3", "room3 short", "room3 long long long");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    int cnt = 0;
    room_t *curr_room;
    ITER_ALL_ROOMS(game, curr_room) {
        cnt++;
        if (!strncmp(curr_room->room_id, "room1", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room1 long long long",
            "ldesc does not correspond");
        } else if (!strncmp(curr_room->room_id, "room2", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room2 long long long",
            "ldesc does not correspond");
        } else if (!strncmp(curr_room->room_id, "room3", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room3 long long long",
            "ldesc does not correspond");
        } else {
            cr_assert_fail("non-existent room detected");
        }
    }
    cr_assert_eq(cnt, 3, "wrong room counts");
    game_free(game);
}

Test(iter, get_all_rooms) {
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "room1 short", "room1 long long long");
    room_t *room2 = room_new("room2", "room2 short", "room2 long long long");
    room_t *room3 = room_new("room3", "room3 short", "room3 long long long");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    add_room_to_game(game, room3);
    int cnt = 0;
    room_t *curr_room;
    room_list_t *list = get_all_rooms(game);
    room_list_t *elt;
    LL_FOREACH(list, elt) {
        cnt++;
        curr_room = elt->room;
        if (!strncmp(curr_room->room_id, "room1", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room1 long long long",
            "ldesc does not correspond");
        } else if (!strncmp(curr_room->room_id, "room2", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room2 long long long",
            "ldesc does not correspond");
        } else if (!strncmp(curr_room->room_id, "room3", MAX_ID_LEN)) {
            cr_assert_str_eq(get_ldesc(curr_room), "room3 long long long",
            "ldesc does not correspond");
        } else {
            cr_assert_fail("non-existent room detected");
        }
    }
    cr_assert_eq(cnt, 3, "wrong room counts");
    cr_assert_eq(delete_room_llist(list), SUCCESS, "delete llist failed");
    game_free(game);
}
/*
//untested
//doesn't need testing
//is carbon copy of game_free for now
void game_quit(game_t *game);


//tested
void move_room(game_t *game, room_t *new_room);
int add_player_to_game(game_t *game, player_t *player);
int add_room_to_game(game_t *game, room_t *room);
int set_curr_player(game_t *game, player_t *player);
player_t *get_player(game_t *game, char *player_id);
int game_free(game_t *game);
game_t *game_new(char *start_desc);
int create_connection(game_t *game, char* src_room, char* dest_room, char* direction);
room_t *find_room(game_t *game, char* room_id);

*/
