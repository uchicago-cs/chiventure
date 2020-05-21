#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_items.h"
#include "../../include/openworld/sample_rooms.h"

/* Tests the functions in sample_items.h */

/* Test fix_item_new function for APPLE */
Test(item, new1)
{
	fix_item_t *i;

	i = fix_item_new(APPLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	cr_assert_str_eq(i->item->item_id, "apple", "fix_item_new() didn't set item_id");
	cr_assert_eq(i->item_tag, APPLE, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(i->item->long_desc, "A juicy Red Delicious apple", 
		"fix_item_new() didn't set long_desc");
	cr_assert_str_eq(i->item->short_desc, "a red apple", 
		"fix_item_new() didn't set short_desc");
}

/* Test fix_item_new function for KETTLE */
Test(item, new2)
{
	fix_item_t *i;

	i = fix_item_new(KETTLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	cr_assert_str_eq(i->item->item_id, "kettle", "fix_item_new() didn't set item_id");
	cr_assert_eq(i->item_tag, KETTLE, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(i->item->long_desc, "A black kettle on a stove",
		"fix_item_new() didn't set long_desc");
	cr_assert_str_eq(i->item->short_desc, "a black kettle",
		"fix_item_new() didn't set short_desc");
}

/* Test fix_item_init function for APPLE */
Test(item, init1)
{
	fix_item_t *i;
	int rc;

	rc = fix_item_init(i, APPLE);

	cr_assert_eq(rc, SUCCESS, "fix_item_init() failed");

	cr_assert_str_eq(i->item->item_id, "apple", "fix_item_new() didn't set item_id");
	cr_assert_eq(i->item_tag, APPLE, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(i->item->long_desc, "A juicy Red Delicious apple",
		"fix_item_new() didn't set long_desc");
	cr_assert_str_eq(i->item->short_desc, "a red apple",
		"fix_item_new() didn't set short_desc");
}

/* Test fix_item_init function for KETTLE */
Test(item, init2)
{
	fix_item_t *i;
	int rc;

	rc = fix_item_init(i, KETTLE);

	cr_assert_eq(rc, SUCCESS, "fix_item_init() failed");

	cr_assert_str_eq(i->item->item_id, "kettle", "fix_item_new() didn't set item_id");
	cr_assert_eq(i->item_tag, KETTLE, "fix_item_new() didn't set item_tag");
	cr_assert_str_eq(i->item->long_desc, "A black kettle on a stove",
		"fix_item_new() didn't set long_desc");
	cr_assert_str_eq(i->item->short_desc, "a black kettle",
		"fix_item_new() didn't set short_desc");
}

/* Test fix_item_free function for APPLE */
Test(item, free1)
{
	fix_item_t* i;
	int rc;

	i = fix_item_new(APPLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	rc = fix_item_free(i);

	cr_assert_eq(rc, SUCCESS, "fix_item_free() failed");
}

/* Test fix_item_free function for KETTLE */
Test(item, free2)
{
	fix_item_t* i;
	int rc;

	i = fix_item_new(KETTLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	rc = fix_item_free(i);

	cr_assert_eq(rc, SUCCESS, "fix_item_free() failed");
}

/* Test get_sdesc_fix_item function for APPLE */
Test(item, sdesc1) {
	fix_item_t* i;

	i = fix_item_new(APPLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	char* ret = get_sdesc_fix_item(i);

	cr_assert_str_eq(ret, "a red apple", "get_sdesc_fix_item() failed");

}

/* Test get_sdesc_fix_item function for KETTLE */
Test(item, sdesc2) {
	fix_item_t* i;

	i = fix_item_new(KETTLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	char* ret = get_sdesc_fix_item(i);

	cr_assert_str_eq(ret, "a black kettle", "get_sdesc_fix_item() failed");

}

/* Test get_ldesc_fix_item function for APPLE */
Test(item, ldesc1) {
	fix_item_t* i;

	i = fix_item_new(APPLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	char* ret = get_ldesc_fix_item(i);

	cr_assert_str_eq(ret, "A juicy Red Delicious apple", 
		"get_ldesc_fix_item() failed");

}

/* Test get_ldesc_fix_item function for KETTLE */
Test(item, ldesc2) {
	fix_item_t* i;

	i = fix_item_new(KETTLE);

	cr_assert_not_null(i, "fix_item_new() failed");

	char* ret = get_sdesc_fix_item(i);

	cr_assert_str_eq(ret, "A black kettle on a stove", "get_ldesc_fix_item() failed");

}