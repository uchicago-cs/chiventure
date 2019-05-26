#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "room.h"

// BASIC ROOM UNIT TESTS ------------------------------------------------------
Test(room, new)
{
  room_t *new_room = room_new("test_room", "room for testing",
  "testing if memory is correctly allocated for new rooms");

  cr_assert_not_null(new_room, "room_new() test 1 has failed!");

}

// Test(room, free)
// {
//   item_t *item_tofree = item_new();
//   int init = item_init(item_tofree, "my_item", "pls free me",
//   "this item needs to be freed");
//
//   cr_assert_eq(init, SUCCESS, "item_free test 1: item init failed!");
//
//   int freed = item_free(item_tofree);
//
//   cr_assert_eq(freed, SUCCESS, "item_free() test 1 has failed!");
//
//
// }
