#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "room.h"

// BASIC ROOM UNIT TESTS ------------------------------------------------------
Test(room, new)
{
  room_t *new_room = room_new("test_room", "room for testing", "testing if memory is correctly allocated for new rooms");

  cr_assert_not_null(new_room, "room_new() test 1 has failed!");

}

Test(room, init)
{
  room_t *empty_room = room_new("test_room", "This is a test room",
  "The purpose of this room is testing");
  int check = room_init(empty_room, "test_room", "This is a test room",
  "The purpose of this room is testing");

  cr_assert_eq(check, SUCCESS, "room_new() test 1 has failed!");
}

Test(room, free)
{
  room_t *room_tofree = room_new("test_room", "room for testing", "testing if memory is correctly freed for rooms");

  cr_assert_not_null(room_tofree, "room_free(): room is null");
  int freed = room_free(room_tofree);

  cr_assert_eq(freed, SUCCESS, "room_free() test 1 has failed!");


}

/* Checks if get_item_in_room() correctly retrieves an item in room*/
Test(room, get_item)
{
    room_t *new_room = room_new("test_room", "room for testing", "testing if memory is correctly allocated for new rooms");
    item_t *test_item = item_new("test_item", "item for testing", "testing to see if get_item() works");
    int rv = add_item_to_room(new_room, test_item);
    cr_assert_eq(rv, SUCCESS, "item not added to room correctly");
    item_t *returned_item = get_item_in_room(new_room, "test_item");
    cr_assert_eq(test_item, returned_item, "item not added to room correctly");

}

/* Checks if get_item_in_room() returns NULL when searching non-existent item*/
Test(room, get_nonexistent_item)
{
    room_t *new_room = room_new("test_room", "room for testing", "testing if memory is correctly allocated for new rooms");
    item_t *test_item = item_new("test_item", "item for testing", "testing to see if get_item() works");
    int rv = add_item_to_room(new_room, test_item);
    cr_assert_eq(rv, SUCCESS, "item not added to room correctly");
    item_t *returned_item = get_item_in_room(new_room, "test_item_2");
    cr_assert_null(returned_item, "Item retrieved but should be NULL");

}
