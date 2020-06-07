#include <criterion/criterion.h>
#include "test_wdl.h"
#include "wdl/attributes.h"

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

Test(attributes, append)
{
    obj_attr_t *item1 = new_attr("skill", "water magic");
    cr_assert_not_null(prev, "new_attr() failed to init & alloc attr");
    
    obj_attr_t *item2 = new_attr("skill", "welding");
    cr_assert_not_null(prev, "new_attr() failed to init & alloc attr");
    
    obj_attr_t *item3 = new_attr("skill", "underwater basket-weaving");
    cr_assert_not_null(prev, "new_attr() failed to init & alloc attr");

    append_attr(item1, item2);
    cr_assert_eq(item1->next, item2, "append_attr() failed to assign next");
    cr_assert_eq(item2->prev, item1, "append_attr() failed to assign prev");

    append_attr(item2, item3);
    cr_assert_eq(item2->next, item3, "append_attr() failed to assign next");
    cr_assert_eq(item3->prev, item2, "append_attr() failed to assign prev");
}

Test(attributes, free)
{
    obj_attr_t *attrs = NULL;

    obj_attr_t *new = add_attribute(&attrs, "class", "adventurer");
    cr_assert_not_null(attrs, "add_attr() failed to add attr");

    int res = free_attr(&attrs,new);
    cr_assert_eq(res, SUCCESS, "free_attr() failed");
}