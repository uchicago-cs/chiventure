#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/openworld/sample_rooms.h"
#include "../../include/openworld/sample_items.h"

/* Tests the functions in sample_rooms.h */


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
