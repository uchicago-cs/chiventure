#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "game-state/game.h"

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
    game_free(game);
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
    game_free(game);
}

/* Checks that find_room_from_game() returns the desired room pointer from a game
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

    room_t *r1 = find_room_from_game(game, room1->room_id);
    room_t *r2 = find_room_from_game(game, room2->room_id);
    room_t *r3 = find_room_from_game(game, "boiiii");
    int r1chk = strncmp(r1->room_id, room1->room_id, 256);
    int r2chk = strncmp(r2->room_id, room2->room_id, 256);
    cr_assert_not_null(r1, "room 1 not added");
    cr_assert_not_null(r2, "room 2 not added");

    cr_assert_eq(r1chk, 0, "found wrong room1");
    cr_assert_eq(r2chk, 0, "found wrong room2");
    cr_assert_eq(r3, NULL, "found bad room");
    game_free(game);
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
    cr_assert_eq(north, 0, "create_connection: failed to exit successfully");
    game_free(game);
}

/* Checks that create_connection() fails if source room is not found
*/
Test(game_room, create_connection_2)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;

    int south = create_connection(game, "vroom", "nroom", "south");
    cr_assert_eq(south, 2, "create_connection: should have failed");
    game_free(game);
}

/* Checks that create_connection() fails if dest room is not found
*/
Test(game_room, create_connection_3)
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");

    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;

    int west = create_connection(game, "vroom1", "nrom", "west");
    cr_assert_eq(west, 3, "create_connection: should have failed");
    game_free(game);
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

    // room_t *curr = game->curr_room;
    room_t *room3 = NULL;
    game_t *game_fake = NULL;
    int mv_check = move_room(game, room2);
    int strcheck = strncmp(room2->room_id, game->curr_room->room_id, MAX_ID_LEN);
    int mv_fail = move_room(game, room3);
    int mv_gfail = move_room(game_fake, room2);

    cr_assert_eq(mv_check, SUCCESS, "failed to move room");
    cr_assert_eq(strcheck, SUCCESS, "failed to move to new room");
    cr_assert_eq(mv_fail, 3, "moved to NULL room");
    cr_assert_eq(mv_gfail, 2, "moved in null game");
    game_free(game);

}

/* Checks that add_player_to_game() adds a player to the
game struct's player hash table */
Test(game_player, add_player_to_game)
{
    game_t *game = game_new("Welcome to Chiventure!");
    player_t *plyr = player_new("player_one");
    add_player_to_game(game, plyr);
    set_curr_player(game, plyr);

    cr_assert_not_null(plyr, "player 1 not initialized");
    player_t *p1 = get_player(game, "player_one");
    int p1chk = strncmp(p1->player_id, plyr->player_id, 256);
    cr_assert_not_null(p1, "player 1 not added to all_players");

    cr_assert_eq(p1chk, 0, "found wrong player1");
    game_free(game);
}

/* Checks that set_curr_player() sets the current player field of game struct
* tests set to player_one
* tests set to player_two
* tests set to NULL
*/
Test(game_player, set_curr_player)
{
    game_t *game = game_new("Welcome to Chiventure!");
    player_t *plyr1 = player_new("player_one");
    player_t *plyr2 = player_new("player_two");
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
    game_free(game);
}

/* Checks that get_player() returns the desired player from the game struct */
Test(game_player, get_player)
{
    game_t *game = game_new("Welcome to Chiventure!");
    player_t *plyr1 = player_new("player_one");
    player_t *plyr2 = player_new("player_two");
    add_player_to_game(game, plyr1);
    add_player_to_game(game, plyr2);

    player_t *test1 = get_player(game, "player_one");
    player_t *test2 = get_player(game, "player_two");

    int check1 = strncmp(test1->player_id, plyr1->player_id, MAX_ID_LEN);
    int check2 = strncmp(test2->player_id, plyr2->player_id, MAX_ID_LEN);

    cr_assert_eq(check1, 0, "get_player: failed plyr1");
    cr_assert_eq(check2, 0, "get_player: failed plyr2");
    game_free(game);
}

/* Checks that add_npc_to_game() adds an npc to the game's npc hash table 
 * Checks that get_npc() correctly finds an npc in game's npc hash table.
 */
Test(game_npc, add_and_get_npc)
{
    game_t *game = game_new("Welcome to Chiventure!");
    npc_t *npc = npc_new("TEST_NPC", "a test npc", "an npc for testing",
                         NULL, NULL, false);
    add_npc_to_game(game, npc);

    cr_assert_not_null(npc, "test_npc not initialized");

    npc_t *test = get_npc(game, "TEST_NPC");

    int check = strncmp(npc->npc_id, npc->npc_id, MAX_ID_LEN);

    cr_assert_not_null(test, "test_npc not found in game");
    cr_assert_eq(check, 0, "get_npc found wrong npc");
    game_free(game);
}

/* Checks that add_end_condition_to_game() adds valid end conditions to a game
 * Additionally insures that bad end conditions are not added 
 */
Test(game_end_condition, add_end_condition_to_game)
{
    game_t *game = game_new("Welcome to Chiventure!");

    attribute_value_t *test_value_1 = malloc(sizeof(attribute_value_t));
    test_value_1->str_val = "Test_Value_1";
    attribute_value_t *test_value_2 = malloc(sizeof(attribute_value_t));
    test_value_2->str_val = "Test_Value_2";



    item_t *test_item_1 = item_new("test_item_1", 
    "test item 1 for end conditions",
    "item for testing add_end_condition_to_game()");
    set_str_attr(test_item_1, "Test_Attribute_1", "Test_Value_1");
    
    item_t *test_item_2 = item_new("test_item_2", 
    "test item 2 for end conditions",
    "item for testing add_end_condition_to_game()");
    set_str_attr(test_item_2, "Test_Attribute_2", "Test_Value_2");

    add_item_to_game(game, test_item_1);

    condition_t *condition_1 = attribute_condition_new(test_item_1, "Test_Attribute_1", test_value_1);
    condition_t *condition_2 = attribute_condition_new(test_item_1, "Test_Attribute_2", test_value_2);
    condition_t *condition_3 = attribute_condition_new(test_item_2, "Test_Attribute_1", test_value_1);
    condition_t *condition_4 = attribute_condition_new(test_item_2, "Test_Attribute_2", test_value_2);
    
    int add_1 = add_end_condition_to_game(game, condition_1);
    cr_assert_eq(add_1, SUCCESS, "add_end_condition_to_game() did not add condition_1");
    
    int add_2 = add_end_condition_to_game(game, condition_2);    
    cr_assert_neq(add_2, SUCCESS, "add_end_condition_to_game() added an invalid condition (2)");
    
    int add_3 = add_end_condition_to_game(game, condition_3);
    cr_assert_neq(add_3, SUCCESS, "add_end_condition_to_game() added an invalid condition (3)");
    
    int add_4 = add_end_condition_to_game(game, condition_4);
    cr_assert_neq(add_4, SUCCESS, "add_end_condition_to_game() added an invalid condition (4)");

    add_item_to_game(game, test_item_2);
    int add_5 = add_end_condition_to_game(game, condition_4);
    cr_assert_eq(add_5, SUCCESS, "add_end_condition_to_game() did not add condition_2");
    game_free(game);
    free(test_value_1);
    free(test_value_2);
}

/* Checks that end_conditions_met() properly assesses when 
 * all end conditions of a game have been met 
 */
Test(game_end_condition, end_conditions_met)
{
    game_t *game = game_new("Welcome to Chiventure!");
    
    bool test_1 = end_conditions_met(game);
    cr_assert_eq(test_1, false, "end_conditions_met() does not return false when there are no end conditions");
    
    attribute_value_t *expected = malloc(sizeof(attribute_value_t));
    expected->str_val = "Valid_Value";
    
    item_t *test_item_1 = item_new("test_item_1", 
    "test item 1 for end conditions",
    "item for testing end_conditions_met()");
    set_str_attr(test_item_1, "Test_Attribute_1", "Invalid_Value_1");
    add_item_to_game(game, test_item_1);

    condition_t *condition_1 = attribute_condition_new(test_item_1, "Test_Attribute_1", expected);
    add_end_condition_to_game(game, condition_1);
    
    item_t *test_item_2 = item_new("test_item_2", 
    "test item 2 for end conditions",
    "item for testing end_conditions_met()");
    set_str_attr(test_item_2, "Test_Attribute_2", "Invalid_Value_2");
    add_item_to_game(game, test_item_2);

    condition_t *condition_2 = attribute_condition_new(test_item_2, "Test_Attribute_2", expected);
    add_end_condition_to_game(game, condition_2);
    
    item_t *test_item_3 = item_new("test_item_3", 
    "test item 3 for end conditions",
    "item for testing end_conditions_met()");
    set_str_attr(test_item_3, "Test_Attribute_3", "Invalid_Value_3");
    add_item_to_game(game, test_item_3);
    
    condition_t *condition_3 = attribute_condition_new(test_item_3, "Test_Attribute_3", expected);
    add_end_condition_to_game(game, condition_3);
    
    bool test_2 = end_conditions_met(game);
    cr_assert_eq(test_2, false, "end_conditions_met() returns true when not all conditions are met");

    set_str_attr(test_item_1, "Test_Attribute_1", "Valid_Value");
    bool test_3 = end_conditions_met(game);
    cr_assert_eq(test_3, false, "end_conditions_met() returns true when not all conditions are met");
    
    set_str_attr(test_item_3, "Test_Attribute_3", "Valid_Value");
    bool test_4 = end_conditions_met(game);
    cr_assert_eq(test_4, false, "end_conditions_met() returns true when not all conditions are met");

    set_str_attr(test_item_2, "Test_Attribute_2", "Valid_Value");
    bool test_5 = end_conditions_met(game);
    cr_assert_eq(test_5, true, "end_conditions_met() does not return true when all end conditions are met");
    game_free(game);
    free(expected);
}

/* Helper function for is_game_over_tests to setup initial game */
game_t* setup_is_game_over_test(bool has_final_room, bool has_end_conditions)
{
    game_t *game = game_new("Welcome to Chiventure!");
    
    attribute_value_t *expected = malloc(sizeof(attribute_value_t));
    attribute_value_t *unexpected = malloc(sizeof(attribute_value_t));
    
    expected->str_val = malloc(sizeof(char)*100);
    memcpy(expected->str_val, "Valid_Value", strlen("Valid_Value"));
    unexpected->str_val = malloc(sizeof(char)*100);
    memcpy(unexpected->str_val, "Invalid_Value", strlen("Invalid_Value"));
    
    item_t *test_item = item_new("test_item", 
    "test item for is_game_over",
    "item for testing is_game_over()");
    set_str_attr(test_item, "Test_Attribute", unexpected->str_val);
    add_item_to_game(game, test_item);
    
    room_t *test_room1 = room_new("test_room1", "room1 short", "room1 long long long");
    room_t *test_room2 = room_new("test_room2", "room2 short", "room2 long long long");
    
    add_item_to_game(game, test_item);
    add_room_to_game(game, test_room1);
    add_room_to_game(game, test_room2);
    game->curr_room = test_room1;
    
    if (has_end_conditions)
    {
        condition_t *condition = attribute_condition_new(test_item, "Test_Attribute",
                                  expected);
        add_end_condition_to_game(game, condition);
    }
    
    if (has_final_room)
    {
        add_final_room_to_game(game, test_room2);
    }

    return game;
}

/* Checks that is_game_over properly returns false for a neverending game
 * ie when a game has no final room or end conditions */
Test(game_end_condition, is_game_over_neverending)
{
    game_t *game = setup_is_game_over_test(false, false);
    cr_assert_eq(is_game_over(game), false, "is_game_over() returns true when "
                 "no final room or end conditions exist");
    game_free(game);
}

/* Checks that is_game_over properly assesses when a game with
 * end conditions but no final room is over */
Test(game_end_condition, is_game_over_end_conditions)
{
    game_t *game = setup_is_game_over_test(false, true);
    
    cr_assert_eq(is_game_over(game), false, "is_game_over() returns true when "
                 "end conditions have not been met & no final room exists");
    item_t *item = get_item_from_game(game, "test_item");
    set_str_attr(item, "Test_Attribute", "Valid_Value");
    cr_assert_eq(is_game_over(game), true, "is_game_over() returns false when "
                 "end conditions have been met & no final room exists");
    game_free(game);
}

/* Checks that is_game_over properly assesses when a game with
 * a final room but no end conditions is over */
Test(game_end_condition, is_game_over_final_room)
{
    game_t *game = setup_is_game_over_test(true, false);
    
    cr_assert_eq(is_game_over(game), false, "is_game_over() returns true when "
                 "player has yet to reach final room & no end conditions exist");
    move_room(game, game->final_room);
    cr_assert_eq(is_game_over(game), true, "is_game_over() returns false when "
                 "player has reached final room & no end conditions exist");
    game_free(game);
}

/* Checks that is_game_over properly assesses when a game with
 * both a final room and end conditions is over */
Test(game_end_condition, is_game_over_end_conditions_final_room)
{
    game_t *game = setup_is_game_over_test(true, true);
    
    cr_assert_eq(is_game_over(game), false, "is_game_over() returns true when "
                 "player has yet to reach final room & "
                 "end conditions have not been met");
    
    move_room(game, game->final_room);
    cr_assert_eq(is_game_over(game), false, "is_game_over() returns true when "
                 "player has reached final room but "
                 "end conditions have not been met");
    
    room_t *room = find_room_from_game(game, "test_room1");
    move_room(game, room);
    item_t *item = get_item_from_game(game, "test_item");
    set_str_attr(item, "Test_Attribute", "Valid_Value");
    cr_assert_eq(is_game_over(game), false, "is_game_over() returns true when "
                 "end conditions have been met but "
                 "player has yet to reach final room");
    
    move_room(game, game->final_room);
    cr_assert_eq(is_game_over(game), true, "is_game_over() returns false when "
                 "end conditions have been met and "
                 "player has reached final room");
    game_free(game);
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

Test(iter, get_all_rooms_macro) {
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

Test(iter, get_all_rooms) {
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "room1 short", "room1 long long long");
    room_t *room2 = room_new("room2", "room2 short", "room2 long long long");
    room_t *room3 = room_new("room3", "room3 short", "room3 long long long");
    HASH_ADD_KEYPTR(hh, game->all_rooms, room1->room_id, strnlen(room1->room_id, MAX_ID_LEN), room1);
    HASH_ADD_KEYPTR(hh, game->all_rooms, room2->room_id, strnlen(room2->room_id, MAX_ID_LEN), room2);
    HASH_ADD_KEYPTR(hh, game->all_rooms, room3->room_id, strnlen(room3->room_id, MAX_ID_LEN), room3);
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

/* Checks that add_effect_to_game() adds a global effect to the
game struct's player hash table */
Test(game_stat_effects, add_stat_to_game)
{
    game_t *game = game_new("Welcome to Chiventure!");
    stats_global_t *global_stat = stats_global_new("health", 1000);
    int rc = add_stat_to_game(game, global_stat);

    cr_assert_eq(rc, SUCCESS, "add_stat_to_game failed");
    cr_assert_not_null(game->curr_stats, "stat not added to curr_stats");
    free_stats_global_table(game->curr_stats);
    game_free(game);
}

/* Checks that add_effect_to_game() adds a global effect to the
game struct's player hash table */
Test(game_stat_effects, add_effect_to_game)
{
    game_t *game = game_new("Welcome to Chiventure!");
    effects_global_t *effect = global_effect_new("health");
    int rc = add_effect_to_game(game, effect);

    cr_assert_eq(rc, SUCCESS, "add_effect_to_game failed");
    cr_assert_not_null(game->all_effects, "effect not added to all_effects");
    delete_all_global_effects(game->all_effects);
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
room_t *find_room_from_game(game_t *game, char* room_id);

*/
