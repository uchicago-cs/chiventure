#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "libobj/obj.h"
#include "common/utlist.h"

/* Tests obj_new */
Test(test_obj, new)
{
    obj_t* obj;
    char *id = "test_id";

    obj = obj_new(id);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_str_eq(obj->id, id, "obj_new didn't set id");
    cr_assert_eq(obj->type, TYPE_NONE, "obj_new didn't set type");
}

/* Tests obj_init */
Test(test_obj, init)
{
    obj_t obj;
    char *id = "test_id";

    int rc = obj_init(&obj, id);

    cr_assert_eq(rc, EXIT_SUCCESS, "obj_init failed");
    cr_assert_str_eq(obj.id, id, "obj_init didn't set name");
    cr_assert_eq(obj.type, TYPE_NONE, "obj_init didn't set type");
}

/* Tests obj_free */
Test(test_obj, free)
{
    obj_t* obj;
    char *id = "test_id";

    obj = obj_new(id);

    cr_assert_not_null(obj, "obj_new failed");

    int rc = obj_free(obj);

    cr_assert_eq(rc, EXIT_SUCCESS, "obj_free failed");
}

/* Tests obj_free_all */
Test(test_obj, free_all)
{
    obj_t* obj;
    char *id = "test_id";

    obj = obj_new(id);
    obj_t *child = obj_new("child");

    obj_list_t *lst = NULL;
    DL_APPEND(lst, obj_new("list"));

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    obj_add_attr(obj, "child", child);
    obj_set_list(obj, "lst", lst);

    int rc = obj_free_all(obj);

    cr_assert_eq(rc, EXIT_SUCCESS, "obj_free_all failed");
}

/* Tests obj_add_attr */
Test(test_obj, add_attr)
{
    obj_t* obj, *tmp0, *tmp1;
    char *id = "test_id";
    char *id0 = "child0";
    char *id1 = "child1";
    char *id_children = "children";

    obj = obj_new(id);
    obj_t *child0 = obj_new(id0);
    obj_t *child1 = obj_new(id1);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child0, "obj_new failed");
    cr_assert_not_null(child1, "obj_new failed");

    int rc = obj_add_attr(obj, "child0", child0);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for immediate child failed");
    HASH_FIND_STR(obj->data.attr, id0, tmp0);
    cr_assert_str_eq(tmp0->id, id0, "could not find child0");

    rc = obj_add_attr(obj, "children.child1", child1);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for nested child failed");
    HASH_FIND_STR(obj->data.attr, id_children, tmp0);
    cr_assert_str_eq(tmp0->id, id_children, "could not children attribute");
    HASH_FIND_STR(tmp0->data.attr, id1, tmp1);
    cr_assert_str_eq(tmp1->id, id1, "could not find child0");
}

