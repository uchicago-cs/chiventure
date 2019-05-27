#include <stdio.h>
#include <criterion/criterion.h>
#include "room.h"
#include "game_state_common.h"
#include "common-room.h"


// BASIC PATH UNIT TESTS ------------------------------------------------------
/* checks creation of new path */
Test(path, new)
{
    room_t *new_room = room_new("test_room", "room for testing", "room to test path_new()");
    path_t *new_path = path_new(new_room, "north");

    cr_assert_not_null(new_path, "path_new() test 1 has failed!");

}

/* checks path is properly freed */
Test(path, free)
{
    room_t *test_dest = room_new("test_dest", "room for testing", "room to test path_free");
    path_t *path_tofree = path_new(test_dest, "west");

    int freed = path_free(path_tofree);

    cr_assert_eq(freed, SUCCESS, "path_free() test 1 has failed!");

}

// TESTS FOR ADDING FUNCTIONS -------------------------------------------------

Test(path, add_to_room)
{
    room_t *test_room = room_new("test_room", "room for testing", "testing add_path_to_room()");
    path_t *test_path = path_new(test_room, "east");

    cr_assert_not_null(test_path, "add_path_to_room() test: path initialization failed!");

    int added = add_path_to_room(test_room, test_path);
    cr_assert_eq(added, SUCCESS, "add_path_to_room() test: path was not successfully added to room!");

}

// will write tests for adding conditions to path when WDL and action management finalize conditions
// TESTS FOR FIND/SEARCH FUNCTIONS --------------------------------------------
Test(path, search)
{
    room_t *test_room = room_new("test_room", "room for testing", "testing path_search()");
    path_t *test_path = path_new(test_room, "south");

    int added = add_path_to_room(test_room, test_path);
    cr_assert_eq(added, SUCCESS, "path_search() test: path was not successfully added to room!");

    path_t *path_found = path_search(test_room, "south");

    cr_assert_str_eq(path_found->direction, "south", "path_search() test: path found has incorrect direction!");
    cr_assert_str_eq(path_found->dest->room_id, "test_room", "path_search() test: path found has incorrect destination room!");

}

Test(path, find_room)
{
    room_t *test_room = room_new("test_room", "room for testing", "room for testing find_room_from_path()");
    path_t *test_path = path_new(test_room, "north");

    room_t *found_room = find_room_from_path(test_path);

    cr_assert_str_eq(found_room->room_id, "test_room", "find_room_from_path() test: room found from path has incorrect room_id!");

    cr_assert_str_eq(found_room->short_desc, "room for testing", "find_room_from_path() test: room found from path has incorrect short description!");

    cr_assert_str_eq(found_room->long_desc, "room for testing find_room_from_path()", "find_room_from_path() test: room found from path has incorrect long description!");
}
