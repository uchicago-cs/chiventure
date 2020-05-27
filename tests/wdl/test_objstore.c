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
    obj_t *test = malloc(sizeof(obj_t));
    strcpy(test->id, "villager");
    test->type = 6;
    test->attrs = NULL;

    objstore_t *store = NULL;
    add_objstore(&store, test);
    cr_assert_not_null(store, "add_objstore() failed");

    objstore_t *res = find_objstore(&store, "robber", 6);
    cr_assert_null(res, "find_objstore() failed - returned value when NULL expected");
}

Test(objstore, find_failure_empty)
{
    objstore_t *test = NULL;
    objstore_t *res = find_objstore(&test, "Room B", 2);
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
    cr_assert_not_null(store, "add_objstore() failed");

    objstore_t *res = find_objstore(&store, "villager", 6);
    cr_assert_not_null(res, "find_objstore() failed - returned NULL when value expected");
}

Test(objstore, add_new)
{
    obj_t *old = malloc(sizeof(obj_t));
    strcpy(old->id, "villager");
    old->type = 6;
    old->attrs = malloc(sizeof(attribute_t));

    obj_t *new = malloc(sizeof(obj_t));
    strcpy(new->id, "robber");
    new->type = 6;
    new->attrs = malloc(sizeof(attribute_t));

    objstore_t *store = NULL;
    add_objstore(&store, old);
    add_objstore(&store, new);

    objstore_t *res = find_objstore(&store, new->id, new->type);

    cr_assert_not_null(res, "add_objstore() failed to add obj to nonempty hash");
}

Test(objstore, add_new_empty)
{  
    obj_t *test = malloc(sizeof(obj_t));
    strcpy(test->id, "villager");
    test->type = 6;
    objstore_t *res = NULL;
    add_objstore(&res, test);

    cr_assert_not_null(res, "add_objstore() failed to add item");
}

Test(objstore, add_NULL)
{  
    obj_t *obj = NULL;
    objstore_t *store = NULL;
    int res = add_objstore(&store, obj);

    cr_assert_eq(res, FAILURE, "add_objstore() added NULL object");
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

Test(objstore, free)
{
    obj_t *obj = malloc(sizeof(obj_t));
    strcpy(obj->id, "villager");
    obj->type = 6;

    objstore_t *store = new_objstore(obj);
    cr_assert_not_null(store, "new_objstore() failed");

    int res = free_objstore(&store, store);
    cr_assert_eq(res, SUCCESS, "free_objstore() failed");
}

Test(objstore, free_all)
{
    obj_t *old = malloc(sizeof(obj_t));
    strcpy(old->id, "villager");
    old->type = 6;

    obj_t *new = malloc(sizeof(obj_t));
    strcpy(new->id, "robber");
    new->type = 6;

    objstore_t *store = NULL;
    add_objstore(&store, old);
    add_objstore(&store, new);

    int res = free_all(&store);
    cr_assert_eq(res, SUCCESS, "free_all() failed");
}