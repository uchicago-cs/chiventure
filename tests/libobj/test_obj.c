#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "libobj/obj.h"

/* Tests class_new */
Test(test_obj, new)
{
    obj_t* obj;
    char *id = "test_id";

    obj = obj_new(id);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_str_eq(obj->id, id, "obj_new didn't set id");
    cr_assert_eq(obj->type, TYPE_NONE, "obj_new didn't set type");
}

/* Tests class_init */
Test(test_obj, init)
{
    obj_t obj;
    char *id = "test_id";

    int rc = obj_init(&obj, id);

    cr_assert_eq(rc, EXIT_SUCCESS, "obj_init failed");
    cr_assert_str_eq(obj.id, id, "obj_init didn't set name");
    cr_assert_eq(obj.type, TYPE_NONE, "obj_init didn't set type");
}

/* Tests class_free */
Test(test_obj, free)
{
    obj_t* obj;
    char *id = "test_id";

    obj = obj_new(id);

    cr_assert_not_null(obj, "obj_new failed");

    int rc = obj_free(obj);

    cr_assert_eq(rc, EXIT_SUCCESS, "obj_new failed");
}
