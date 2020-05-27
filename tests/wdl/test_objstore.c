#include <criterion/criterion.h>
#include "test_wdl.h"
#include "wdl/objstore.h"

Test(objstore, new_failure)
{
    obj_t *test = NULL;
    objstore_t *res = new_objstore(test);
    cr_assert_null(res, "new_objstore() failed");
}

Test(objstore, new_success)
{
    obj_t *test = malloc(sizeof(obj_t));
    strcpy(test->id, "villager");
    test->type = 6;
    objstore_t *res = new_objstore(test);
    cr_assert_not_null(res, "new_objstore() failed");
}

Test(objstore, find_failure)
{
    objstore_t *test = NULL;
    objstore_t *res = find_objstore(&test, 2, "Room B");
    cr_assert_null(res, "find_objstore() failed - returned value when NULL expected");
}

Test(objstore, find_success)
{
    obj_t *test = malloc(sizeof(obj_t));
    strcpy(test->id, "villager");
    test->type = 6;
    test->attrs = NULL;

    objstore_t *store = NULL;
    add_objstore(&store, test);

    objstore_t *res = find_objstore(&store, 6, "villager");
    cr_assert_not_null(res, "find_objstore() failed - returned NULL when value expected");
}

Test(objstore, add_new)
{  
    obj_t *test = malloc(sizeof(obj_t));
    strcpy(test->id, "villager");
    test->type = 6;
    objstore_t *res = NULL;
    add_objstore(&res, test);

    cr_assert_not_null(test, "add_objstore() failed to add item");
}

Test(objstore, add_replace)
{
    // if key is not unique, add_objstore will replace o value with given value
    obj_t *old = malloc(sizeof(obj_t));
    strcpy(old->id, "villager");
    old->type = 6;
    old->attrs = malloc(sizeof(attribute_t));
    strcpy(old->attrs->id, "health");

    obj_t *new = malloc(sizeof(obj_t));
    strcpy(new->id, "villager");
    new->type = 6;
    new->attrs = malloc(sizeof(attribute_t));
    strcpy(new->attrs->id, "mana");

    objstore_t *res = NULL;
    add_objstore(&res, old);
    add_objstore(&res, new);

    cr_assert_eq(strcmp(res->o->attrs->id, new->attrs->id), 0, "add_objstore() failed to replace item with same key");
    
}
