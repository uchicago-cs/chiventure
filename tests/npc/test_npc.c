#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "npc/npc.h"
#include "game-state/item.h"
#include "playerclass/class.h"

/* Creates a sample class. Taken from test_class.c */
class_t* generate_test_class()
{
    class_t* c;
    char *name, *shortdesc, *longdesc;

    name = "Warrior";
    shortdesc = "Mechanically, the warrior focuses on up-close physical "
                "damage with weapons and survives enemy attacks "
                "using heavy armor.\n";
    longdesc = "The warrior is the ultimate armor and weapons expert,"
                " relying on physical strength and years of training to "
                "deal with any obstacle. Mechanically, the warrior focuses "
                "on up-close physical damage with weapons and survives enemy "
                "attacks using heavy armor.\n";

    c = class_new(name, shortdesc, longdesc, NULL, NULL, NULL);

}

/* Creates a sample npc_mov struct. Taken from test_rooms_npc.c */
npc_mov_t *generate_test_npc_mov()
{
    npc_mov_t *npc_mov;
    room_t *test_room;
    test_room = room_new("test_room", "test", "test test");
    npc_mov = npc_mov_new(NPC_MOV_DEFINITE, test_room);
}


/* Checks that npc_new() properly mallocs and inits a new npc struct */
Test(npc, new)
{
    class_t* c;
    npc_t *npc;
    npc_mov_t *movement = generate_test_npc_mov();

    char *npc_id = "npc_22";

    c = generate_test_class();

    npc = npc_new(npc_id, "man", "tall man", c, movement, false);

    cr_assert_not_null(npc, "npc_new() failed");

    cr_assert_eq(strncmp(npc->npc_id, "npc_22", MAX_ID_LEN), 0,
                 "npc_new didn't set npc_id"); 
    cr_assert_eq(strncmp(npc->short_desc, "man", MAX_SDESC_LEN), 0, 
                 "npc_new didn't set short_desc");
    cr_assert_eq(strncmp(npc->long_desc, "tall man", MAX_LDESC_LEN), 0, 
                 "npc_new didn't set long_desc");
    cr_assert_str_eq(npc->class->shortdesc,
                     c->shortdesc, "npc_new didn't set short description for class");
    cr_assert_eq(npc->will_fight, false, 
                      "npc_new didn't set will_fight");
}


/* Checks that npc_init() initialized the fields in the new npc struct */
Test(npc, init)
{
    class_t* c;
    npc_t *npc;
    npc_mov_t *movement = generate_test_npc_mov();
    int res;
  
    char *npc_id2 = "test";

    npc = npc_new(npc_id2, "woman", "short woman", NULL, movement, false);
  
    c = generate_test_class();

    char *npc_id = "npc_22";

    res = npc_init(npc, npc_id, "man", "tall man", c, movement, false); 

    cr_assert_eq(res, SUCCESS, "npc_init() failed");

    cr_assert_eq(strncmp(npc->npc_id, "npc_22", MAX_ID_LEN), 0,
                 "npc_init didn't set npc_id");
    cr_assert_eq(strncmp(npc->short_desc, "man", MAX_SDESC_LEN), 0, 
                 "npc_init didn't set short_desc");
    cr_assert_eq(strncmp(npc->long_desc, "tall man", MAX_LDESC_LEN), 0, 
                 "npc_init didn't set long_desc");
    cr_assert_str_eq(npc->class->shortdesc,
                     c->shortdesc, "npc_init didn't set short description for class");
    cr_assert_eq(npc->will_fight, false, 
                      "npc_init didn't set will_fight");
}


/* Checks that npc_free() frees the given npc struct from memory */
Test(npc, free)
{
    npc_t *npc;
    int res;
    char *npc_id = "test";

    npc = npc_new(npc_id, "woman", "short woman", NULL, NULL, false);

    cr_assert_not_null(npc, "npc_new() failed");

    res = npc_free(npc);

    cr_assert_eq(res, SUCCESS, "npc_free() failed");

}

/* Checks that get_sdesc_npc() returns the short description of the npc */
Test(npc, get_sdesc_npc)
{
    npc_t *npc;
    char *get;
    
    char *npc_id = "test";

    npc = npc_new(npc_id, "woman", "short woman", NULL, NULL, false);

    cr_assert_not_null(npc, "npc_new() failed");
    cr_assert_eq(strncmp(npc->short_desc, "woman", MAX_SDESC_LEN), 0, 
                 "npc_new didn't set short_desc");

    get = get_sdesc_npc(npc);

    cr_assert_not_null(get, "get_sdesc_npc() failed");
    cr_assert_eq(strncmp(get, "woman", MAX_SDESC_LEN), 0, 
                 "get_sdesc_npc() didn't get npc's short_desc");
}

/* Checks that get_ldesc_npc() returns the long description of the npc */
Test(npc, get_ldesc_npc)
{
    npc_t *npc;
    char *get;
    
    char *npc_id = "test";

    npc = npc_new(npc_id, "man", "tall man", NULL, NULL, false);

    cr_assert_not_null(npc, "npc_new() failed");
    cr_assert_eq(strncmp(npc->long_desc, "tall man", MAX_LDESC_LEN), 0, 
                 "npc_new didn't set long_desc");

    get = get_ldesc_npc(npc);

    cr_assert_not_null(get, "get_ldesc_npc() failed");
    cr_assert_eq(strncmp(get, "tall man", MAX_LDESC_LEN), 0, 
                 "get_ldesc_npc() didn't get npc's long_desc");
}

/* Checks that get_inventory() returns the npc's inventory */
Test(npc, add_to_and_get_inventory)
{
    npc_t *npc1, *npc2;
    item_t *new_item;
    item_hash_t *hash1, *hash2;
    item_list_t *list1, *list2;
    char *npc_id1 = "npc_1";
    char *npc_id2 = "npc_2";

    npc1 = npc_new(npc_id1, "short", "long", NULL, NULL, false);
    npc2 = npc_new(npc_id2, "short", "long", NULL, NULL, false);
    new_item = item_new("test_item", "item for npc testing",
                        "item for testing get_npc_inventory()");
    add_item_to_npc(npc2, new_item);

    hash1 = get_npc_inv_hash(npc1);
    hash2 = get_npc_inv_hash(npc2);

    list1 = get_npc_inv_list(npc1);
    list2 = get_npc_inv_list(npc2);

    // Assert everything was made and malloced
    cr_assert_not_null(npc1, "npc_new() failed on npc1");
    cr_assert_not_null(npc2, "npc_new() failed on npc2");
    cr_assert_not_null(new_item, "item_new() failed");

    // Check that inventory with added item is not NULL
    cr_assert_not_null(npc2->inventory,
                       "add_item_to_npc() failed to add item");

    // Check inventory hashes
    cr_assert_eq(hash1, npc1->inventory, "get_npc_inv_hash() failed to "
                 "return NULL for empty inventory");
    cr_assert_eq(hash2, npc2->inventory,
                 "get_npc_inv_hash() failed to return inventory");

    // Check inventory lists
    cr_assert_eq(list1, NULL, "get_npc_inv_list() failed to "
                 "return NULL for empty inventory");
    cr_assert_not_null(list2, "get_npc_inventory() failed to "
                       "return inventory list");

    // Check that added item has correct fields
    cr_assert_eq(strcmp(new_item->item_id, list2->item->item_id), 0,
                 "add_item_to_npc() failed to add item (id is wrong)");
    cr_assert_eq(strcmp(new_item->short_desc, list2->item->short_desc), 0,
                 "add_item_to_npc() failed to add item (short desc is wrong)");
    cr_assert_eq(strcmp(new_item->long_desc, list2->item->long_desc), 0,
                 "add_item_to_npc() failed to add item (long desc is wrong)");
}

/* Checks that add_item_to_npc adds item to the npc struct's inventory 
   by not returning NULL */
Test(npc, add_item_to_npc)
{
    char *npc_id = "1";
    npc_t *npc = npc_new(npc_id, "short", "long", NULL, NULL, false);
    item_t *new_item = item_new("test_item", "item for npc testing",
                                "item for testing add_item_to_npc");
    item_t *dup_item = item_new("test_item", "item for npc testing",
                                "item for testing add_item_to_npc");
    add_item_to_npc(npc, new_item);

    cr_assert_not_null(npc, "npc_new() failed");
    cr_assert_not_null(new_item, "item_new() failed");
    cr_assert_not_null(npc->inventory,
                       "add_item_to_npc() failed to add item");
    
    int rc = add_item_to_npc(npc, dup_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_npc failed to add "
                 "item with identical id");
}

/* Checks that remove_item_from_npc properly removes items */
Test(npc, remove_item_from_npc)
{
    char *npc_id = "npc";
    npc_t *npc = npc_new(npc_id, "short", "long", NULL, NULL, false);
    item_t *test_item = item_new("item", "short", "long");
    item_t *dup_item = item_new("item", "short", "long");
    item_list_t *item_list;
    int rc;
    
    rc = add_item_to_npc(npc, test_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_npc failed to "
                 "add an item to npc");
    rc = add_item_to_npc(npc, dup_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_npc failed to "
                 "add an item to npc");
    
    rc = remove_item_from_npc(npc, test_item);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_npc failed to "
                 "remove an item from npc");
    
    item_list = get_npc_inv_list(npc);
    cr_assert_not_null(item_list, "remove_item_from_npc removed "
                       "both identical items from npc");
}