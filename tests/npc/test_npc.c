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


/* Checks that npc_new() properly mallocs and inits a new npc struct */
Test(npc, new)
{
    class_t* c;
    npc_t *npc;

    c = generate_test_class();

    npc = npc_new("npc_22", 20, c);

    cr_assert_not_null(npc, "npc_new() failed");

    cr_assert_eq(strncmp(npc->npc_id, "npc_22", MAX_ID_LEN), 0,
                 "npc_new didn't set npc_id");
    cr_assert_eq(npc->health, 20, "npc_new() didn't set health");
    cr_assert_str_eq(npc->class->shortdesc,
                     c->shortdesc, "npc_new didn't set short description for class");
}

/* Checks that npc_init() initialized the fields in the new npc struct */
Test(npc, init)
{
    class_t* c;
    npc_t *npc;
    int res;

    npc = npc_new("test", 30, NULL);

    c = generate_test_class();

    res = npc_init(npc, "npc_22", 20, c);

    cr_assert_eq(res, SUCCESS, "npc_init() failed");

    cr_assert_eq(strncmp(npc->npc_id, "npc_22", MAX_ID_LEN), 0,
                 "npc_22", "npc_init didn't set npc_id");
    cr_assert_eq(npc->health, 20, "npc_init didn't set health");
    cr_assert_str_eq(npc->class->shortdesc,
                     c->shortdesc, "npc_new didn't set short description for class");
}

/* Checks that npc_free() frees the given npc struct from memory */
Test(npc, free)
{
    npc_t *npc;
    int res;

    npc = npc_new("npc_22", 20, NULL);

    cr_assert_not_null(npc, "npc_new() failed");

    res = npc_free(npc);

    cr_assert_eq(res, SUCCESS, "npc_free() failed");
}

/* Checks that get_health() returns the health of the npc */
Test(npc, get_npc_health)
{
    npc_t *npc;
    int health;

    npc = npc_new("npc_22", 20, NULL);

    health = get_npc_health(npc);

    cr_assert_not_null(npc, "npc_new() failed");

    cr_assert_eq(health, 20, "get_npc_health() returned incorrect health");
}

/* Checks that an npc's health is changed by change_npc_health()
   both positively and negatively with a set maximum */
Test(npc, change_npc_health) 
{
    npc_t *npc;
    int health1, health2, health3;

    npc = npc_new("npc_22", 99, NULL);
    health1 = change_npc_health(npc, 2, 100);
    health2 = change_npc_health(npc, -20, 100);
    health3 = change_npc_health(npc, 3, 83);

    cr_assert_not_null(npc, "npc_new() failed");

    cr_assert_eq(health1, 100,
                 "change_npc_health() increased health past max");
    cr_assert_eq(health2, 80,
                 "change_npc_health() did not properly reduce health");
    cr_assert_eq(health3, 83,
                 "change_npc_health() did not properly add health");
}

/* Checks that get_inventory() returns the npc's inventory */
Test(npc, add_to_and_get_inventory)
{
    npc_t *npc1, *npc2;
    item_t *new_item;
    item_hash_t *hash1, *hash2;
    item_list_t *list1, *list2;

    npc1 = npc_new("npc_1",20, NULL);
    npc2 = npc_new("npc_2", 21, NULL);
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
    npc_t *npc = npc_new("1", 100, NULL);
    item_t *new_item = item_new("test_item", "item for npc testing",
                                "item for testing add_item_to_npc");
    add_item_to_npc(npc, new_item);

    cr_assert_not_null(npc, "npc_new() failed");
    cr_assert_not_null(new_item, "item_new() failed");
    cr_assert_not_null(npc->inventory,
                       "add_item_to_npc() failed to add item");
}
