#include <stdio.h>
#include <criterion/criterion.h>
#include "item.h"
#include "common-item.h"

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

Test(item, get_attribute_exists)
{
	item_t *new_item = item_new();
	attribute_t* new_attribute = malloc(sizeof(attribute_t));
    new_attribute->attribute_tag = STRING;
    new_attribute->attribute_value.str_val = "This is a value";
    new_attribute->attribute_key = "Attribute";
    int rv = add_attribute_to_hash(new_item->attributes, new_attribute);
    rv ++;
    //attribute_t* found_atttribute = get_attribute(new_item, "Attribute");
    //cr_assert_str_eq(new_attribute->attribute_value.str_val, found_atttribute->attribute_value.str_val, "get_attribute() has failed!");

}

// 
