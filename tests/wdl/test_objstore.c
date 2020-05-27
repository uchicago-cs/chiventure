#include <criterion/criterion.h>
#include "test_wdl.h"
#include "./../src/libobj/sandbox/objstore.h"

Test(objstore, new)
{
    obj_t *test;
    strcpy(test->id, "villager");
    test->type = 6;
    objstore_t *res = new_objstore(test);
    cr_assert_not_null(res, "new_objstore() failed");
}

Test(objstore, find_failure)
{
    objstore_t *test = NULL;
    objstore_t *res = find_objstore(2, "Room B");
    cr_assert_null(res, "find_objstore() failed - returned value when NULL expected");
}

Test(objstore, find_success)
{
    objstore_t *test;
    strcpy(test->key.id, "villager");
    test->key.type = 6;
    objstore_t *res = find_objstore(6, "villager");
    cr_assert_not_null(res, "find_objstore() failed - returned NULL when value expected");
}