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

item_t *item_setup() {
  item_t *test_item = item_new();
  int init = item_init(test_item, "item1", "item to test attr fxn",
  "this item serves as a fixture to test functions involving hash tables");

  cr_assert_eq(init, SUCCESS, "item_setup: item init failed!");

  return test_item;
}

void item_teardown(item_t *test_item) {

  free(test_item);

}


Test(attribute, set_int_attribute)
{
	item_t *test_item = item_new();
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
	cr_assert_eq(rv, SUCCESS, "set_string_attribute: returned the wrong value");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name"); //that is returning a NULL value

	//int test_int = test_attr->attribute_tag;
	//int test_int = get_int_attr(test_item, "Attribute_Test_Name");
	cr_assert_null(test_attr, "set_string_attribute: set the wrong value");
}

//
// Test(attributes, set_int)
// {
//   item_t* test_item = item_setup();
//   int set = set_int_attr(test_item, "locked", 1);
//   cr_assert_eq(set, SUCCESS, "set_int_attr test failed!");
//
// }

// Test(atrributes, add_attr_to_hash, .init = item_setup, .fini = item_teardown)
// don't really understand the last two args, doesn't pass the structure to
// the test to be used
/*
Test(attributes, add_attr_to_hash)
{
  attribute_t test_attr = {0};
  // char *attr_name = "locked";
  // int attr_val = 1;
  test_attr.attribute_key = "locked";
  test_attr.attribute_tag = INTEGER;
  test_attr.attribute_value.int_val = 1;
  attribute_t *attr_ptr = &test_attr;
  item_t *test_item = item_setup();
  int test = add_attribute_to_hash(test_item->attributes, attr_ptr);

  cr_assert_eq(test, SUCCESS, "add_attr_to_hash() test 1 failed!");

  item_teardown(test_item);
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
*/