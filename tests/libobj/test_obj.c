#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "libobj/obj.h"
#include "common/utlist.h"
#include "common/uthash.h"

int count_attrs(obj_t *obj, char *path, int expected)
{
    int count = 0;

    obj_t *loc = obj_get_attr(obj, path, false);

    cr_assert_eq(loc->type, TYPE_OBJ, "count_attrs needs the object type to be TYPE_OBJ");

    obj_t *curr, *tmp;
    HASH_ITER(hh, loc->data.attr, curr, tmp)
    {
        count++;
    }

    cr_assert_eq(count, expected, 
                 "obj_t '%s' has the wrong number of attrs at '%s'- expected: %d, got %d",
                 obj->id, path, expected, count);
}

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

/* Tests obj_add_attr for an immediate attribute */
Test(test_obj, add_immediate_attr)
{
    obj_t* obj, *tmp;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, ".", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for immediate child failed");
    HASH_FIND_STR(obj->data.attr, id_child, tmp);
    cr_assert_str_eq(tmp->id, id_child, "could not find child");
}

/* Tests obj_add_attr for a nested attribute */
Test(test_obj, add_nested_attr)
{
    obj_t* obj, *tmp0, *tmp1, *tmp2, *tmp3;
    char *id = "test_id";
    char *id_child = "child";
    char *id_intermediate_0 = "intermediate_0";
    char *id_intermediate_1 = "intermediate_1";
    char *id_intermediate_2 = "intermediate_2";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, "intermediate_0.intermediate_1.intermediate_2", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for nested child failed");

    HASH_FIND_STR(obj->data.attr, id_intermediate_0, tmp0);
    cr_assert_str_eq(tmp0->id, id_intermediate_0, "could not find %s attribute", id_intermediate_0);

    HASH_FIND_STR(tmp0->data.attr, id_intermediate_1, tmp1);
    cr_assert_str_eq(tmp1->id, id_intermediate_1, "could not find %s attribute", id_intermediate_1);

    HASH_FIND_STR(tmp1->data.attr, id_intermediate_2, tmp2);
    cr_assert_str_eq(tmp2->id, id_intermediate_2, "could not find %s attribute", id_intermediate_2);

    HASH_FIND_STR(tmp2->data.attr, id_child, tmp3);
    cr_assert_str_eq(tmp3->id, id_child, "could not find child");
}

/* Tests obj_get_attr for an immediate attribute, doesn't create intermediaries */
Test(test_obj, get_immediate_attr_no_create)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, ".", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for immediate child failed");

    obj_t *get_success = obj_get_attr(obj, id_child, false);
    cr_assert_eq(get_success, child, "could not find existing child");

    obj_t *get_fail = obj_get_attr(obj, "nonexistent_id", false);
    cr_assert_eq(get_fail, NULL, "obj_get_attr found a nonexistent object");
}

/* Tests obj_get_attr for a nested attribute, doesn't create intermediaries */
Test(test_obj, get_nested_attr_no_create)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, "intermediate_0.intermediate_1.intermediate_2", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for nested child failed");

    obj_t *get_success = obj_get_attr(obj, "intermediate_0", false);
    cr_assert_neq(get_success, NULL, "could not find existing intermediate child 0");
    obj_t *get_fail = obj_get_attr(obj, "nonexistent_id", false);
    cr_assert_eq(get_fail, NULL, "obj_get_attr found a nonexistent object at intermediate 0 level");

    get_success = obj_get_attr(obj, "intermediate_0.intermediate_1", false);
    cr_assert_neq(get_success, NULL, "could not find existing intermediate child 1");
    get_fail = obj_get_attr(obj, "intermediate_0.nonexistent_id", false);
    cr_assert_eq(get_fail, NULL, "obj_get_attr found a nonexistent object at intermediate 1 level");

    get_success = obj_get_attr(obj, "intermediate_0.intermediate_1.intermediate_2", false);
    cr_assert_neq(get_success, NULL, "could not find existing intermediate child 2");
    get_fail = obj_get_attr(obj, "intermediate_0.intermediate_1.nonexistent_id", false);
    cr_assert_eq(get_fail, NULL, "obj_get_attr found a nonexistent object at intermediate 2 level");

    get_success = obj_get_attr(obj, "intermediate_0.intermediate_1.intermediate_2.child", false);
    cr_assert_eq(get_success, child, "could not find existing intermediate child 0");
    get_fail = obj_get_attr(obj, "intermediate_0.intermediate_1.intermediate_2.nonexistent_id", false);
    cr_assert_eq(get_fail, NULL, "obj_get_attr found a nonexistent object at child level");

    count_attrs(obj, ".", 1);
    count_attrs(obj, "intermediate_0", 1);
    count_attrs(obj, "intermediate_0.intermediate_1", 1);
    count_attrs(obj, "intermediate_0.intermediate_1.intermediate_2", 1);
}

/* Tests obj_get_attr for an immediate attribute, creates intermediaries */
Test(test_obj, get_immediate_attr_create)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, ".", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for immediate child failed");

    obj_t *get_success = obj_get_attr(obj, id_child, false);
    cr_assert_eq(get_success, child, "could not find existing child");

    obj_t *get_new = obj_get_attr(obj, "nonexistent_id", true);
    cr_assert_neq(get_new, NULL, "obj_get_attr did not create a new object");
}

/* Tests obj_get_attr for a nested attribute, creates intermediaries */
Test(test_obj, get_nested_attr_create)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, "intermediate_0.intermediate_1.intermediate_2", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for nested child failed");

    obj_t *get_success = obj_get_attr(obj, "intermediate_0", true);
    cr_assert_neq(get_success, NULL, "could not find existing intermediate child 0");
    obj_t *get_new = obj_get_attr(obj, "nonexistent_id0", true);
    cr_assert_neq(get_new, NULL, "obj_get_attr did not create a new object at intermediate 0 level");

    get_success = obj_get_attr(obj, "intermediate_0.intermediate_1", true);
    cr_assert_neq(get_success, NULL, "could not find existing intermediate child 1");
    get_new = obj_get_attr(obj, "intermediate_0.nonexistent_id0", true);
    cr_assert_neq(get_new, NULL, "obj_get_attr did not create a new object at intermediate 1 level");

    get_success = obj_get_attr(obj, "intermediate_0.intermediate_1.intermediate_2", true);
    cr_assert_neq(get_success, NULL, "could not find existing intermediate child 2");
    get_new = obj_get_attr(obj, "intermediate_0.intermediate_1.nonexistent_id1", true);
    cr_assert_neq(get_new, NULL, "obj_get_attr did not create a new object at intermediate 2 level");

    get_success = obj_get_attr(obj, "intermediate_0.intermediate_1.intermediate_2.child", true);
    cr_assert_eq(get_success, child, "could not find existing intermediate child 0");
    get_new = obj_get_attr(obj, "intermediate_0.intermediate_1.intermediate_2.nonexistent_id2", true);
    cr_assert_neq(get_new, NULL, "obj_get_attr did not create a new object at child level");

    count_attrs(obj, ".", 2);
    count_attrs(obj, "intermediate_0", 2);
    count_attrs(obj, "intermediate_0.intermediate_1", 2);
    count_attrs(obj, "intermediate_0.intermediate_1.intermediate_2", 2);
}

void get_test(obj_t *parent, obj_t *expected, char *path)
{
    obj_t *get_success = obj_get_attr(parent, path, false);
    cr_assert_eq(get_success, expected, "get for path '%s' failed", path);
}

/* Tests obj_get_attr get syntax */
Test(test_obj, get_syntax)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, "0.1.2", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for nested child failed");

    obj_t *get_success = obj_get_attr(obj, "self", false);
    cr_assert_eq(get_success, obj, "could not get self");

    get_test(obj, obj, "self");
    get_test(obj, obj, ".");
    get_test(obj, obj, ".....");
    get_test(obj, obj, "self.self.self");
    get_test(obj, obj, "...self...self.self");
    get_test(obj, obj, "...self...self.self.");
    get_test(obj, obj, "");

    get_test(obj, child, "0.1.2.child");
    get_test(obj, child, "...0.1...2...child..");
    get_test(obj, child, "self..0...1..2...child..");
    get_test(obj, child, ".self..0.1...2...child.");

    get_test(obj, NULL, "na");
    get_test(obj, NULL, ".na..");
    get_test(obj, NULL, "self.0.1.2.child.na");
    get_test(obj, NULL, "self.0.1.2.child.na");
    get_test(obj, NULL, "self.0.1.2.child.ads");
}

/* Tests obj_remove_attr for an immediate attribute, doesn't free */
Test(test_obj, remove_immediate_no_free)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, ".", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for immediate child failed");
    count_attrs(obj, ".", 1);

    rc = obj_remove_attr(obj, id_child, false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for immediate child failed");

    rc = obj_remove_attr(obj, id_child, false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for immediate child 2 failed");

    rc = obj_remove_attr(obj, "na", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for immediate child failed");

    count_attrs(obj, ".", 0);
}

/* Tests obj_remove_attr for a nested attribute, doesn't free */
Test(test_obj, remove_nested_no_free)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, "intermediate_0.intermediate_1.intermediate_2", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for nested child failed");

    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2.child", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for child failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2.child", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for child 2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2.nonexistent_id2", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent child failed");
    count_attrs(obj, "intermediate_0.intermediate_1.intermediate_2", 0);

    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_2 2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.nonexistent_id2", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent intermediate_2 failed");
    count_attrs(obj, "intermediate_0.intermediate_1", 0);

    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_1 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_1 2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.nonexistent_id1", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent intermediate_1 failed");
    count_attrs(obj, "intermediate_0", 0);

    rc = obj_remove_attr(obj, "intermediate_0", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_0 failed");
    rc = obj_remove_attr(obj, "intermediate_0", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_0 2 failed");
    rc = obj_remove_attr(obj, "nonexistent_id0", false);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent intermediate_0 failed");
    count_attrs(obj, ".", 0);
}

/* Tests obj_remove_attr for an immediate attribute, frees */
Test(test_obj, remove_immediate_free)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, ".", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for immediate child failed");
    count_attrs(obj, ".", 1);

    rc = obj_remove_attr(obj, id_child, true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for immediate child failed");

    rc = obj_remove_attr(obj, id_child, true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for immediate child 2 failed");

    rc = obj_remove_attr(obj, "na", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for immediate child failed");

    count_attrs(obj, ".", 0);
}

/* Tests obj_remove_attr for a nested attribute, frees */
Test(test_obj, remove_nested_free)
{
    obj_t* obj;
    char *id = "test_id";
    char *id_child = "child";

    obj = obj_new(id);
    obj_t *child = obj_new(id_child);

    cr_assert_not_null(obj, "obj_new failed");
    cr_assert_not_null(child, "obj_new failed");

    int rc = obj_add_attr(obj, "intermediate_0.intermediate_1.intermediate_2", child);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_add_attr for nested child failed");

    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2.child", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for child failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2.child", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for child 2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2.nonexistent_id2", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent child failed");
    count_attrs(obj, "intermediate_0.intermediate_1.intermediate_2", 0);

    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.intermediate_2", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_2 2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1.nonexistent_id2", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent intermediate_2 failed");
    count_attrs(obj, "intermediate_0.intermediate_1", 0);

    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_1 failed");
    rc = obj_remove_attr(obj, "intermediate_0.intermediate_1", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_1 2 failed");
    rc = obj_remove_attr(obj, "intermediate_0.nonexistent_id1", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent intermediate_1 failed");
    count_attrs(obj, "intermediate_0", 0);

    rc = obj_remove_attr(obj, "intermediate_0", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_0 failed");
    rc = obj_remove_attr(obj, "intermediate_0", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for intermediate_0 2 failed");
    rc = obj_remove_attr(obj, "nonexistent_id0", true);
    cr_assert_eq(rc, EXIT_SUCCESS, "obj_remove_attr for nonexistent intermediate_0 failed");
    count_attrs(obj, ".", 0);
}
