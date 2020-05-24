#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/default_items.h"
#include "../../include/common/uthash.h"

/* Tests the functions in default_items.h */
//printf("out here");
Test(item, default_hat) {
	printf("begin");
	item_hash_t *def = get_default_items();
	printf("more check!\n");
	cr_assert_not_null(def, "get_default_items() NULL, and failed");
	printf("HERE NOW");
	item_t *hat;
	printf("asking for hat\n");
	HASH_FIND_STR(def, "hat", hat);
	cr_assert_not_null(hat, "get_default_items(hat) NULL, and failed");
	printf("here");
//	cr_assert_str_eq(hat->item_id, "hat", 
//		"get_default_items(hat) wrong item id");
//	cr_assert_str_eq(hat->short_desc, "a top hat", 
//		"get_default_items(hat) wrong item id");
//	cr_assert_str_eq(hat->long_desc, "A black top hat with monogrammed A. L.",
//		"get_default_items(hat) wrong item id");
}
/*
Test(item, default_gold) {
	item_hash_t **def = get_default_items();
	cr_assert_not_null(def, "get_default_items() NULL, and failed");

	item_t *gold;
	HASH_FIND_STR(*def, "gold", gold);
	cr_assert_not_null(def, "get_default_items(gold) NULL, and failed");

	cr_assert_str_eq(gold->item_id, "gold", 
		"get_default_items(gold) wrong item id");
	cr_assert_str_eq(gold->short_desc, "three gold coins",
		"get_default_items(gold) wrong short desc");
	cr_assert_str_eq(gold->long_desc, "Three shiny gold coins the size of your eye",
		"get_default_items(gold) wrong long desc");
}

Test(item, default_kettle) {
	item_hash_t **def = get_default_items();
	cr_assert_not_null(def, "get_default_items() NULL, and failed");

	item_t *kettle;
	HASH_FIND_STR(*def, "kettle", kettle);
	cr_assert_not_null(def, "get_default_items(kettle) NULL, and failed");

	cr_assert_str_eq(kettle->item_id, "kettle", 
		"get_default_items(kettle) wrong item id");
	cr_assert_str_eq(kettle->short_desc, "a black kettle", 
		"get_default_items(kettle) wrong short desc");
	cr_assert_str_eq(kettle->long_desc, "A black kettle on a stove",
		"get_default_items(kettle) wrong long desc");
}*/
