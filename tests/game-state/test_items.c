#include <stdio.h>
#include <criterion/criterion.h>
#include "game-state/item.h"

#include "game-state/player.h"

#include "game-state/item.h"
#include "game-state/room.h"

// BASIC ITEM UNIT TESTS ------------------------------------------------------

/* Checks creation of new item */
Test(item, new)
{
    item_t *new_item = item_new("test_item", "item for testing",
    "test item for item_new()");

    cr_assert_not_null(new_item, "item_new() test 1 has failed!");

}

/* Checks initialization of new item */
Test(item, init)
{
    item_t *empty_item = item_new("test_item", "This is a test item",
    "The purpose of this item is testing");
    int check = item_init(empty_item, "test_item", "This is a test item",
    "The purpose of this item is testing");

    cr_assert_eq(check, SUCCESS, "item_new() test 1 has failed!");
}

/* Checks freeing of item struct */
Test(item, free)
{
    item_t *item_tofree = item_new("my_item", "pls free me",
    "this item needs to be freed");
    int init = item_init(item_tofree, "my_item", "pls free me",
    "this item needs to be freed");

    cr_assert_eq(init, SUCCESS, "item_free test 1: item init failed!");

    int freed = item_free(item_tofree);

    cr_assert_eq(freed, SUCCESS, "item_free() test 1 has failed!");


}

/* Checks return of short description of item */
Test(item, get_sdesc_item)
{
  item_t *new_item = item_new("item", "short", "long");
  item_t *null_item = NULL;
  
  char *ret = get_sdesc_item(new_item);
  char *null_ret = get_sdesc_item(null_item);

  cr_assert_eq(ret, new_item->short_desc, "get_sdesc_item() failed to \
return short description");
  cr_assert_eq(null_ret, NULL, "get_sdesc_item() failed to return NULL\
 for NULL item");
}

/* Checks return of long description of item */
Test(item, get_ldesc_item)
{
  item_t *new_item = item_new("item", "short", "long");
  item_t *null_item = NULL;

  char *ret = get_ldesc_item(new_item);
  char *null_ret = get_ldesc_item(null_item);

  cr_assert_eq(ret, new_item->long_desc, "get_ldesc_item() failed to \
return long description");
  cr_assert_eq(null_ret, NULL, "get_ldesc_item() failed to return NULL\
 for NULL item");
}

// TESTS FOR ADD_ATRR_TO_HASH --------------------------------------------------

/* Checks adding attribute to item hash */
Test(attribute, add_attr_to_hash_success)
{
    item_t *test_item = item_new("test_item", "test item for attributes",
    "item for testing add_attr_to_hash");

    attribute_t *test_attr = malloc(sizeof(attribute_t));
    test_attr->attribute_key = (char*)malloc(100);
    test_attr->attribute_key = "test_attr";
    test_attr->attribute_tag = STRING;
    test_attr->attribute_value.str_val = "test";

    int test = add_attribute_to_hash(test_item, test_attr);

    cr_assert_eq(test, SUCCESS, "add_attr_to_hash() test failed!");

}

/* Checks if adding same attribute to item hash twice fails */
Test(attribute, add_attr_to_hash_failure)
{
    item_t *test_item = item_new("test_item", "test item for attributes",
    "item for testing add_attr_to_hash");

    attribute_t *test_attr = malloc(sizeof(attribute_t));
    test_attr->attribute_key = (char*)malloc(100);
    test_attr->attribute_key = "test_attr";
    test_attr->attribute_tag = STRING;
    test_attr->attribute_value.str_val = "test";

    int setup = add_attribute_to_hash(test_item, test_attr);
    cr_assert_eq(setup, SUCCESS, "add_attr_to_hash() test setup failed!");

    int test = add_attribute_to_hash(test_item, test_attr);
    cr_assert_eq(test, FAILURE,
        "add_attr_to_hash() test failed: duplicate attribute added");

}


// TEST FOR GENERAL GET_ATTRIBUTE()---------------------------------------------

/* Checks helper function to retrieve attribute from item */
Test(attribute, get_attribute)
{
    item_t *test_item = item_new("test_item", "test item for attributes",
    "item for testing get_attribute()");

    int test_attr1 = set_str_attr(test_item, "door", "locked");
    int test_attr2 = set_int_attr(test_item, "# of weapons", 1);

    cr_assert_eq(test_attr1, SUCCESS, "get_attr(): adding attr1 failed!");
    cr_assert_eq(test_attr2, SUCCESS, "get_attr(): adding attr2 failed!");

    attribute_t *my_attr = get_attribute(test_item, "door");

    cr_assert_str_eq(my_attr->attribute_key, "door", "get_attr(): wrong key!");
    cr_assert_str_eq(my_attr->attribute_value.str_val, "locked",
    "get_attr(): wrong value!");

}

// TESTS FOR TYPE-SPECIFIC SET_ATTR() FUNCTIONS --------------------------------

/* Checks creation of new string attribute and adding it to an item */
Test(attribute, set_str_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_str_attr(test_item, "Attribute_Test_Name", "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
	char* test_str = test_attr->attribute_value.str_val;
	cr_assert_str_eq(test_str, "Attribute_Test_Value",
    "change_str_attr: set the wrong value");

}

/* Checks creation of new integer attribute and adding it to an item */
Test(attribute, set_int_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
	cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "set_int_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "set_int_attribute: null attribute returned");
	int test_int = test_attr->attribute_value.int_val;
	cr_assert_eq(test_int, 2, "set_int_attribute: set the wrong value");

}

/* Checks creation of new double attribute and adding it to an item */
Test(attribute, set_double_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
	cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_double_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr,
        "change_double_attribute: null attribute returned");
	double test_double = test_attr->attribute_value.double_val;
	cr_assert_float_eq(test_double, 2.0, 0.001,
        "change_double_attribute: set the wrong value");

}

/* Checks creation of new character attribute and adding it to an item */
Test(attribute, set_char_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
	cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_char_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr,
        "change_char_attribute: null attribute returned");
	char test_char = test_attr->attribute_value.char_val;
	cr_assert_eq(test_char, 'a', "change_char_attribute: set the wrong value");

}

/* Checks creation of new boolean attribute and adding it to an item */
Test(attribute, set_bool_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
	cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_bool_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr,
        "change_bool_attribute: null attribute returned");
	bool test_bool = test_attr->attribute_value.bool_val;
	cr_assert_eq(test_bool, true, "change_bool_attribute: set the wrong value");

}

// TESTS FOR TYPE-SPECIFIC SET_ATTR() FUNCTIONS CHANGING ATTR VALUE ------------------------

/* Checks creation of new string attribute and changing its value */
Test(attribute, change_str_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value_2");
	cr_assert_eq(rv, SUCCESS,
        "change_str_attr: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
	char* test_str = test_attr->attribute_value.str_val;
	cr_assert_str_eq(test_str, "Attribute_Test_Value_2",
    "change_str_attr: changed to the wrong value");

}

/* Checks creation of new str attribute and if change to non-str is blocked */
Test(attribute, change_str_attr_fail)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");

	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");

	rv = set_int_attr(test_item, "Attribute_Test_Name", 3);
	cr_assert_eq(rv, FAILURE,
        "change_str_attr: string attr was wrongfully overwritten");

	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
	char* test_str = test_attr->attribute_value.str_val;
	cr_assert_str_eq(test_str, "Attribute_Test_Value",
    "change_str_attr: changed to a non-string type");

}

/* Checks creation of new string attribute and changing its value */
Test(attribute, change_int_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
	cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "set_int_attribute: no elements added to hash");
	rv = set_int_attr(test_item, "Attribute_Test_Name", 3);
	cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "set_int_attribute: null attribute returned");
	int test_int = test_attr->attribute_value.int_val;
	cr_assert_eq(test_int, 3, "set_int_attribute: set the wrong value");

}

/* Checks creation of new int attribute and if change to non-int is blocked */
Test(attribute, change_int_attr_fail)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 5);

	cr_assert_eq(rv, SUCCESS, "change_int_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_int_attr: no elements added to hash");

	rv = set_str_attr(test_item, "Attribute_Test_Name", "five");
	cr_assert_eq(rv, FAILURE,
        "change_int_attr: integer attr was wrongfully overwritten");

	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_int_attr: null attribute returned");
	int test_int = test_attr->attribute_value.int_val;
	cr_assert_eq(test_int, 5, "change_int_attr: changed to a non-integer type");

}

/* Checks creation of new double attribute and changing its value */
Test(attribute, change_double_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
	cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_double_attribute: no elements added to hash");
	rv = set_double_attr(test_item, "Attribute_Test_Name", 2.5);
	cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr,
        "change_double_attribute: null attribute returned");
	double test_double = test_attr->attribute_value.double_val;
	cr_assert_float_eq(test_double, 2.5, 0.0001,
        "change_double_attribute: set the wrong value");

}

/* Checks creation of new dbl attribute and if change to non-dbl is blocked */
Test(attribute, change_double_attr_fail)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_double_attr(test_item, "Attribute_Test_Name", 5.0);

	cr_assert_eq(rv, SUCCESS,
        "change_double_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_double_attr: no elements added to hash");

	rv = set_str_attr(test_item, "Attribute_Test_Name", "five");
	cr_assert_eq(rv, FAILURE,
        "change_double_attr: double attr was wrongfully overwritten");

	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr,
        "change_double_attr: null attribute returned");
	double test_double = test_attr->attribute_value.double_val;
	cr_assert_eq(test_double, 5.0,
        "change_double_attr: changed to a non-double type");

}

/* Checks creation of new character attribute and changing its value */
Test(attribute, change_char_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
	cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_char_attribute: no elements added to hash");
	rv = set_char_attr(test_item, "Attribute_Test_Name", 'b');
	cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr,
        "change_char_attribute: null attribute returned");
	char test_char = test_attr->attribute_value.char_val;
	cr_assert_eq(test_char, 'b', "change_char_attribute: set the wrong value");

}

/* Checks creation of new char attribute and if change to non-char is blocked */
Test(attribute, change_char_attr_fail)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'x');

	cr_assert_eq(rv, SUCCESS,
        "change_char_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_char_attr: no elements added to hash");

	rv = set_int_attr(test_item, "Attribute_Test_Name", 8);
	cr_assert_eq(rv, FAILURE,
        "change_char_attr: char attr was wrongfully overwritten");

	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_char_attr: null attribute returned");
	char test_char = test_attr->attribute_value.char_val;
	cr_assert_eq(test_char, 'x',
    "change_char_attr: changed to a non-char type");

}

/* Checks creation of new boolean attribute and changing its value */
Test(attribute, change_bool_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
	cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully set attr");

	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_bool_attribute: no elements added to hash");

	rv = set_bool_attr(test_item, "Attribute_Test_Name", false);
	cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully change attr");

	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr,
        "change_bool_attribute: null attribute returned");

	bool test_bool = test_attr->attribute_value.bool_val;
	cr_assert_eq(test_bool, false,
        "change_bool_attribute: set the wrong value");

}

/* Checks creation of new bool attribute and if change to non-bool is blocked */
Test(attribute, change_bool_attr_fail)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);

	cr_assert_eq(rv, SUCCESS,
        "change_bool_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_bool_attr: no elements added to hash");

	rv = set_int_attr(test_item, "Attribute_Test_Name", 8);
	cr_assert_eq(rv, FAILURE,
        "change_bool_attr: bool attr was wrongfully overwritten");

	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_bool_attr: null attribute returned");

	bool test_bool = test_attr->attribute_value.bool_val;
	cr_assert_eq(test_bool, true,
        "change_bool_attr: changed to a non-bool type");

}


// TESTS FOR TYPE-SPECIFIC GET_ATTR() FUNCTIONS -------------------------------

/* Checks retrieval of string attribute value */
Test(attribute, get_str_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
	int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	char* test_str = get_str_attr(test_item, "Attribute_Test_Name");
	cr_assert_str_eq(test_str, "Attribute_Test_Value",
    "change_str_attr: set the wrong value");

}

/* Checks retrieval of integer attribute value */
Test(attribute, get_int_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
	cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "set_int_attribute: no elements added to hash");
	int test_int = get_int_attr(test_item, "Attribute_Test_Name");
	cr_assert_eq(test_int, 2, "set_int_attribute: set the wrong value");

}

/* Checks retrieval of double attribute value */
Test(attribute, get_double_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
	int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
	cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_double_attribute: no elements added to hash");
	double test_double = get_double_attr(test_item, "Attribute_Test_Name");
	cr_assert_float_eq(test_double, 2.0, 0.001,
        "change_double_attribute: set the wrong value");

}

/* Checks retrieval of character attribute value */
Test(attribute, get_char_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
	cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_char_attribute: no elements added to hash");
	char test_char = get_char_attr(test_item, "Attribute_Test_Name");
	cr_assert_eq(test_char, 'a', "change_char_attribute: set the wrong value");

}

/* Checks retrieval of boolean attribute value */
Test(attribute, get_bool_attr)
{
	item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
	cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0,
        "change_bool_attribute: no elements added to hash");
	bool test_bool = get_bool_attr(test_item, "Attribute_Test_Name");
	cr_assert_eq(test_bool, true, "change_bool_attribute: set the wrong value");

}


/* Checks if retrieval of non-str attribute using get_str_attr is blocked */
Test(attribute, get_non_str_attr) {
	item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);

	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);

	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	char *check = get_str_attr(test_item, "Attribute_Test_Name");

    cr_assert_null(check, "get_non_str_attr() test: incorrect finding");
}

/* Checks if retrieval of non-int attribute using get_int_attr is blocked */
Test(attribute, get_non_int_attr) {
	item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

	int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	int check = get_int_attr(test_item, "Attribute_Test_Name");

    cr_assert_eq(check, -1, "get_non_int_attr() test: incorrect finding");


}

/* checks if retrieval of non-double attribute using get_double_attr is blocked */
Test(attribute, get_non_double_attr) {
	item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	double check = get_double_attr(test_item, "Attribute_Test_Name");

    cr_assert_float_eq(check, -1.0, 0.001,
        "change_double_attr: incorrect finding");
}

/* Checks if retrieval of non-character attribute using get_char_attr is blocked */
Test(attribute, get_non_char_attr) {
	item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	char check = get_char_attr(test_item, "Attribute_Test_Name");

    cr_assert_eq(check, '~', "get_non_char_attr() test: incorrect finding");
}

/* Checks if retrieval of non-boolean attribute using get_bool_attr is blocked */
Test(attribute, get_non_bool_attr) {
	item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

	int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	bool check = get_bool_attr(test_item, "Attribute_Test_Name");

    cr_assert_null(check, "get_non_bool_attr() test: incorrect finding");
}

// TEST FOR ATTRIBUTES_EQUAL()-------------------------------------------------

/* checks that two equal attributes are equal */
Test(attribute, equal)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test");
    set_str_attr(item2, "test_attr", "test");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, SUCCESS, "attributes_equal() test failed!");

}

/* checks that two unequal attributes are not equal */
Test(attribute, not_equal)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_str_attr(item2, "test_attr", "test2");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, FAILURE, "attributes_equal() test failed!");

}

/* checks that function catches if one of the attributes being compared
is NULL */
Test(attribute, null_attr)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: neither of the attributes are NULL");

}

/* the following tests check that function catches if the attributes being compared are of different types  */

// str + int
Test(attribute_equal, str_to_int)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_int_attr(item2, "test_attr", 1);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// str + char
Test(attribute_equal, str_to_char)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_char_attr(item2, "test_attr", 'x');

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// str + double
Test(attribute_equal, str_to_double)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_double_attr(item2, "test_attr", 2.0);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// str + bool
Test(attribute_equal, str_to_bool)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_bool_attr(item2, "test_attr", true);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// int + char
Test(attribute_equal, int_to_char)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_int_attr(item1, "test_attr", 1);
    set_char_attr(item2, "test_attr", 'x');

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// int + double
Test(attribute_equal, int_to_double)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_int_attr(item1, "test_attr", 1);
    set_double_attr(item2, "test_attr", 2.0);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// int + bool
Test(attribute_equal, int_to_bool)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_int_attr(item1, "test_attr", 1);
    set_bool_attr(item2, "test_attr", true);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// char + double
Test(attribute_equal, char_to_double)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_char_attr(item1, "test_attr", 'x');
    set_double_attr(item2, "test_attr", 2.0);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// char + bool
Test(attribute_equal, char_to_bool)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_char_attr(item1, "test_attr", 'x');
    set_bool_attr(item2, "test_attr", true);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");

}

// TEST FOR ATTRIBUTE_FREE() --------------------------------------------------

/* Checks freeing of attribute struct */
Test(attribute, attr_free)
{
    attribute_t *test_attr = (attribute_t*)malloc(sizeof(attribute_t));

    test_attr->attribute_key = malloc(sizeof(char)*100);
    test_attr->attribute_tag = INTEGER;
    test_attr->attribute_value.int_val = 5;

    int test = attribute_free(test_attr);

    cr_assert_eq(test, SUCCESS, "attribute_free() test failed!");

}

// TESTS FOR HASH DELETION ----------------------------------------------------

/* Checks deletion of all attributes associated with an item struct */
Test(attribute, deletion)
{
    item_t *test_item = item_new("test_item", "item for attr testing",
    "item for testing del_all_attr function");

    set_str_attr(test_item, "test1", "this is a test");
    set_int_attr(test_item, "open", 1);
    set_double_attr(test_item, "battery", 0.75);


    int test = delete_all_attributes(test_item->attributes);

    cr_assert_eq(test, SUCCESS, "delete_all_attributes() test failed!");

}

/* Checks deletion of all items within a room struct */
Test(item, deletion_in_room)
{
    room_t *test_room = room_new("test_room", "room for item testing",
    "room for testing item deletion");
    item_t *test_item1 = item_new("hat", "fedora", "Indiana Jones vibes");
    item_t *test_item2 = item_new("lightsaber", "weapon",
    "star wars vibes, it's a crossover episode");
    item_t *test_item3 = item_new("apple", "fujis are the best",
    "a player's gotta nourish");

    int item_add1 = add_item_to_room(test_room, test_item1);
    int item_add2 = add_item_to_room(test_room, test_item2);
    int item_add3 = add_item_to_room(test_room, test_item3);

    cr_assert_eq(item_add1, SUCCESS,
        "del_all_items test: item1 was not added!");
    cr_assert_eq(item_add2, SUCCESS,
        "del_all_items test: item2 was not added!");
    cr_assert_eq(item_add3, SUCCESS,
        "del_all_items test: item3 was not added!");

    int del_items = delete_all_items(&test_room->items);
    cr_assert_eq(del_items, SUCCESS,
        "del_all_items test: items were not successfully deleted!");


}

/* Checks deletion of all items within a player struct */
Test(item, deletion_in_player)
{
    player_t *test_player = player_new("test_player", 100);
    item_t *test_item1 = item_new("hat", "fedora", "Indiana Jones vibes");
    item_t *test_item2 = item_new("lightsaber", "weapon",
    "star wars vibes, it's a crossover episode");
    item_t *test_item3 = item_new("apple", "fujis are the best",
    "a player's gotta nourish");

    int item_add1 = add_item_to_player(test_player, test_item1);
    int item_add2 = add_item_to_player(test_player, test_item2);
    int item_add3 = add_item_to_player(test_player, test_item3);

    cr_assert_eq(item_add1, SUCCESS,
        "del_all_items test: item1 was not added!");
    cr_assert_eq(item_add2, SUCCESS,
        "del_all_items test: item2 was not added!");
    cr_assert_eq(item_add3, SUCCESS,
        "del_all_items test: item3 was not added!");

    int del_items = delete_all_items(&test_player->inventory);
    cr_assert_eq(del_items, SUCCESS,
        "del_all_items test: items were not successfully deleted!");


}
