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

// TESTS FOR ADD_ATRR_TO_HASH --------------------------------------------------

Test(attribute, add_attr_to_hash_success)
{
    item_t *test_item = item_new();
    int fill_item = item_init(test_item, "test_item", "test item for attributes", "item for testing add_attr_to_hash");

    cr_assert_eq(fill_item, SUCCESS, "add_attribute_to_hash() test: item initialization failed!");

    attribute_t *test_attr = malloc(sizeof(attribute_t));
    test_attr->attribute_key = (char*)malloc(100);
    test_attr->attribute_key = "test_attr";
    test_attr->attribute_tag = STRING;
    test_attr->attribute_value.str_val = "test";

    int test = add_attribute_to_hash(test_item, test_attr);

    cr_assert_eq(test, SUCCESS, "add_attr_to_hash() test failed!");


}


Test(attribute, add_attr_to_hash_failure)
{
    item_t *test_item = item_new();
    int fill_item = item_init(test_item, "test_item", "test item for attributes", "item for testing add_attr_to_hash");

    cr_assert_eq(fill_item, SUCCESS, "add_attribute_to_hash() test: item initialization failed!");

    attribute_t *test_attr = malloc(sizeof(attribute_t));
    test_attr->attribute_key = (char*)malloc(100);
    test_attr->attribute_key = "test_attr";
    test_attr->attribute_tag = STRING;
    test_attr->attribute_value.str_val = "test";

    int setup = add_attribute_to_hash(test_item, test_attr);
    cr_assert_eq(setup, SUCCESS, "add_attr_to_hash() test setup failed!");

    int test = add_attribute_to_hash(test_item, test_attr);
    cr_assert_eq(test, FAILURE, "add_attr_to_hash() test failed: duplicate attribute added");


}


// TEST FOR GENERAL GET_ATTRIBUTE()--------------------------------------------
Test(attribute, get_attribute)
{
    item_t *test_item = item_new();
    int fill_item = item_init(test_item, "test_item", "test item for attributes", "item for testing get_attribute()");

    cr_assert_eq(fill_item, SUCCESS, "get_attribute() test: item initialization failed!");

    int test_attr1 = set_str_attr(test_item, "door", "locked");
    int test_attr2 = set_int_attr(test_item, "# of weapons", 1);

    cr_assert_eq(test_attr1, SUCCESS, "get_attr(): adding attr1 failed!");
    cr_assert_eq(test_attr2, SUCCESS, "get_attr(): adding attr2 failed!");

    attribute_t *my_attr = get_attribute(test_item, "door");

    cr_assert_str_eq(my_attr->attribute_key, "door", "get_attr(): wrong key!");
    cr_assert_str_eq(my_attr->attribute_value.str_val, "locked", "get_attr(): wrong value!");
}

// TESTS FOR TYPE-SPECIFIC SET_ATTR() FUNCTIONS -------------------------------
Test(attribute, set_str_attr)
{
	item_t *test_item = item_new();
	int rv = set_str_attr(test_item, "Attribute_Test_Name", "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
	char* test_str = test_attr->attribute_value.str_val;
	cr_assert_str_eq(test_str, "Attribute_Test_Value", "change_str_attr: set the wrong value");
}

Test(attribute, set_int_attr)
{
	item_t *test_item = item_new();
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
	cr_assert_eq(rv, SUCCESS, "set_int_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "set_int_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "set_int_attribute: null attribute returned");
	int test_int = test_attr->attribute_value.int_val;
	cr_assert_eq(test_int, 2, "set_int_attribute: set the wrong value");
}

Test(attribute, set_double_attr)
{
	item_t *test_item = item_new();
	int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
	cr_assert_eq(rv, SUCCESS, "change_double_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_double_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_double_attribute: null attribute returned");
	double test_double = test_attr->attribute_value.double_val;
	cr_assert_float_eq(test_double, 2.0, 0.001, "change_double_attribute: set the wrong value");
}

Test(attribute, set_char_attr)
{
	item_t *test_item = item_new();
	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
	cr_assert_eq(rv, SUCCESS, "change_char_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_char_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_char_attribute: null attribute returned");
	char test_char = test_attr->attribute_value.char_val;
	cr_assert_eq(test_char, 'a', "change_char_attribute: set the wrong value");
}

Test(attribute, set_bool_attr)
{
	item_t *test_item = item_new();
	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
	cr_assert_eq(rv, SUCCESS, "change_bool_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_bool_attribute: no elements added to hash");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_bool_attribute: null attribute returned");
	bool test_bool = test_attr->attribute_value.bool_val;
	cr_assert_eq(test_bool, true, "change_bool_attribute: set the wrong value");
}


// TESTS FOR TYPE-SPECIFIC CHANGE_ATTR() FUNCTIONS ----------------------------
Test(attribute, change_str_attr)
{
	item_t *test_item = item_new();
	int rv = set_str_attr(test_item, "Attribute_Test_Name", "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	rv = set_str_attr(test_item, "Attribute_Test_Name", "Attribute_Test_Value_2");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
	char* test_str = test_attr->attribute_value.str_val;
	cr_assert_str_eq(test_str, "Attribute_Test_Value_2", "change_str_attr: changed to the wrong value");
}

Test(attribute, change_int_attr)
{
	item_t *test_item = item_new();
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
	cr_assert_eq(rv, SUCCESS, "set_int_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "set_int_attribute: no elements added to hash");
	rv = set_int_attr(test_item, "Attribute_Test_Name", 3);
	cr_assert_eq(rv, SUCCESS, "set_int_attribute: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "set_int_attribute: null attribute returned");
	int test_int = test_attr->attribute_value.int_val;
	cr_assert_eq(test_int, 3, "set_int_attribute: set the wrong value");
}

Test(attribute, change_double_attr)
{
	item_t *test_item = item_new();
	int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
	cr_assert_eq(rv, SUCCESS, "change_double_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_double_attribute: no elements added to hash");
	rv = set_double_attr(test_item, "Attribute_Test_Name", 2.5);
	cr_assert_eq(rv, SUCCESS, "change_double_attribute: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_double_attribute: null attribute returned");
	double test_double = test_attr->attribute_value.double_val;
	cr_assert_float_eq(test_double, 2.5, 0.0001, "change_double_attribute: set the wrong value");

}

Test(attribute, change_char_attr)
{
	item_t *test_item = item_new();
	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
	cr_assert_eq(rv, SUCCESS, "change_char_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_char_attribute: no elements added to hash");
	rv = set_char_attr(test_item, "Attribute_Test_Name", 'b');
	cr_assert_eq(rv, SUCCESS, "change_char_attribute: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_char_attribute: null attribute returned");
	char test_char = test_attr->attribute_value.char_val;
	cr_assert_eq(test_char, 'b', "change_char_attribute: set the wrong value");
}

Test(attribute, change_bool_attr)
{
	item_t *test_item = item_new();
	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
	cr_assert_eq(rv, SUCCESS, "change_bool_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_bool_attribute: no elements added to hash");
	rv = set_bool_attr(test_item, "Attribute_Test_Name", false);
	cr_assert_eq(rv, SUCCESS, "change_bool_attribute: did not successfully change attr");
	attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
	cr_assert_not_null(test_attr, "change_bool_attribute: null attribute returned");
	bool test_bool = test_attr->attribute_value.bool_val;
	cr_assert_eq(test_bool, false, "change_bool_attribute: set the wrong value");
}



//write tests for changing a attr of the wrong type

// TESTS FOR TYPE-SPECIFIC GET_ATTR() FUNCTIONS -------------------------------
Test(attribute, get_str_attr)
{
	item_t *test_item = item_new();
	int rv = set_str_attr(test_item, "Attribute_Test_Name", "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	char* test_str = get_str_attr(test_item, "Attribute_Test_Name");
	cr_assert_str_eq(test_str, "Attribute_Test_Value", "change_str_attr: set the wrong value");
}

Test(attribute, get_int_attr)
{
	item_t *test_item = item_new();
	int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
	cr_assert_eq(rv, SUCCESS, "set_int_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "set_int_attribute: no elements added to hash");
	int test_int = get_int_attr(test_item, "Attribute_Test_Name");
	cr_assert_eq(test_int, 2, "set_int_attribute: set the wrong value");
}

Test(attribute, get_double_attr)
{
	item_t *test_item = item_new();
	int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
	cr_assert_eq(rv, SUCCESS, "change_double_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_double_attribute: no elements added to hash");
	double test_double = get_double_attr(test_item, "Attribute_Test_Name");
	cr_assert_float_eq(test_double, 2.0, 0.001, "change_double_attribute: set the wrong value");
}

Test(attribute, get_char_attr)
{
	item_t *test_item = item_new();
	int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
	cr_assert_eq(rv, SUCCESS, "change_char_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_char_attribute: no elements added to hash");
	char test_char = get_char_attr(test_item, "Attribute_Test_Name");
	cr_assert_eq(test_char, 'a', "change_char_attribute: set the wrong value");
}

Test(attribute, get_bool_attr)
{
	item_t *test_item = item_new();
	int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
	cr_assert_eq(rv, SUCCESS, "change_bool_attribute: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_bool_attribute: no elements added to hash");
	bool test_bool = get_bool_attr(test_item, "Attribute_Test_Name");
	cr_assert_eq(test_bool, true, "change_bool_attribute: set the wrong value");
}

Test(attribute, get_false_str_attr, .exit_code = 1) {
	item_t *test_item = item_new();
	int rv = set_str_attr(test_item, "Attribute_Test_Name", "Attribute_Test_Value");
	cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
	int num_in_hash = HASH_COUNT(test_item->attributes);
	cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
	bool test_str = get_bool_attr(test_item, "Attribute_Test_Name");
}


// TEST FOR ATTRIBUTES_EQUAL()-------------------------------------------------

Test(attribute, equal)
{
    item_t *item1 = item_new();
    item_t *item2 = item_new();
    item_init(item1, "test_item1", "attribute test", "testing equality of attributes");
    item_init(item2, "test_item2", "attribute test", "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test");
    set_str_attr(item2, "test_attr", "test");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, 1, "attributes_equal() test failed!");


}

Test(attribute, not_equal)
{
    item_t *item1 = item_new();
    item_t *item2 = item_new();
    item_init(item1, "test_item1", "attribute test", "testing equality of attributes");
    item_init(item2, "test_item2", "attribute test", "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_str_attr(item2, "test_attr", "test2");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, 0, "attributes_equal() test failed!");


}

Test(attribute, null_attr)
{
    item_t *item1 = item_new();
    item_t *item2 = item_new();
    item_init(item1, "test_item1", "attribute test", "testing equality of attributes");
    item_init(item2, "test_item2", "attribute test", "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    // set_str_attr(item2, "test_attr", "test2");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1, "attributes_equal() test failed: neither of the attributes are NULL");


}

Test(attribute, not_equal_types)
{
    item_t *item1 = item_new();
    item_t *item2 = item_new();
    item_init(item1, "test_item1", "attribute test", "testing equality of attributes");
    item_init(item2, "test_item2", "attribute test", "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_int_attr(item2, "test_attr", 1);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1, "attributes_equal() test failed: attributes are of the same type");

}

// TEST FOR ATTRIBUTE_FREE() --------------------------------------------------
