#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/default_rooms.h"
#include "../../include/openworld/default_items.h"
/* Tests the functions in default_rooms.h */

/* Tests get_allowed_items for defined room */
Test(room, get_allowed_defn){
	roomspec_t **rooms = get_allowed_rooms("school", NULL, NULL, NULL);	
	cr_assert_not_null(rooms, "get_allowed_rooms failed");

	cr_assert_str_eq(rooms[0]->room_name, "closet",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[1]->room_name, "hallway",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[2]->room_name, "library",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[3]->room_name, "cafeteria",
		"get_alowed_rooms failed");
	cr_assert_str_eq(rooms[4]->room_name, "classroom",
		"get_alllowed_rooms failed");
	cr_assert_str_eq(rooms[0]->allowed_items->item->item_id, "door",
		"get_allowed_rooms failed");
}

/* Tests get_allowed_items for undefined empty room */
Test(room, get_allowed_undef_empty) {
	roomspec_t **rooms = get_allowed_rooms("pharmacy", NULL, NULL, NULL);

	cr_assert_not_null(rooms, "get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->room_name, "pharmacy", 
		"get_allowed_rooms failed");
	cr_assert_null(rooms[0]->short_desc,
		"get_allowed_rooms failed");
	cr_assert_null(rooms[0]->long_desc,
		"get_allowed_rooms failed");
	cr_assert_null(rooms[0]->items, "get_allowed_rooms failed");
}

/* Tests get_allowed_items for undefined room with input strings */
Test(room, get_allowed_undef_bogus) {
	roomspec_t **rooms = get_allowed_rooms("pharmacy", "short bogus",
		"long bogus", NULL);

	cr_assert_not_null(rooms, "get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->room_name, "pharmacy",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->short_desc, "short bogus",
		"get_allowed_rooms failed");
	cr_assert_str_eq(rooms[0]->long_desc, "long bogus",
		"get_allowed_rooms failed");
}

/* testing make_default_room for defined bucket, NULL sh_desc, l_desc*/
Test(room, make_default_defn){
	roomspec_t *hash = make_default_room("school", NULL, NULL, NULL);
	cr_assert_not_null(hash, "make_default_room failed");

	roomspec_t *r1, *r2, *r3, *r4, *r5;
	HASH_FIND_STR(hash, "closet", r1);
	HASH_FIND_STR(hash, "cafeteria", r2);
	HASH_FIND_STR(hash, "classroom", r3);
	HASH_FIND_STR(hash, "hallway", r4);
	HASH_FIND_STR(hash, "library", r5);

	cr_assert_not_null(r1, "make_default_room failed");
	cr_assert_not_null(r2, "make_default_room failed");
	cr_assert_not_null(r3, "make_default_room failed");
	cr_assert_not_null(r4, "maske_default_room failed");
	cr_assert_not_null(r5, "make_default_room failed");

	//check that items got assigned to rooms
	cr_assert_str_eq(r1->allowed_items->item->item_id, "door", 
		"make_default_room failed");
	cr_assert_str_eq(r2->allowed_items->item->item_id, "apple",
		"make_default_room failed");
	cr_assert_str_eq(r3->allowed_items->item->item_id, "book",
		"make_default_room failed");
	cr_assert_str_eq(r4->allowed_items->item->item_id, "door",
		"make_default_room failed");
//	cr_assert_str_eq(r5->allowed_items->item->item_id, "book",
		//"make_default_room failed");
	

}

/* testing make_default_room for undef bucket, bogus sh_desc, l_desc */
Test(room, make_default_undef_bogus) {
	roomspec_t *hash = make_default_room("pharmacy", "short bogus", 
		"long bogus", NULL);
	cr_assert_not_null(hash, "make_default_room failed");

	roomspec_t *r;
	HASH_FIND_STR(hash, "pharmacy", r);

	cr_assert_not_null(hash, "make_default_room failed");
	cr_assert_str_eq(r->short_desc, "short bogus",
		"make_default_room failed");
	cr_assert_str_eq(r->long_desc, "long bogus",
		"make_default_room failed");
}
