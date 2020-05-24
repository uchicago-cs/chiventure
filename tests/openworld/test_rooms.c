#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/default_rooms.h"
#include "../../include/openworld/default_items.h"
/* Tests the functions in default_rooms.h */


/* testing make_default_room for defined bucket, NULL sh_desc, l_desc*/
Test(room, make_default_defn){
	roomspec_t *hash = make_default_room("school", NULL , NULL, NULL);
	cr_assert_not_null(hash, "make_default_room failed");

	roomspec_t *r1, *r2, *r3, *r4, *r5, *r6;
	HASH_FIND_STR(hash, "library", r1);
	HASH_FIND_STR(hash, "classroom", r2);
	HASH_FIND_STR(hash, "closet", r3);
	HASH_FIND_STR(hash, "cafeteria", r4);
	HASH_FIND_STR(hash, "hallway", r5);

	//check if not empty
	cr_assert_not_null(r1);
	cr_assert_not_null(r2);
	cr_assert_not_null(r3);
	cr_assert_not_null(r4);
	cr_assert_not_null(r5);

	
	//check if room id matches hash room name
	cr_assert_str_eq(r1->room_name, "library");
	cr_assert_str_eq(r2->room_name, "classroom");
	cr_assert_str_eq(r3->room_name, "closet");
	cr_assert_str_eq(r4->room_name, "cafeteria");
	cr_assert_str_eq(r5->room_name, "hallway");

	//make sure items are assigned to rooms (and not empty)
	cr_assert_not_null(r1->allowed_items);
	cr_assert_not_null(r2->allowed_items);
	cr_assert_not_null(r3->allowed_items);
	cr_assert_not_null(r4->allowed_items);
	cr_assert_not_null(r5->allowed_items);
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
