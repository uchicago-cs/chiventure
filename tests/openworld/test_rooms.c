#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "openworld/default_items.h"
#include "openworld/default_rooms.h"

/* Tests the functions in default_rooms.h */

/* testing copy_item_to_hash for item id */
Test(room, copy_apple)
{
    item_hash_t *def = get_default_items();
    item_hash_t *tmp = NULL;
    item_t *item;
    int rc;

    rc = copy_item_to_hash(&tmp, def, "apple");
    cr_assert_not_null(tmp);

    HASH_FIND_STR(tmp, "apple", item);
    cr_assert_str_eq(item->item_id, "apple");
}

/* testing copy_item_to_hash for short desc/long desc */
Test(room, copy_book)
{
    item_hash_t *def = get_default_items();
    item_hash_t *tmp = NULL;
    item_t *item;
    int rc;

    rc = copy_item_to_hash(&tmp, def, "olive");
    cr_assert_not_null(tmp);

    HASH_FIND_STR(tmp, "olive", item);
    cr_assert_str_eq(item->short_desc, "a black olive");
    cr_assert_str_eq(item->long_desc, "A singular, unrefrigerated black olive");
}


/* testing copy_item_to_hash for adding multiple items with 
   the same id; should 'stack' items as lists */
Test(room, copy_duplicate_items)
{
    item_hash_t *orig_hash = get_default_items();
    item_hash_t *dest_hash = NULL;
    
    int num_copies = 4;
    for (int i = 0; i < num_copies; i++) {
        int rc = copy_item_to_hash(&dest_hash, orig_hash, "ice");
        cr_assert_eq(rc, SUCCESS, "Failed to add %dth copy to hash.", i + 1);
    }
    
    cr_assert_not_null(dest_hash);

    item_t *lst_head, *elt;
    HASH_FIND_STR(dest_hash, "ice", lst_head); 
    int count = 0;
    DL_FOREACH(lst_head, elt) {
        if (strcmp(elt->item_id, "ice") != 0) {
            continue;
        }
        count++;
    }

    cr_assert_eq(num_copies, count, 
                 "Expected %d copies of ice item, got %d.", 
                 num_copies, count);
}


/* testing make_default_room for school */
Test(room, make_default_school)
{
    rspec_hash_t *hash = make_default_room("school", NULL, NULL);
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
    item_t *r1_item, *r2_item, *r3_item, *r4_item, *r5_item;

    HASH_FIND_STR(r1->items, "book", r1_item);
    cr_assert_not_null(r1_item);
    cr_assert_str_eq(r1_item->item_id, "book");

    HASH_FIND_STR(r2->items, "pencil", r2_item);
    cr_assert_not_null(r2_item);
    cr_assert_str_eq(r2_item->item_id, "pencil");

    HASH_FIND_STR(r3->items, "door", r3_item);
    cr_assert_not_null(r3_item);
    cr_assert_str_eq(r3_item->item_id, "door");

    HASH_FIND_STR(r4->items, "tray", r4_item);
    cr_assert_not_null(r4_item);
    cr_assert_str_eq(r4_item->item_id, "tray");

    HASH_FIND_STR(r5->items,"door", r5_item);
    cr_assert_not_null(r5_item);
    cr_assert_str_eq(r5_item->item_id, "door");
}

/* testing make_default_room for farmhouse */
Test(room, make_default_farm)
{
    rspec_hash_t *hash = make_default_room("farmhouse", NULL, NULL);
    cr_assert_not_null(hash, "make_default_room failed");

    roomspec_t *r1, *r2, *r3, *r4, *r5, *r6;
    HASH_FIND_STR(hash, "living room", r1);
    HASH_FIND_STR(hash, "open field", r2);
    HASH_FIND_STR(hash, "closet", r3);
    HASH_FIND_STR(hash, "kitchen", r4);
    HASH_FIND_STR(hash, "barn", r5);

    //check if not empty
    cr_assert_not_null(r1);
    cr_assert_not_null(r2);
    cr_assert_not_null(r3);
    cr_assert_not_null(r4);
    cr_assert_not_null(r5);


    //check if room id matches hash room name
    cr_assert_str_eq(r1->room_name, "living room");
    cr_assert_str_eq(r2->room_name, "open field");
    cr_assert_str_eq(r3->room_name, "closet");
    cr_assert_str_eq(r4->room_name, "kitchen");
    cr_assert_str_eq(r5->room_name, "barn");

    //make sure items are assigned to rooms (and not empty)
    item_t *r1_item, *r2_item, *r3_item, *r4_item, *r5_item;

    HASH_FIND_STR(r1->items, "xylophone", r1_item);
    cr_assert_not_null(r1_item);
    cr_assert_str_eq(r1_item->item_id, "xylophone");

    HASH_FIND_STR(r2->items, "eagle", r2_item);
    cr_assert_not_null(r2_item);
    cr_assert_str_eq(r2_item->item_id, "eagle");

    HASH_FIND_STR(r3->items, "door", r3_item);
    cr_assert_not_null(r3_item);
    cr_assert_str_eq(r3_item->item_id, "door");

    HASH_FIND_STR(r4->items, "ice", r4_item);
    cr_assert_not_null(r4_item);
    cr_assert_str_eq(r4_item->item_id, "ice");

    HASH_FIND_STR(r5->items,"cow", r5_item);
    cr_assert_not_null(r5_item);
    cr_assert_str_eq(r5_item->item_id, "cow");
}

/* testing make_default_room for castle */
Test(room, make_default_castle)
{
    rspec_hash_t *hash = make_default_room("castle", NULL, NULL);
    cr_assert_not_null(hash, "make_default_room failed");

    roomspec_t *r1, *r2, *r3, *r4, *r5, *r6;
    HASH_FIND_STR(hash, "dungeon", r1);
    HASH_FIND_STR(hash, "throne room", r2);
    HASH_FIND_STR(hash, "closet", r3);
    HASH_FIND_STR(hash, "library", r4);
    HASH_FIND_STR(hash, "hallway", r5);

    //check if not empty
    cr_assert_not_null(r1);
    cr_assert_not_null(r2);
    cr_assert_not_null(r3);
    cr_assert_not_null(r4);
    cr_assert_not_null(r5);


    //check if room id matches hash room name
    cr_assert_str_eq(r1->room_name, "dungeon");
    cr_assert_str_eq(r2->room_name, "throne room");
    cr_assert_str_eq(r3->room_name, "closet");
    cr_assert_str_eq(r4->room_name, "library");
    cr_assert_str_eq(r5->room_name, "hallway");

    //make sure items are assigned to rooms (and not empty)
    item_t *r1_item, *r2_item, *r3_item, *r4_item, *r5_item;

    HASH_FIND_STR(r1->items, "nail", r1_item);
    cr_assert_not_null(r1_item);
    cr_assert_str_eq(r1_item->item_id, "nail");

    HASH_FIND_STR(r2->items, "gold", r2_item);
    cr_assert_not_null(r2_item);
    cr_assert_str_eq(r2_item->item_id, "gold");

    HASH_FIND_STR(r3->items, "door", r3_item);
    cr_assert_not_null(r3_item);
    cr_assert_str_eq(r3_item->item_id, "door");

    HASH_FIND_STR(r4->items, "book", r4_item);
    cr_assert_not_null(r4_item);
    cr_assert_str_eq(r4_item->item_id, "book");

    HASH_FIND_STR(r5->items,"door", r5_item);
    cr_assert_not_null(r5_item);
    cr_assert_str_eq(r5_item->item_id, "door");
}


/* testing make_default_room for undef bucket, bogus sh_desc, l_desc */
Test(room, make_default_undef_bogus)
{
    rspec_hash_t *hash = make_default_room("pharmacy", "short bogus",
                                         "long bogus");
    cr_assert_not_null(hash, "make_default_room failed");

    roomspec_t *r;
    HASH_FIND_STR(hash, "pharmacy", r);

    cr_assert_not_null(hash, "make_default_room failed");
    cr_assert_str_eq(r->short_desc, "short bogus",
                     "make_default_room failed");
    cr_assert_str_eq(r->long_desc, "long bogus",
                     "make_default_room failed");
}
