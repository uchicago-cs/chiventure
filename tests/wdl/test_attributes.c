#include <criterion/criterion.h>
#include "test_wdl.h"
#include "wdl/attributes.h"


/* ---------- HASH FUNCTIONS ---------- */

Test(attributes, new_failure)
{
    int data = 100;
    obj_attr_t *res = new_attr(NULL, &data);
    cr_assert_null(res, "new_attr() failed - returned value when NULL expected");
}

Test(attributes, new_success)
{
    int d1 = 1;
    obj_attr_t *prev = new_attr("xp", &d1);
    cr_assert_not_null(prev, "new_attr() failed to init & alloc attr");

    obj_attr_t *next = new_attr("class", "knight");
    cr_assert_not_null(prev, "new_attr() failed to init & alloc attr");

    bool d2 = false;
    obj_attr_t *res = new_attr("alive?", &d2);
    cr_assert_not_null(prev, "new_attr() failed to init & alloc attr");
}

Test(attributes, find_failure)
{
    obj_attr_t *test = NULL;
    add_attribute(&test, "class", "thief");

    obj_attr_t *res = find_attr(&test, "mana");
    cr_assert_null(res, "find_attr() failed - returned value when NULL expected");
    
}

Test(attributes, find_failure_empty)
{
    obj_attr_t *test = NULL;
    obj_attr_t *res = find_attr(&test, "xp");

    cr_assert_null(res, "find_attr() failed - returned value when NULL expected");
}

Test(attributes, find_success)
{
    obj_attr_t *test = NULL;
    add_attribute(&test,"race", "orc");
    cr_assert_not_null(test, "add_attr() failed to add attr");
    
    obj_attr_t *res = find_attr(&test, "race");
    cr_assert_not_null(res, "find_attr() failed - returned NULL when value expected");
}

Test(attributes, add_new)
{
    obj_attr_t *attrs = NULL;

    int data = 1;
    add_attribute(&attrs, "xp", &data);
    add_attribute(&attrs, "class", "thief");

    obj_attr_t *res = find_attr(&attrs, "class");
    cr_assert_not_null(res, "add_attribute() failed to add obj to nonempty hash");
}

Test(attributes, add_new_empty)
{
    obj_attr_t *test = NULL;
    add_attribute(&test, "class", "thief");
    cr_assert_not_null(test, "add_attribute() failed to add attr");
}

Test(attributes, add_NULL)
{
    obj_attr_t *test = NULL;

    add_attribute(&test, NULL, NULL);
    cr_assert_null(test, "add_attribute() failed - added NULL");
}

Test(attributes, add_replace)
{
    obj_attr_t *attrs = NULL;
    
    add_attribute(&attrs, "class", "adventurer");
    add_attribute(&attrs, "class", "mage");

    cr_assert_eq(strcmp("class", attrs->id), 0, "add_attribute() failed - didn't replace item");
}

Test(attributes, free_hash)
{
    obj_attr_t *attrs = NULL;
    
    obj_attr_t *item1 = add_attribute(&attrs, "class", "adventurer");
    obj_attr_t *item2 = add_attribute(&attrs, "class", "mage");
    
    obj_attr_t *head = init_attr_list(item1);
    obj_attr_t *item3 = new_attr("weapon", "sword");
    append_attr(head, item3);
    cr_assert_eq(item1->next, item3, "append_attr() failed to assign next");

    int res = free_attr_hash(&attrs);
    cr_assert_eq(res, 0, "free_attr_hash() failed");
}


/* ---------- LINKED LIST FUNCTIONS ---------- */

Test(attributes, init_list)
{
    obj_attr_t *test = new_attr("skill", "water magic");
    obj_attr_t *res = init_attr_list(test);
    cr_assert_not_null(res, "init_attr_list() failed");
}

Test(attributes, append)
{
    obj_attr_t *item1 = new_attr("skill", "water magic");
    cr_assert_not_null(item1, "new_attr() failed to init & alloc attr");
    
    obj_attr_t *item2 = new_attr("skill", "welding");
    cr_assert_not_null(item2, "new_attr() failed to init & alloc attr");
    
    obj_attr_t *item3 = new_attr("skill", "underwater basket-weaving");
    cr_assert_not_null(item3, "new_attr() failed to init & alloc attr");

    obj_attr_t *head = init_attr_list(item1);
    cr_assert_not_null(head, "init_attr_list() failed");

    append_attr(head, item2);
    cr_assert_eq(item1->next, item2, "append_attr() failed to assign next");
    cr_assert_eq(item2->prev, item1, "append_attr() failed to assign prev");

    append_attr(head, item3);
    cr_assert_eq(item2->next, item3, "append_attr() failed to assign next");
    cr_assert_eq(item3->prev, item2, "append_attr() failed to assign prev");
}

Test(attributes, count)
{
    obj_attr_t *item1 = new_attr("class", "monster");
    obj_attr_t *item2 = new_attr("skill", "fire magic");

    item1->next = item2;
    item2->prev = item1;

    int res = count_attr_list(item1);
    cr_assert_eq(res, 2, "count_attr_list() failed");
}

Test(attributes, free)
{
    obj_attr_t *item1 = new_attr("class", "adventurer");
    cr_assert_not_null(item1, "new_attr() failed to init & alloc attr");

    obj_attr_t *head = init_attr_list(item1);
    obj_attr_t *item2 = new_attr("weapon", "stick");
    append_attr(head, item2);

    int res = free_attr(head, item2);
    cr_assert_eq(res, SUCCESS, "free_attr() failed");
}

Test(attributes, free_list)
{
    obj_attr_t *attrs = NULL;

    obj_attr_t *item1 = new_attr("skill", "water magic");
    cr_assert_not_null(item1, "new_attr() failed to init & alloc attr");
    
    obj_attr_t *item2 = new_attr("skill", "welding");
    cr_assert_not_null(item2, "new_attr() failed to init & alloc attr");
    
    obj_attr_t *item3 = new_attr("skill", "underwater basket-weaving");
    cr_assert_not_null(item3, "new_attr() failed to init & alloc attr");

    obj_attr_t *head = init_attr_list(item1);
    append_attr(head, item2);
    cr_assert_eq(item1->next, item2, "append_attr() failed to assign next");
    append_attr(head, item3);
    cr_assert_eq(item2->next, item3, "append_attr() failed to assign next");

    int res = free_attr_list(&attrs, head);

    cr_assert_eq(res, SUCCESS, "free_attr_list() failed");
}


/* ---------- INTERFACE FUNCTIONS ---------- */

Test(attributes, get_id)
{
    obj_attr_t *test = new_attr("class", "adventurer");
    char *res = get_attr_id(test);

    cr_assert_eq(strcmp(res, "class"), 0, "get_attr_id() failed");
}

Test(attributes, get_data)
{
    obj_attr_t *test = new_attr("class", "adventurer");
    char *res = get_attr_data(test);

    cr_assert_eq(strcmp(res, "adventurer"), 0, "get_attr_data() failed");
}

Test(attributes, get_next)
{
    obj_attr_t *item1 = new_attr("class", "adventurer");
    obj_attr_t *item2 = new_attr("weapon", "shield");
    item1->next = item2;
    item2->prev = item1;
    obj_attr_t *res = get_next_attr(item1);

    cr_assert_eq(res, item2, "get_attr_next() failed");
}

Test(attributes, get_prev)
{
    obj_attr_t *item1 = new_attr("class", "adventurer");
    obj_attr_t *item2 = new_attr("weapon", "shield");
    item1->prev = item2;
    item2->next = item1;
    obj_attr_t *res = get_prev_attr(item1);

    cr_assert_eq(res, item2, "get_attr_prev() failed");
}
