#include <stdio.h>
#include <criterion/criterion.h>
#include "item.c"

// BASIC ITEM UNIT TESTS ------------------------------------------------------
Test(item, new)
{
  item_t *new_item = item_new();

  cr_assert_not_null(new_item, "item_new() test 1 has failed!");

}

Test(item, init)
{
  item_t *empty_item = item_new();
  int check = item_init(empty_item, "test_item", "This is a test item",
  "The purpose of this item is testing");

  cr_assert_eq(check, SUCCESS, "item_new() test 1 has failed!");
}

Test(item, free)
{
  item_t *item_tofree = item_new();
  int init = item_init(item_tofree, "my_item", "pls free me",
  "this item needs to be freed");

  cr_assert_eq(init, SUCCESS, "item_free test 1: item init failed!");

  int freed = item_free(item_tofree);

  cr_assert_eq(freed, SUCCESS, "item_free() test 1 has failed!");


}

// 
