#include <stdio.h>
#include <criterion/criterion.h>
#include "game-state/item.h"

#include "game-state/player.h"

#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/room.h"

// BASIC ITEM UNIT TESTS ------------------------------------------------------

/* Checks creation of new item */
Test(item, new)
{
    item_t *new_item = item_new("test_item", "item for testing",
    "test item for item_new()");

    cr_assert_not_null(new_item, "item_new() test 1 has failed!");
    item_free(new_item);
}

/* Checks initialization of new item */
Test(item, init)
{
    item_t *empty_item = item_new("test_item", "This is a test item",
    "The purpose of this item is testing");
    int check = item_init(empty_item, "test_item", "This is a test item",
    "The purpose of this item is testing");

    cr_assert_eq(check, SUCCESS, "item_new() test 1 has failed!");
    item_free(empty_item);
}

/* Checks freeing of item struct */
Test(item, free)
{
    item_t *item_tofree = item_new("my_item", "pls free me",
    "this item needs to be freed");
    int init = item_init(item_tofree, "my_item", "pls free me",
    "this item needs to be freed");

    cr_assert_eq(init, SUCCESS, "item_free test 1: item init failed!");

    int freed = item_free(item_tofree);

    cr_assert_eq(freed, SUCCESS, "item_free() test 1 has failed!");


}

/* Checks return of short description of item */
Test(item, get_sdesc_item)
{
  item_t *new_item = item_new("item", "short", "long");
  item_t *null_item = NULL;
  
  char *ret = get_sdesc_item(new_item);
  char *null_ret = get_sdesc_item(null_item);

  cr_assert_eq(ret, new_item->short_desc, "get_sdesc_item() failed to \
return short description");
  cr_assert_eq(null_ret, NULL, "get_sdesc_item() failed to return NULL\
 for NULL item");
  item_free(new_item);
}

/* Checks return of long description of item */
Test(item, get_ldesc_item)
{
  item_t *new_item = item_new("item", "short", "long");
  item_t *null_item = NULL;

  char *ret = get_ldesc_item(new_item);
  char *null_ret = get_ldesc_item(null_item);

  cr_assert_eq(ret, new_item->long_desc, "get_ldesc_item() failed to \
return long description");
  cr_assert_eq(null_ret, NULL, "get_ldesc_item() failed to return NULL\
 for NULL item");
  item_free(new_item);
}

/* Checks that add_item_to_hash adds item to an item hashtable as expected. */
Test(item, add_item_to_hash)
{
    item_hash_t *ht = NULL;
    item_t *test_item = item_new("item", "short", "long");
    int rc;
    
    rc = add_item_to_hash(&ht, test_item);
    cr_assert_eq(rc, SUCCESS, "add_item_to_hash failed to "
                 "add an item to hashtable");
    delete_all_items(&ht);
}

/* Checks that add_item_to_hash properly adds duplicate items
 * to the item hashtable */
Test(item, add_item_to_hash_duplicate_items)
{
    item_hash_t *ht = NULL;
    item_t *test_item1 = item_new("item", "short", "long");
    item_t *test_item2 = item_new("item", "short", "long");
    item_t *check, *iter;
    int rc;
    int count = 0;
    
    rc = add_item_to_hash(&ht, test_item1);
    
    rc = add_item_to_hash(&ht, test_item1);
    cr_assert_eq(rc, FAILURE, "add_item_to_hash added item with same "
                 "memory address as head item to hashtable");
    
    rc = add_item_to_hash(&ht, test_item2);
    cr_assert_eq(rc, SUCCESS, "add_item_to_hash did not add item with same "
                 "item id as another item to hashtable");
    
    rc = add_item_to_hash(&ht, test_item1);
    cr_assert_eq(rc, FAILURE, "add_item_to_hash added item with same "
                 "memory address as non-head item to hashtable");
    
    HASH_FIND(hh, ht, test_item1->item_id, strnlen(test_item1->item_id, MAX_ID_LEN), check);
    LL_FOREACH(check, iter)
    {
        count++;
    }
    cr_assert_eq(count, 2, "add_item_to_hash did not add items with same "
                 "item ids correctly.");
    delete_all_items(&ht);
}

/* Checks that get_all_items_in_hash returns the expected 
 * item linked list from an item hashtable */
Test(item, get_all_items_in_hash)
{
    item_hash_t *ht = NULL;
    item_t *test_item1 = item_new("item1", "short", "long");
    item_t *test_item2 = item_new("item2", "short", "long");
    item_list_t *list, *iter;
    int count = 0;
    
    list = get_all_items_in_hash(&ht);
    cr_assert_eq(list, NULL, "get_all_items_in_hash did not return NULL for "
                 "empty hashtable");
    
    add_item_to_hash(&ht, test_item1);
    add_item_to_hash(&ht, test_item2);
    list = get_all_items_in_hash(&ht);
    cr_assert_not_null(list, "get_all_items_in_hash returned NULL for "
                       "non-empty hashtable");
    
    LL_FOREACH(list, iter)
    {
        count++;
    }
    
    cr_assert_eq(count, 2, "get_all_items_in_hash did not include all items "
                 "in returned list.");
    delete_all_items(&ht);
    delete_item_llist(list);

}

/* Checks that get_all_items_in_hash returns a linked list
 * with duplicate items if duplicate items exist in an
 * item hashtable */
Test(item, get_all_items_in_hash_duplicate_items)
{
    item_hash_t *ht = NULL;
    item_t *test_item1 = item_new("item1", "short", "long");
    item_t *test_item2 = item_new("item1", "short", "long");
    item_t *test_item3 = item_new("item3", "short", "long");
    item_list_t *list, *iter;
    int count = 0;
    
    add_item_to_hash(&ht, test_item1);
    add_item_to_hash(&ht, test_item2);
    list = get_all_items_in_hash(&ht);
    
    LL_FOREACH(list, iter)
    {
        count++;
    }
    cr_assert_eq(count, 2, "get_all_items_in_hash did not add duplicate "
                 "items to linked list");
    
    add_item_to_hash(&ht, test_item3);
    delete_item_llist(list);
    list = get_all_items_in_hash(&ht);
    count = 0;
    
    LL_FOREACH(list, iter)
    {
        count++;
    }
    cr_assert_eq(count, 3, "get_all_items_in_hash did not include all items "
                 "in returned list");
    delete_all_items(&ht);
    delete_item_llist(list);
}

/* Checks that remove_item_from_hash properly removes items 
 * from an item hashtable. */
Test(item, remove_item_from_hash)
{
    item_hash_t *ht = NULL;
    item_t *test_item1 = item_new("item1", "short", "long");
    item_t *test_item2 = item_new("item2", "short", "long");
    int rc;
    item_list_t *list, *iter;
    int count = 0;
    
    rc = add_item_to_hash(&ht, test_item1);
    cr_assert_eq(rc, SUCCESS, "add_item_to_hash failed to "
                 "add an item to hashtable");
    
    remove_item_from_hash(&ht, test_item2);
    list = get_all_items_in_hash(&ht);
    count = 0;
    LL_FOREACH(list, iter)
    {
        count++;
    }
    cr_assert_eq(count, 1, "remove_item_from_hash did not properly handle case "
                 "where item not in hash was passed to be removed");
    
    rc = remove_item_from_hash(&ht, test_item1);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_hash failed to "
                 "remove an item from hashtable");
    delete_all_items(&ht);
    item_free(test_item1);
    delete_item_llist(list);
    item_free(test_item2);
}

/* Checks that remove_item_from_hash properly removes
 * the head item in a chain of identical id items */
Test(item, remove_item_from_hash_duplicate_items_head)
{
    item_hash_t *ht = NULL;
    item_t *head = item_new("item", "short", "long");
    item_t *last = item_new("item", "short", "long");
    item_t *check = NULL;
    int rc;
    
    add_item_to_hash(&ht, last);
    add_item_to_hash(&ht, head);
        
    rc = remove_item_from_hash(&ht, head);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_hash failed to "
                 "remove an item from hashtable");

    HASH_FIND(hh, ht, head->item_id, strnlen(head->item_id, MAX_ID_LEN), check);
    cr_assert_not_null(check, "remove_item_from_hash removed both "
                       "duplicate items from hashtable");
    cr_assert_eq(check, last, "remove_item_from_hash removed wrong "
                 "item from hashtable");
    cr_assert_eq(check->next, NULL, "remove_item_from_hash failed to "
                 "remove a duplicate item id from hashtable");
    cr_assert_eq(head->next, NULL, "remove_item_from_hash failed to "
                 "update the removed item");
    
    /* Since remove_item_from_hash does not free associated item, manual free */
    rc = item_free(head);
    cr_assert_eq(rc, SUCCESS, "item_free failed to free associated item");

    delete_all_items(&ht);
}

Test(item, delete_all_items_duplicate_item_in_hash)
{
    item_hash_t *ht = NULL;
    item_t *head = item_new("item", "short", "long");
    item_t *last = item_new("item", "short", "long");
    item_t *check = NULL;
    int rc;
    
    add_item_to_hash(&ht, last);
    add_item_to_hash(&ht, head);

    rc = delete_all_items(&ht);
    cr_assert_eq(rc, SUCCESS, "delete_all_items failed to free all associated resources");
}

/* Checks that remove_item_from_hash does not remove
 * an item with identical id but in different memory location
 * than items in hash */
Test(item, remove_item_from_hash_duplicate_items_nonexistant)
{
    item_hash_t *ht = NULL;
    item_t *head = item_new("item", "short", "long");
    item_t *last = item_new("item", "short", "long");
    item_t *check = NULL;
    int rc;
    
    add_item_to_hash(&ht, head);
    
    remove_item_from_hash(&ht, last);
    HASH_FIND(hh, ht, head->item_id, strnlen(head->item_id, MAX_ID_LEN), check);
    cr_assert_not_null(check, "remove_item_from_hash did not properly handle "
                       "case where duplicate item not in hash was passed to "
                       "be removed");
    delete_all_items(&ht);
    item_free(last);
}

/* Checks that remove_item_from_hash properly removes
 * the last item in a chain of identical id items */
Test(item, remove_item_from_hash_duplicate_items_last)
{
    item_hash_t *ht = NULL;
    item_t *head = item_new("item", "short", "long");
    item_t *last = item_new("item", "short", "long");
    item_t *check = NULL;
    int rc;
    
    add_item_to_hash(&ht, last);
    add_item_to_hash(&ht, head);

    rc = remove_item_from_hash(&ht, last);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_hash failed to "
                 "remove an item from hashtable");
    HASH_FIND(hh, ht, head->item_id, strnlen(head->item_id, MAX_ID_LEN), check);
    cr_assert_not_null(check, "remove_item_from_hash removed both "
                       "duplicate items from hashtable");
    cr_assert_eq(check, head, "remove_item_from_hash removed wrong "
                 "duplicate item from hashtable");
    cr_assert_eq(check->next, NULL, "remove_item_from_hash failed to "
                 "remove a duplicate item id from hashtable");
    delete_all_items(&ht);
    item_free(last);
}

/* Checks that remove_item_from_hash properly removes
 * a middle item in a chain of identical id items */
Test(item, remove_item_from_hash_duplicate_items_middle)
{
    item_hash_t *ht = NULL;
    item_t *head = item_new("item", "short", "long");
    item_t *middle = item_new("item", "short", "long");
    item_t *last = item_new("item", "short", "long");
    item_t *check = NULL;
    int rc;
    
    add_item_to_hash(&ht, last);
    add_item_to_hash(&ht, middle);
    add_item_to_hash(&ht, head);

    rc = remove_item_from_hash(&ht, middle);
    cr_assert_eq(rc, SUCCESS, "remove_item_from_hash failed to "
                 "remove an item from hashtable");
    HASH_FIND(hh, ht, head->item_id, strnlen(head->item_id, MAX_ID_LEN), check);
    cr_assert_not_null(check, "remove_item_from_hash removed all "
                       "duplicate items from hashtable");
    cr_assert_eq(check, head, "remove_item_from_hash removed wrong "
                 "duplicate item from hashtable");
    cr_assert_eq(check->next, last, "remove_item_from_hash did remove "
                 "duplicate item from middle of list properly");
    cr_assert_eq(middle->next, NULL, "remove_item_from_hash failed to "
                 "update the removed item");
    delete_all_items(&ht);
    item_free(middle);
}

/* Checks that add_effect_to_items() adds a sat effect to an item */
Test(item, add_effect_to_item)
{
    item_t *item = item_new("item", "short", "long");
    effects_global_t *global = global_effect_new("health");
    stat_effect_t *effect = stat_effect_new(global);
    int rc = add_effect_to_item(item, effect);

    cr_assert_eq(rc, SUCCESS, "add_effect_to_game failed");
    cr_assert_not_null(item->stat_effects, "effect not added to stat_effects");
    item_free(item);
    free(global->name);
    free(global);
}

// TESTS FOR ADD_ATRR_TO_HASH --------------------------------------------------

/* Checks adding attribute to item hash */
Test(attribute, add_attr_to_hash_success)
{
    item_t *test_item = item_new("test_item", "test item for attributes",
    "item for testing add_attr_to_hash");

    attribute_t *test_attr = malloc(sizeof(attribute_t));
    
    char *tmp = "test_attr";
    test_attr->attribute_key = strndup(tmp, 100);
    test_attr->attribute_tag = STRING;
    test_attr->attribute_value.str_val = "test";

    int test = add_attribute_to_hash(test_item, test_attr);

    cr_assert_eq(test, SUCCESS, "add_attr_to_hash() test failed!");
    item_free(test_item);
}

/* Checks if adding same attribute to item hash twice fails */
Test(attribute, add_attr_to_hash_failure)
{
    item_t *test_item = item_new("test_item", "test item for attributes",
    "item for testing add_attr_to_hash");

    attribute_t *test_attr = malloc(sizeof(attribute_t));
        char *tmp = "test_attr";
    test_attr->attribute_key = strndup(tmp, 100);
    test_attr->attribute_tag = STRING;
    test_attr->attribute_value.str_val = "test";

    int setup = add_attribute_to_hash(test_item, test_attr);
    cr_assert_eq(setup, SUCCESS, "add_attr_to_hash() test setup failed!");

    int test = add_attribute_to_hash(test_item, test_attr);
    cr_assert_eq(test, FAILURE,
        "add_attr_to_hash() test failed: duplicate attribute added");
    item_free(test_item);

}


// TEST FOR GENERAL GET_ATTRIBUTE()---------------------------------------------

/* Checks helper function to retrieve attribute from item */
Test(attribute, get_attribute)
{
    item_t *test_item = item_new("test_item", "test item for attributes",
    "item for testing get_attribute()");

    int test_attr1 = set_str_attr(test_item, "door", "locked");
    int test_attr2 = set_int_attr(test_item, "# of weapons", 1);

    cr_assert_eq(test_attr1, SUCCESS, "get_attr(): adding attr1 failed!");
    cr_assert_eq(test_attr2, SUCCESS, "get_attr(): adding attr2 failed!");

    attribute_t *my_attr = get_attribute(test_item, "door");

    cr_assert_str_eq(my_attr->attribute_key, "door", "get_attr(): wrong key!");
    cr_assert_str_eq(my_attr->attribute_value.str_val, "locked",
    "get_attr(): wrong value!");
    item_free(test_item);

}

// TESTS FOR TYPE-SPECIFIC ATTR_NEW() FUNCTIONS --------------------------------

Test(attribute, str_attr_new)
{
    attribute_t *test_attr = str_attr_new("Attribute_Test_Name", "Attribute_Test_Value");

    cr_assert_not_null(test_attr, "str_attr_new: null attribute returned");

    cr_assert_str_eq(test_attr->attribute_value.str_val, "Attribute_Test_Value", 
                     "str_attr_new: Attribute value not correctly set");

    attribute_free(test_attr);
}

Test(attribute, int_attr_new)
{
    attribute_t *test_attr = int_attr_new("Attribute_Test_Name", 0);

    cr_assert_not_null(test_attr, "int_attr_new: null attribute returned");

    cr_assert_eq(test_attr->attribute_value.int_val, 0, 
                 "int_attr_new: Attribute value not correctly set");

    attribute_free(test_attr);
}

Test(attribute, double_attr_new)
{
    attribute_t *test_attr = double_attr_new("Attribute_Test_Name", 0.0);

    cr_assert_not_null(test_attr, "double_attr_new: null attribute returned");

    cr_assert_eq(test_attr->attribute_value.double_val, 0.0, 
                 "double_attr_new: Attribute value not correctly set");

    attribute_free(test_attr);
}

Test(attribute, char_attr_new)
{
    attribute_t *test_attr = char_attr_new("Attribute_Test_Name", 'a');

    cr_assert_not_null(test_attr, "char_attr_new: null attribute returned");

    cr_assert_eq(test_attr->attribute_value.char_val, 'a', 
                 "char_attr_new: Attribute value not correctly set");

    attribute_free(test_attr);
}

Test(attribute, bool_attr_new)
{
    attribute_t *test_attr = bool_attr_new("Attribute_Test_Name", true);

    cr_assert_not_null(test_attr, "bool_attr_new: null attribute returned");

    cr_assert_eq(test_attr->attribute_value.bool_val, true, 
                     "int_attr_new: Attribute value not correctly set");

    attribute_free(test_attr);
}

// TESTS FOR TYPE-SPECIFIC SET_ATTR() FUNCTIONS --------------------------------

/* Checks creation of new string attribute and adding it to an item */
Test(attribute, set_str_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_str_attr(test_item, "Attribute_Test_Name", "Attribute_Test_Value");
    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
    char* test_str = test_attr->attribute_value.str_val;
    cr_assert_str_eq(test_str, "Attribute_Test_Value",
    "change_str_attr: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new integer attribute and adding it to an item */
Test(attribute, set_int_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
    cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "set_int_attribute: no elements added to hash");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "set_int_attribute: null attribute returned");
    int test_int = test_attr->attribute_value.int_val;
    cr_assert_eq(test_int, 2, "set_int_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new double attribute and adding it to an item */
Test(attribute, set_double_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
    cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_double_attribute: no elements added to hash");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr,
        "change_double_attribute: null attribute returned");
    double test_double = test_attr->attribute_value.double_val;
    cr_assert_float_eq(test_double, 2.0, 0.001,
        "change_double_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new character attribute and adding it to an item */
Test(attribute, set_char_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
    cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_char_attribute: no elements added to hash");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr,
        "change_char_attribute: null attribute returned");
    char test_char = test_attr->attribute_value.char_val;
    cr_assert_eq(test_char, 'a', "change_char_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new boolean attribute and adding it to an item */
Test(attribute, set_bool_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
    cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_bool_attribute: no elements added to hash");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr,
        "change_bool_attribute: null attribute returned");
    bool test_bool = test_attr->attribute_value.bool_val;
    cr_assert_eq(test_bool, true, "change_bool_attribute: set the wrong value");
    item_free(test_item);
}

// TESTS FOR TYPE-SPECIFIC SET_ATTR() FUNCTIONS CHANGING ATTR VALUE ------------------------

/* Checks creation of new string attribute and changing its value */
Test(attribute, change_str_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");
    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value_2");
    cr_assert_eq(rv, SUCCESS,
        "change_str_attr: did not successfully change attr");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
    char* test_str = test_attr->attribute_value.str_val;
    cr_assert_str_eq(test_str, "Attribute_Test_Value_2",
    "change_str_attr: changed to the wrong value");
    item_free(test_item);
}

/* Checks creation of new str attribute and if change to non-str is blocked */
Test(attribute, change_str_attr_fail)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");

    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");

    rv = set_int_attr(test_item, "Attribute_Test_Name", 3);
    cr_assert_eq(rv, FAILURE,
        "change_str_attr: string attr was wrongfully overwritten");

    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "change_str_attr: null attribute returned");
    char* test_str = test_attr->attribute_value.str_val;
    cr_assert_str_eq(test_str, "Attribute_Test_Value",
    "change_str_attr: changed to a non-string type");
    item_free(test_item);
}

/* Checks creation of new string attribute and changing its value */
Test(attribute, change_int_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
    cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "set_int_attribute: no elements added to hash");
    rv = set_int_attr(test_item, "Attribute_Test_Name", 3);
    cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully change attr");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "set_int_attribute: null attribute returned");
    int test_int = test_attr->attribute_value.int_val;
    cr_assert_eq(test_int, 3, "set_int_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new int attribute and if change to non-int is blocked */
Test(attribute, change_int_attr_fail)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_int_attr(test_item, "Attribute_Test_Name", 5);

    cr_assert_eq(rv, SUCCESS, "change_int_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_int_attr: no elements added to hash");

    rv = set_str_attr(test_item, "Attribute_Test_Name", "five");
    cr_assert_eq(rv, FAILURE,
        "change_int_attr: integer attr was wrongfully overwritten");

    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "change_int_attr: null attribute returned");
    int test_int = test_attr->attribute_value.int_val;
    cr_assert_eq(test_int, 5, "change_int_attr: changed to a non-integer type");
    item_free(test_item);
}

/* Checks creation of new double attribute and changing its value */
Test(attribute, change_double_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
    cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_double_attribute: no elements added to hash");
    rv = set_double_attr(test_item, "Attribute_Test_Name", 2.5);
    cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully change attr");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr,
        "change_double_attribute: null attribute returned");
    double test_double = test_attr->attribute_value.double_val;
    cr_assert_float_eq(test_double, 2.5, 0.0001,
        "change_double_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new dbl attribute and if change to non-dbl is blocked */
Test(attribute, change_double_attr_fail)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_double_attr(test_item, "Attribute_Test_Name", 5.0);

    cr_assert_eq(rv, SUCCESS,
        "change_double_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_double_attr: no elements added to hash");

    rv = set_str_attr(test_item, "Attribute_Test_Name", "five");
    cr_assert_eq(rv, FAILURE,
        "change_double_attr: double attr was wrongfully overwritten");

    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr,
        "change_double_attr: null attribute returned");
    double test_double = test_attr->attribute_value.double_val;
    cr_assert_eq(test_double, 5.0,
        "change_double_attr: changed to a non-double type");
    item_free(test_item);
}

/* Checks creation of new character attribute and changing its value */
Test(attribute, change_char_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
    cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_char_attribute: no elements added to hash");
    rv = set_char_attr(test_item, "Attribute_Test_Name", 'b');
    cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully change attr");
    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr,
        "change_char_attribute: null attribute returned");
    char test_char = test_attr->attribute_value.char_val;
    cr_assert_eq(test_char, 'b', "change_char_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new char attribute and if change to non-char is blocked */
Test(attribute, change_char_attr_fail)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_char_attr(test_item, "Attribute_Test_Name", 'x');

    cr_assert_eq(rv, SUCCESS,
        "change_char_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_char_attr: no elements added to hash");

    rv = set_int_attr(test_item, "Attribute_Test_Name", 8);
    cr_assert_eq(rv, FAILURE,
        "change_char_attr: char attr was wrongfully overwritten");

    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "change_char_attr: null attribute returned");
    char test_char = test_attr->attribute_value.char_val;
    cr_assert_eq(test_char, 'x',
    "change_char_attr: changed to a non-char type");
    item_free(test_item);
}

/* Checks creation of new boolean attribute and changing its value */
Test(attribute, change_bool_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
    cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully set attr");

    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_bool_attribute: no elements added to hash");

    rv = set_bool_attr(test_item, "Attribute_Test_Name", false);
    cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully change attr");

    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr,
        "change_bool_attribute: null attribute returned");

    bool test_bool = test_attr->attribute_value.bool_val;
    cr_assert_eq(test_bool, false,
        "change_bool_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks creation of new bool attribute and if change to non-bool is blocked */
Test(attribute, change_bool_attr_fail)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test setting attributes");
    int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);

    cr_assert_eq(rv, SUCCESS,
        "change_bool_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_bool_attr: no elements added to hash");

    rv = set_int_attr(test_item, "Attribute_Test_Name", 8);
    cr_assert_eq(rv, FAILURE,
        "change_bool_attr: bool attr was wrongfully overwritten");

    attribute_t* test_attr = get_attribute(test_item, "Attribute_Test_Name");
    cr_assert_not_null(test_attr, "change_bool_attr: null attribute returned");

    bool test_bool = test_attr->attribute_value.bool_val;
    cr_assert_eq(test_bool, true,
        "change_bool_attr: changed to a non-bool type");
    item_free(test_item);
}


// TESTS FOR TYPE-SPECIFIC GET_ATTR() FUNCTIONS -------------------------------

/* Checks retrieval of string attribute value */
Test(attribute, get_str_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
    int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");
    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    char* test_str = get_str_attr(test_item, "Attribute_Test_Name");
    cr_assert_str_eq(test_str, "Attribute_Test_Value",
    "change_str_attr: set the wrong value");
    item_free(test_item);
}

/* Checks retrieval of integer attribute value */
Test(attribute, get_int_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
    int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);
    cr_assert_eq(rv, SUCCESS,
        "set_int_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "set_int_attribute: no elements added to hash");
    int test_int = get_int_attr(test_item, "Attribute_Test_Name");
    cr_assert_eq(test_int, 2, "set_int_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks retrieval of double attribute value */
Test(attribute, get_double_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
    int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
    cr_assert_eq(rv, SUCCESS,
        "change_double_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_double_attribute: no elements added to hash");
    double test_double = get_double_attr(test_item, "Attribute_Test_Name");
    cr_assert_float_eq(test_double, 2.0, 0.001,
        "change_double_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks retrieval of character attribute value */
Test(attribute, get_char_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
    int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
    cr_assert_eq(rv, SUCCESS,
        "change_char_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_char_attribute: no elements added to hash");
    char test_char = get_char_attr(test_item, "Attribute_Test_Name");
    cr_assert_eq(test_char, 'a', "change_char_attribute: set the wrong value");
    item_free(test_item);
}

/* Checks retrieval of boolean attribute value */
Test(attribute, get_bool_attr)
{
    item_t *test_item = item_new("test_item", "attr test",
    "item to test getting attributes");
    int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
    cr_assert_eq(rv, SUCCESS,
        "change_bool_attribute: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0,
        "change_bool_attribute: no elements added to hash");
    bool test_bool = get_bool_attr(test_item, "Attribute_Test_Name");
    cr_assert_eq(test_bool, true, "change_bool_attribute: set the wrong value");
    item_free(test_item);
}


/* Checks if retrieval of non-str attribute using get_str_attr is blocked */
Test(attribute, get_non_str_attr) {
    item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");
    int rv = set_int_attr(test_item, "Attribute_Test_Name", 2);

    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");
    int num_in_hash = HASH_COUNT(test_item->attributes);

    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    char *check = get_str_attr(test_item, "Attribute_Test_Name");

    cr_assert_null(check, "get_non_str_attr() test: incorrect finding");
    item_free(test_item);
}

/* Checks if retrieval of non-int attribute using get_int_attr is blocked */
Test(attribute, get_non_int_attr) {
    item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

    int rv = set_double_attr(test_item, "Attribute_Test_Name", 2.0);
    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    int check = get_int_attr(test_item, "Attribute_Test_Name");

    cr_assert_eq(check, -1, "get_non_int_attr() test: incorrect finding");
    item_free(test_item);
}

/* checks if retrieval of non-double attribute using get_double_attr is blocked */
Test(attribute, get_non_double_attr) {
    item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

    int rv = set_char_attr(test_item, "Attribute_Test_Name", 'a');
    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    double check = get_double_attr(test_item, "Attribute_Test_Name");

    cr_assert_float_eq(check, -1.0, 0.001,
        "change_double_attr: incorrect finding");
    item_free(test_item);
}

/* Checks if retrieval of non-character attribute using get_char_attr is blocked */
Test(attribute, get_non_char_attr) {
    item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

    int rv = set_bool_attr(test_item, "Attribute_Test_Name", true);
    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    char check = get_char_attr(test_item, "Attribute_Test_Name");

    cr_assert_eq(check, '~', "get_non_char_attr() test: incorrect finding");
    item_free(test_item);
}

/* Checks if retrieval of non-boolean attribute using get_bool_attr is blocked */
Test(attribute, get_non_bool_attr) {
    item_t *test_item = item_new("test item", "test item for testing",
    "test item for testing item");

    int rv = set_str_attr(test_item, "Attribute_Test_Name",
    "Attribute_Test_Value");
    cr_assert_eq(rv, SUCCESS, "change_str_attr: did not successfully set attr");

    int num_in_hash = HASH_COUNT(test_item->attributes);
    cr_assert_gt(num_in_hash, 0, "change_str_attr: no elements added to hash");
    bool check = get_bool_attr(test_item, "Attribute_Test_Name");

    cr_assert_null(check, "get_non_bool_attr() test: incorrect finding");
    item_free(test_item);
}

// TEST FOR ATTRIBUTES_EQUAL()-------------------------------------------------

/* checks that two equal attributes are equal */
Test(attribute, equal)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test");
    set_str_attr(item2, "test_attr", "test");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, SUCCESS, "attributes_equal() test failed!");
    item_free(item1);
    item_free(item2);

}

/* checks that two unequal attributes are not equal */
Test(attribute, not_equal)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_str_attr(item2, "test_attr", "test2");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, FAILURE, "attributes_equal() test failed!");
    item_free(item1);
    item_free(item2);
}

/* checks that function catches if one of the attributes being compared
is NULL */
Test(attribute, null_attr)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: neither of the attributes are NULL");
    item_free(item1);
    item_free(item2);
}

/* the following tests check that function catches if the attributes being compared are of different types  */

// str + int
Test(attribute_equal, str_to_int)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_int_attr(item2, "test_attr", 1);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// str + char
Test(attribute_equal, str_to_char)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_char_attr(item2, "test_attr", 'x');

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// str + double
Test(attribute_equal, str_to_double)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_double_attr(item2, "test_attr", 2.0);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// str + bool
Test(attribute_equal, str_to_bool)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_str_attr(item1, "test_attr", "test1");
    set_bool_attr(item2, "test_attr", true);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// int + char
Test(attribute_equal, int_to_char)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_int_attr(item1, "test_attr", 1);
    set_char_attr(item2, "test_attr", 'x');

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// int + double
Test(attribute_equal, int_to_double)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_int_attr(item1, "test_attr", 1);
    set_double_attr(item2, "test_attr", 2.0);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// int + bool
Test(attribute_equal, int_to_bool)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_int_attr(item1, "test_attr", 1);
    set_bool_attr(item2, "test_attr", true);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// char + double
Test(attribute_equal, char_to_double)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_char_attr(item1, "test_attr", 'x');
    set_double_attr(item2, "test_attr", 2.0);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// char + bool
Test(attribute_equal, char_to_bool)
{
    item_t *item1 = item_new("test_item1", "attribute test",
    "testing equality of attributes");
    item_t *item2 = item_new("test_item2", "attribute test",
    "testing equality of attributes");
    set_char_attr(item1, "test_attr", 'x');
    set_bool_attr(item2, "test_attr", true);

    int equal = attributes_equal(item1, item2, "test_attr");

    cr_assert_eq(equal, -1,
        "attributes_equal() test failed: attributes are of the same type");
    item_free(item1);
    item_free(item2);
}

// TEST FOR ATTRIBUTE_FREE() --------------------------------------------------

/* Checks freeing of attribute struct */
Test(attribute, attr_free)
{
    attribute_t *test_attr = (attribute_t*)malloc(sizeof(attribute_t));

    test_attr->attribute_key = malloc(sizeof(char)*100);
    test_attr->attribute_tag = INTEGER;
    test_attr->attribute_value.int_val = 5;

    int test = attribute_free(test_attr);

    cr_assert_eq(test, SUCCESS, "attribute_free() test failed!");

}

// TESTS FOR HASH DELETION ----------------------------------------------------

/* Checks deletion of all attributes associated with an item struct */
Test(attribute, deletion)
{
    item_t *test_item = item_new("test_item", "item for attr testing",
    "item for testing del_all_attr function");

    set_str_attr(test_item, "test1", "this is a test");
    set_int_attr(test_item, "open", 1);
    set_double_attr(test_item, "battery", 0.75);


    int test = delete_all_attributes(test_item->attributes);

    cr_assert_eq(test, SUCCESS, "delete_all_attributes() test failed!");
    test_item->attributes = NULL;
    item_free(test_item);
}

/* Checks deletion of all items within a room struct */
Test(item, deletion_in_room)
{
    room_t *test_room = room_new("test_room", "room for item testing",
    "room for testing item deletion");
    item_t *test_item1 = item_new("hat", "fedora", "Indiana Jones vibes");
    item_t *test_item2 = item_new("lightsaber", "weapon",
    "star wars vibes, it's a crossover episode");
    item_t *test_item3 = item_new("apple", "fujis are the best",
    "a player's gotta nourish");

    int item_add1 = add_item_to_room(test_room, test_item1);
    int item_add2 = add_item_to_room(test_room, test_item2);
    int item_add3 = add_item_to_room(test_room, test_item3);

    cr_assert_eq(item_add1, SUCCESS,
        "del_all_items test: item1 was not added!");
    cr_assert_eq(item_add2, SUCCESS,
        "del_all_items test: item2 was not added!");
    cr_assert_eq(item_add3, SUCCESS,
        "del_all_items test: item3 was not added!");

    int del_items = delete_all_items(&test_room->items);
    cr_assert_eq(del_items, SUCCESS,
        "del_all_items test: items were not successfully deleted!");
    room_free(test_room);

}

/* Checks deletion of all items within a player struct */
Test(item, deletion_in_player)
{
    chiventure_ctx_t *ctx = chiventure_ctx_new(NULL);
    player_t *test_player = player_new("test_player");
    item_t *test_item1 = item_new("hat", "fedora", "Indiana Jones vibes");
    item_t *test_item2 = item_new("lightsaber", "weapon",
    "star wars vibes, it's a crossover episode");
    item_t *test_item3 = item_new("apple", "fujis are the best",
    "a player's gotta nourish");

    int item_add1 = add_item_to_player(test_player, test_item1, ctx->game);
    int item_add2 = add_item_to_player(test_player, test_item2, ctx->game);
    int item_add3 = add_item_to_player(test_player, test_item3, ctx->game);

    cr_assert_eq(item_add1, SUCCESS,
        "del_all_items test: item1 was not added!");
    cr_assert_eq(item_add2, SUCCESS,
        "del_all_items test: item2 was not added!");
    cr_assert_eq(item_add3, SUCCESS,
        "del_all_items test: item3 was not added!");

    int del_items = delete_all_items(&test_player->inventory);
    cr_assert_eq(del_items, SUCCESS,
        "del_all_items test: items were not successfully deleted!");
    player_free(test_player);

}

// Tests for attribute_lists---------------------------------------------------

Test(attribute_list, add_to_new_list)
{

    attribute_t* test_attr1 = (attribute_t*)malloc(sizeof(attribute_t));


    char *tmp = "Queen";
    test_attr1->attribute_tag = INTEGER;
    test_attr1->attribute_value.int_val = 5;
    test_attr1->attribute_key = strdup(tmp);

    attribute_list_t* test_head = create_list_attribute();

    int add_attribute = add_attribute_to_list(test_head, test_attr1); 

    cr_assert_eq(add_attribute, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");

    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
}

Test(attribute_list, add_attribute_to_list)
{
    attribute_t* test_attr = (attribute_t*)malloc(sizeof(attribute_t));
    char *n = "Knight";
    test_attr->attribute_tag = INTEGER;
    test_attr->attribute_value.int_val = 5;
    test_attr->attribute_key = strdup(n);

    attribute_list_t* test_head = malloc(sizeof(attribute_list_t));
    test_head->next = NULL;
    test_head->attribute = test_attr;

    attribute_t* test_attr1 = (attribute_t*)malloc(sizeof(attribute_t));
    char *q = "Queen";
    test_attr1->attribute_tag = INTEGER;
    test_attr1->attribute_value.int_val = 5;
    test_attr1->attribute_key = strdup(q);

    int add_attribute = add_attribute_to_list(test_head, test_attr1);

    cr_assert_eq(add_attribute, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");

    delete_attribute_llist(test_head);
    attribute_free(test_attr);
    attribute_free(test_attr1);
}

Test(attribute_list, remove_from_one_attribute_list)
{
    attribute_t* test_attr1 = (attribute_t*)malloc(sizeof(attribute_t));
    char *q = "Queen";
    test_attr1->attribute_tag = INTEGER;
    test_attr1->attribute_value.int_val = 5;
    test_attr1->attribute_key = strdup(q);

    attribute_list_t* test_head = create_list_attribute();

    int add_attribute = add_attribute_to_list(test_head, test_attr1); 

    cr_assert_eq(add_attribute, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");

    int remove_attribute = remove_attribute_from_list(test_head, test_attr1->attribute_key);

    cr_assert_eq(remove_attribute, SUCCESS,
        "remove_from_one_attribute_list test: attribute Queen not removed");
    
    /* Check if we can still use test_head */
    attribute_t *test_attr2 = (attribute_t*)malloc(sizeof(attribute_t));
    char *k = "King";
    test_attr2->attribute_tag = INTEGER;
    test_attr2->attribute_value.int_val = 5;
    test_attr2->attribute_key =  strdup(k);

    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);

    cr_assert_eq(add_attribute2, SUCCESS,
                "add_attribute_to_list after removing last attribute test: Fail");

    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);
}

Test(attribute_list, remove_attribute_from_list)
{

    attribute_list_t* test_head = create_list_attribute();

    attribute_t *test_attr1 = (attribute_t*)malloc(sizeof(attribute_t));
    char *n = "Knight";
    test_attr1->attribute_tag = INTEGER;
    test_attr1->attribute_value.int_val = 5;
    test_attr1->attribute_key =  strdup(n);

    attribute_t *test_attr2 = (attribute_t*)malloc(sizeof(attribute_t));
    char *q = "Queen";
    test_attr2->attribute_tag = INTEGER;
    test_attr2->attribute_value.int_val = 5;
    test_attr2->attribute_key =  strdup(q);

    int add_attribute1 = add_attribute_to_list(test_head, test_attr1);
    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);

    cr_assert_eq(add_attribute1, SUCCESS,
        "add_attribute_to_list test: attribute Knight not added");
    cr_assert_eq(add_attribute2, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");

    int remove_attribute = remove_attribute_from_list(test_head, test_attr2->attribute_key);
  
    cr_assert_eq(remove_attribute, SUCCESS,
        "remove_attirubte_from_list test: attribute Queen not removed");

    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);

}

Test(attribute_list, list_contains_attribute)
{
    attribute_list_t* test_head = create_list_attribute();

    attribute_t *test_attr1 = (attribute_t*)malloc(sizeof(attribute_t));
    char *n = "Knight";
    test_attr1->attribute_tag = INTEGER;
    test_attr1->attribute_value.int_val = 5;
    test_attr1->attribute_key =  strdup(n);

    attribute_t *test_attr2 = (attribute_t*)malloc(sizeof(attribute_t));
    char *q = "Queen";
    test_attr2->attribute_tag = INTEGER;
    test_attr2->attribute_value.int_val = 5;
    test_attr2->attribute_key =  strdup(q);

    attribute_t *test_attr3 = (attribute_t*)malloc(sizeof(attribute_t));
    char *k = "King";
    test_attr3->attribute_tag = INTEGER;
    test_attr3->attribute_value.int_val = 5;
    test_attr3->attribute_key =  strdup(k);

    int add_attribute1 = add_attribute_to_list(test_head, test_attr1);
    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);
    int add_attribute3 = add_attribute_to_list(test_head, test_attr3);

    cr_assert_eq(add_attribute1, SUCCESS,
        "add_attribute_to_list test: attribute Knight not added");
    cr_assert_eq(add_attribute2, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");
    cr_assert_eq(add_attribute3, SUCCESS,
        "add_attribute_to_list test: attribute King not added");

    int contain_attribute = list_contains_attribute(test_head, test_attr3->attribute_key);

    cr_assert_eq(contain_attribute, true,
        "list_contains_attribute test: attribute King not found");
    
    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);
    attribute_free(test_attr3);

}

// Tests for getting attributes from a list ------------------------------------

/* Checks retrieval of a string attribute from a list of attributes */
Test(attribute_list, list_get_str_attr)
{
    attribute_list_t* test_head = create_list_attribute();

    attribute_t *test_attr1 = str_attr_new("Knight", "Sword");
    attribute_t *test_attr2 = str_attr_new("Queen", "Scepter");
    attribute_t *test_attr3 = str_attr_new("King", "Crown");

    int add_attribute1 = add_attribute_to_list(test_head, test_attr1);
    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);
    int add_attribute3 = add_attribute_to_list(test_head, test_attr3);

    cr_assert_eq(add_attribute1, SUCCESS,
        "add_attribute_to_list test: attribute Knight not added");
    cr_assert_eq(add_attribute2, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");
    cr_assert_eq(add_attribute3, SUCCESS,
        "add_attribute_to_list test: attribute King not added");
    
    char* result_n = list_get_str_attr(test_head, "Knight");
    char* result_q = list_get_str_attr(test_head, "Queen");
    char* result_k = list_get_str_attr(test_head, "King");

    cr_assert_not_null(result_n, "list_get_str_attr returned null for the Knight attribute");
    cr_assert_not_null(result_q, "list_get_str_attr returned null for the Queen attribute");
    cr_assert_not_null(result_k, "list_get_str_attr returned null for the King attribute");

    cr_assert_eq(result_n, "Sword", "list_get_str_attr returned the incorrect string for the Knight attribute");
    cr_assert_eq(result_q, "Scepter", "list_get_str_attr returned the incorrect string for the Queen attribute");
    cr_assert_eq(result_k, "Crown", "list_get_str_attr returned the incorrect string for the King attribute");
    
    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);
    attribute_free(test_attr3);
}

/* Checks retrieval of an integer attribute from a list of attributes */
Test(attribute_list, list_get_int_attr)
{
    attribute_list_t* test_head = create_list_attribute();

    attribute_t *test_attr1 = int_attr_new("Knight", 1);
    attribute_t *test_attr2 = int_attr_new("Queen", 3);
    attribute_t *test_attr3 = int_attr_new("King", 5);

    int add_attribute1 = add_attribute_to_list(test_head, test_attr1);
    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);
    int add_attribute3 = add_attribute_to_list(test_head, test_attr3);

    cr_assert_eq(add_attribute1, SUCCESS,
        "add_attribute_to_list test: attribute Knight not added");
    cr_assert_eq(add_attribute2, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");
    cr_assert_eq(add_attribute3, SUCCESS,
        "add_attribute_to_list test: attribute King not added");
    
    int result_n = list_get_int_attr(test_head, "Knight");
    int result_q = list_get_int_attr(test_head, "Queen");
    int result_k = list_get_int_attr(test_head, "King");

    cr_assert_eq(result_n, 1, "list_get_int_attr returned the incorrect int for the Knight attribute");
    cr_assert_eq(result_q, 3, "list_get_int_attr returned the incorrect int for the Queen attribute");
    cr_assert_eq(result_k, 5, "list_get_int_attr returned the incorrect int for the King attribute");
    
    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);
    attribute_free(test_attr3);
}

/* Checks retrieval of a double attribute from a list of attributes */
Test(attribute_list, list_get_double_attr)
{
    attribute_list_t* test_head = create_list_attribute();

    attribute_t *test_attr1 = double_attr_new("Knight", 1.0);
    attribute_t *test_attr2 = double_attr_new("Queen", 3.0);
    attribute_t *test_attr3 = double_attr_new("King", 5.0);

    int add_attribute1 = add_attribute_to_list(test_head, test_attr1);
    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);
    int add_attribute3 = add_attribute_to_list(test_head, test_attr3);

    cr_assert_eq(add_attribute1, SUCCESS,
        "add_attribute_to_list test: attribute Knight not added");
    cr_assert_eq(add_attribute2, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");
    cr_assert_eq(add_attribute3, SUCCESS,
        "add_attribute_to_list test: attribute King not added");
    
    double result_n = list_get_double_attr(test_head, "Knight");
    double result_q = list_get_double_attr(test_head, "Queen");
    double result_k = list_get_double_attr(test_head, "King");

    cr_assert_eq(result_n, 1.0, "list_get_double_attr returned the incorrect double for the Knight attribute");
    cr_assert_eq(result_q, 3.0, "list_get_double_attr returned the incorrect double for the Queen attribute");
    cr_assert_eq(result_k, 5.0, "list_get_double_attr returned the incorrect double for the King attribute");
    
    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);
    attribute_free(test_attr3);
}

/* Checks retrieval of a char attribute from a list of attributes */
Test(attribute_list, list_get_char_attr)
{
    attribute_list_t* test_head = create_list_attribute();

    attribute_t *test_attr1 = char_attr_new("Knight", 'n');
    attribute_t *test_attr2 = char_attr_new("Queen", 'q');
    attribute_t *test_attr3 = char_attr_new("King", 'k');

    int add_attribute1 = add_attribute_to_list(test_head, test_attr1);
    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);
    int add_attribute3 = add_attribute_to_list(test_head, test_attr3);

    cr_assert_eq(add_attribute1, SUCCESS,
        "add_attribute_to_list test: attribute Knight not added");
    cr_assert_eq(add_attribute2, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");
    cr_assert_eq(add_attribute3, SUCCESS,
        "add_attribute_to_list test: attribute King not added");
    
    char result_n = list_get_char_attr(test_head, "Knight");
    char result_q = list_get_char_attr(test_head, "Queen");
    char result_k = list_get_char_attr(test_head, "King");

    cr_assert_eq(result_n, 'n', "list_get_char_attr returned the incorrect char for the Knight attribute");
    cr_assert_eq(result_q, 'q', "list_get_char_attr returned the incorrect char for the Queen attribute");
    cr_assert_eq(result_k, 'k', "list_get_char_attr returned the incorrect char for the King attribute");
    
    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);
    attribute_free(test_attr3);
}

/* Checks retrieval of a boolean attribute from a list of attributes */
Test(attribute_list, list_get_bool_attr)
{
    attribute_list_t* test_head = create_list_attribute();

    attribute_t *test_attr1 = bool_attr_new("Knight", true);
    attribute_t *test_attr2 = bool_attr_new("Queen", false);
    attribute_t *test_attr3 = bool_attr_new("King", true);

    int add_attribute1 = add_attribute_to_list(test_head, test_attr1);
    int add_attribute2 = add_attribute_to_list(test_head, test_attr2);
    int add_attribute3 = add_attribute_to_list(test_head, test_attr3);

    cr_assert_eq(add_attribute1, SUCCESS,
        "add_attribute_to_list test: attribute Knight not added");
    cr_assert_eq(add_attribute2, SUCCESS,
        "add_attribute_to_list test: attribute Queen not added");
    cr_assert_eq(add_attribute3, SUCCESS,
        "add_attribute_to_list test: attribute King not added");
    
    bool result_n = list_get_bool_attr(test_head, "Knight");
    bool result_q = list_get_bool_attr(test_head, "Queen");
    bool result_k = list_get_bool_attr(test_head, "King");

    cr_assert_eq(result_n, 1, "list_get_bool_attr returned the incorrect bool for the Knight attribute");
    cr_assert_eq(result_q, 0, "list_get_bool_attr returned the incorrect bool for the Queen attribute");
    cr_assert_eq(result_k, 1, "list_get_bool_attr returned the incorrect bool for the King attribute");
    
    delete_attribute_llist(test_head);
    attribute_free(test_attr1);
    attribute_free(test_attr2);
    attribute_free(test_attr3);
}

