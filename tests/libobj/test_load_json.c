#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "libobj/obj.h"
#include "libobj/load_json.h"
#include "common/utlist.h"
#include "common/uthash.h"

/* Tests load_json for bools */
Test(test_load_json, load_bool)
{
    obj_t *obj = obj_new("test_id");

    json_object *data = json_object_new_boolean(true);

    int rc = _load_obj_json(obj, data);

    cr_assert_eq(rc, EXIT_SUCCESS, "_load_obj_json failed");

    bool val = obj_get_bool(obj, ".");
    cr_assert_eq(val, true, "_load_obj_json didn't return the correct value");
}

/* Tests load_json for ints */
Test(test_load_json, load_int)
{
    obj_t *obj = obj_new("test_id");

    json_object *data = json_object_new_int(10);

    int rc = _load_obj_json(obj, data);

    cr_assert_eq(rc, EXIT_SUCCESS, "_load_obj_json failed");

    int val = obj_get_int(obj, ".");
    cr_assert_eq(val, 10, "_load_obj_json didn't return the correct value");
}

/* Tests load_json for strings */
Test(test_load_json, load_str)
{
    obj_t *obj = obj_new("test_id");

    json_object *data = json_object_new_string("test_string");

    int rc = _load_obj_json(obj, data);

    cr_assert_eq(rc, EXIT_SUCCESS, "_load_obj_json failed");

    char *val = obj_get_str(obj, ".");
    cr_assert_str_eq(val, "test_string", "_load_obj_json didn't return the correct value");
}

/* Tests load_json for objects */
Test(test_load_json, load_obj)
{
    obj_t *obj = obj_new("test_id");

    json_object *json = json_object_new_object();
    json_object *data0 = json_object_new_int(10);
    json_object_object_add(json, "data0", data0);
    json_object *data1 = json_object_new_boolean(true);
    json_object_object_add(json, "data1", data1);

    int rc = _load_obj_json(obj, json);

    cr_assert_eq(rc, EXIT_SUCCESS, "_load_obj_json failed");

    int val0 = obj_get_int(obj, "data0");
    cr_assert_eq(val0, 10, "_load_obj_json didn't return the correct value");

    bool val1 = obj_get_bool(obj, "data1");
    cr_assert_eq(val1, true, "_load_obj_json didn't return the correct value");
}

/* Tests load_json for lists */
Test(test_load_json, load_list)
{
    obj_t *obj = obj_new("test_id");

    json_object *json = json_object_new_array();
    json_object *data0 = json_object_new_int(10);
    json_object_array_add(json, data0);
    json_object *data1 = json_object_new_boolean(true);
    json_object_array_add(json, data1);

    int rc = _load_obj_json(obj, json);

    cr_assert_eq(rc, EXIT_SUCCESS, "_load_obj_json failed");

    obj_list_t *lst = obj_get_list(obj, ".");

    obj_t *cur = lst;
    int val0 = obj_get_int(cur, ".");
    cr_assert_eq(val0, 10, "_load_obj_json didn't return the correct value");

    cur = cur->next;
    bool val1 = obj_get_bool(cur, ".");
    cr_assert_eq(val1, true, "_load_obj_json didn't return the correct value");

    cr_assert_null(cur->next, "_load_obj_json didn't return the correct value");
}
