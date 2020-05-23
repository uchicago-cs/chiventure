#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_items.h"


/* Tests the functions in sample_items.h */

/* Test get_desc_item for default item */
Test(item, get_apple){
	char **test = get_desc_item("apple");
	cr_assert_not_null(test, "get_desc_item failed");
	cr_assert_str_eq(test[0], "apple", "get_desc_item failed");
	cr_assert_str_eq(test[1], "a red apple", 
		"get_desc_item failed");
	cr_assert_str_eq(test[2], "A juicy Red Delicious apple",
		"get_desc_item failed");
}

/* Test get_desc_item for undefined item */
Test(item, get_baby){
	char **test = get_desc_item("baby");
	cr_assert_not_null(test, "get_desc_item failed");
	cr_assert_str_eq(test[0], "baby", "get_desc_item failed");
	cr_assert_null(test[1], NULL,"get_desc_item failed");
	cr_assert_null(test[2], NULL, "get_desc_item failed");
}

/* Test item_list_new */
Test(item, new_list){
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
}

/* Test free_item_list */
Test(item, free_list) {
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	item_list_free(llist);
	cr_assert_null(llist, "item_list_free failed");
}

/* test add_items_to_llist on empty list*/
Test(item, add_list_empty) {
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist = add_items_to_llist(llist, { { "baby", "baby", "baby" } }, 1);
	cr_assert_not_null(llist, "add_items_to_llist failed")
}

/* Test add_items_to_llist on nonempty list */
Test(item, add_list_not_empty) {
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist->item = item_new("babies", "babies", "babies");
	cr_assert_not_null(llist, "item_new failed");	
	llist = add_items_to_llist(llist, { { "baby", "baby", "baby" } }, 1);
	cr_assert_not_null(llist, "add_items_to_llist failed")
}

/* test get_allowed_items on defined room type with empty list */
Test(item, allowed_dungeon_empty){
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist = add_items_to_llist(llist, 
		{ "door","gold", "ladder", "nail" }, 4);
	cr_assert_not_null(llist, "add_items_to_llist failed");

	item_list_t *ret = get_allowed_items("dungeon", item_list_new());

	cr_assert_not_null(ret, "get_allowed_items failed");

	cr_assert_str_eq(ret->item->item_id, "door", 
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->item->item_id, "gold", 
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->item->item_id, "ladder", 
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->item->item_id, "nail", 
		"get_allowed_items failed");
}

/* Test get_allowed_items on defined room type with nonempty list */
Test(item, allowed_dungeon_not_empty){
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist = add_items_to_llist(llist,
		{ "parrot", "door","gold", "ladder", "nail" }, 4);
	cr_assert_not_null(llist, "add_items_to_llist failed");

	item_list_t *l = add_items_to_llist(item_list_new(), { "parrot" }, 1);
	cr_assert_not_null(l, "add_items_to_llist failed");

	item_list_t *ret = get_allowed_items("dungeon", l);
	cr_assert_not_null(ret, "get_allowed_items failed");

	cr_assert_str_eq(ret->item->item_id, "parrot",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->item->item_id, "door",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->item->item_id, "gold",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->item->item_id, "ladder",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->next->item->item_id, "nail",
		"get_allowed_items failed");
}

/* Test get_allowed_items on undefined room type and empty list */
Test(item, allowed_pharmacy_empty) {
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");

	item_list_t *ret = get_allowed_items("pharmacy", item_list_new());
	cr_assert_null(ret, "get_allowed_items failed");
}

/* Test get_allowed_items on undefined room type and nonempty list */
Test(item, allowed_pharmacy_not_empty){
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist = add_items_to_llist(llist,
		{ "parrot", "door" }, 2);
	cr_assert_not_null(llist, "add_items_to_llist failed");

	item_list_t *ret = get_allowed_items("pharmacy", llist);
	cr_assert_null(ret, "get_allowed_items failed");

	cr_assert_str_eq(ret->item->item_id, "parrot",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->item->item_id, "door",
		"get_allowed_items failed");
}