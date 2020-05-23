#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_rooms.h"
#include "../../include/openworld/sample_items.h"

/* Tests the functions in sample_rooms.h */

/* testing get_desc_room for a default defn room */
Test(room, get_desc_default){
	char **ret[6] = get_desc_room("school", NULL, NULL);
	cr_assert_not_null(ret, "get_desc_room failed");

	cr_assert_str_eq(ret[0][0], "cafeteria", 
		"get_desc_room failed");
	cr_assert_str_eq(ret[1][0], "classroom", 
		"get_desc_room failed");
	cr_assert_str_eq(ret[2][0], "closet", 
		"get_desc_room failed");
	cr_assert_str_eq(ret[3][0], "field", 
		"get_desc_room failed");
	cr_assert_str_eq(ret[4][0], "hallway", 
		"get_desc_room failed");
	cr_assert_str_eq(ret[5][0], "library", 
		"get_desc_room failed");
}

/* testing get_desc_room for undefined room */
Test(room, get_desc_undef){
	char **ret = get_desc_room("bedroom", "bed", "room");
	cr_assert_not_null(ret, "get_desc_room failed");

	cr_assert_str_eq(ret[0], "bedroom",
		"get_desc_room failed");
	cr_assert_str_eq(ret[1], "bedroom",
		"get_desc_room failed");
	cr_assert_str_eq(ret[2], "bedroom",
		"get_desc_room failed");
}

/* testing make_default_room for defined bucket, NULL sh_desc, l_desc*/
Test(room, make_default_defn){
	//I'm not sure how to write out these tests ... 
}

/* testing make_default_room for defined bucket, bogus sh_desc, l_desc */
Test(room, make_default_defn_bogus){}

/* testing make_default_room for undef bucket, NULL sh_desc, l_desc */
Test(room, make_default_undef){}

/* testing make_default_room for undef bucket, bogus sh_desc, l_desc */
Test(room, make_default_undef_bogus){}
