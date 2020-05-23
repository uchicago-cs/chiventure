#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_items.h"


/* Tests the functions in sample_items.h */

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

	item_t *baby = item_new("baby", "baby", "baby");
	item_t *babies[1] = {baby};

	llist = add_items_to_llist(llist, babies, 1);
	cr_assert_not_null(llist, "add_items_to_llist failed");
	cr_assert_str_eq(llist->item->item_id, "baby", "add_items_to_llist failed");
	cr_assert_null(llist->next, "add_items_to_llist failed");
}

/* Test add_items_to_llist on nonempty list */
Test(item, add_list_not_empty) {
	item_list_t *llist = item_list_new();

	cr_assert_not_null(llist, "item_list_new failed");

	llist->item = item_new("babies", "babies", "babies");
	cr_assert_not_null(llist->item, "item_new failed");	
	cr_assert_null(llist->next, "item_list_new failed");
	
	item_t *baby = item_new("baby", "baby", "baby");
	item_t *babies[1] = { baby};
	llist = add_items_to_llist(llist, babies, 1);
	cr_assert_not_null(llist, "add_items_to_llist failed");

	cr_assert_str_eq(llist->item->item_id, "babies", "add_items_to_llist failed");
	cr_assert_not_null(llist->next, "add_items_to_llist failed");
	cr_assert_str_eq(llist->item->item_id, "baby", "add_items_to_llist failed");
	cr_assert_null(llist->next, "add_items_to_llist failed");
}

/* test get_allowed_items on defined room type with empty list */
Test(item, allowed_dungeon_empty){
	item_t *door = item_new("door", "a normal door",
		"A wooden door with a worn doorknob"),
		*gold = item_new("gold", "three gold coins", 
			"Three shiny gold coins the size of your eye"), 
		*hat = item_new("hat", "a top hat",
				"A black top hat with a monogrammed A.L."), 
		*ladder = item_new("ladder", "a wood ladder",
				"A wooden ladder with 5 rungs resting against a door"), 
		*nail = item_new("nail", "a normal nail", "A regular metail nail");

	item_t *dungeon_ids[5] = {door, gold, hat, ladder, nail};

	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist = add_items_to_llist(llist, dungeon_ids, 5);
	cr_assert_not_null(llist, "add_items_to_llist failed");

	item_list_t *ret = get_allowed_items("dungeon", item_list_new());

	cr_assert_not_null(ret, "get_allowed_items failed");

	cr_assert_str_eq(ret->item->item_id, "door", 
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->item->item_id, "gold", 
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->item->item_id, "hat", 
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->item->item_id, "ladder", 
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->next->item->item_id, "nail",
		"get_allowed_items failed");
	cr_assert_null(ret->next->next->next->next->next,
		"get_allowed_items failed");
}

/* Test get_allowed_items on defined room type with nonempty list */
Test(item, allowed_dungeon_not_empty){
	item_t *door = item_new("door", "a normal door",
		"A wooden door with a worn doorknob"),
		*gold = item_new("gold", "three gold coins", 
			"Three shiny gold coins the size of your eye"), 
		*hat = item_new("hat", "a top hat",
				"A black top hat with a monogrammed A.L."), 
		*ladder = item_new("ladder", "a wood ladder",
				"A wooden ladder with 5 rungs resting against a door"), 
		*nail = item_new("nail", "a normal nail", "A regular metail nail");

	item_t *dungeon_ids[5] = {door, gold, hat, ladder, nail};

	item_t *parrot = item_new("parrot", "parrot", "parrot");

	item_t *items[1] = { parrot };

	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist = add_items_to_llist(llist, dungeon_ids, 5);
	cr_assert_not_null(llist, "add_items_to_llist failed");

	item_list_t *l = add_items_to_llist(item_list_new(), items, 1);
	cr_assert_not_null(l, "add_items_to_llist failed");

	item_list_t *ret = get_allowed_items("dungeon", l);
	cr_assert_not_null(ret, "get_allowed_items failed");


	cr_assert_str_eq(ret->item->item_id, "parrot",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->item->item_id, "door",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->item->item_id, "gold",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->item->item_id, "hat",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->next->item->item_id, "ladder",
		"get_allowed_items failed");
	cr_assert_str_eq(ret->next->next->next->next->next->item->item_id, "nail",
		"get_allowed_items failed");
	cr_assert_null(ret->next->next->next->next->next->next,
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
	item_t *items[1] = { item_new("parrot", "parrot", "parrot") };
	item_list_t *llist = item_list_new();
	cr_assert_not_null(llist, "item_list_new failed");
	llist = add_items_to_llist(llist, items, 1);
	cr_assert_not_null(llist, "add_items_to_llist failed");

	item_list_t *ret = get_allowed_items("pharmacy", llist);
	cr_assert_null(ret, "get_allowed_items failed");

	cr_assert_str_eq(ret->item->item_id, "parrot",
		"get_allowed_items failed");
	cr_assert_null(ret->next, "get_allowed_items failed");
}
