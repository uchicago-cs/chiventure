#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "custom-scripts/custom_type.h"

/** Checks that the object_t struct contains the right data when obj_t_new() called
 */
Test(custom_type, obj_t_new)
{
    object_t *ot = obj_t_new();
    cr_assert_eq(ot->type, NONE_TYPE, "obj_t_new: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_new: failed is_lua assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in a bool to obj_t_bool()
 */
Test(custom_type, obj_t_new_bool)
{
    object_t *ot = obj_t_bool(true, NULL);
    cr_assert_eq(ot->type, BOOL_TYPE, "obj_t_bool: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_bool: failed is_lua assignment");
    cr_assert_eq(ot->data.b, true, "obj_t_bool: failed bool assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_bool()
 */
Test(custom_type, obj_t_new_bool_lua)
{   
    object_t *ot = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_test.lua");
    cr_assert_eq(ot->type, BOOL_TYPE, "obj_t_bool: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_bool: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/bool_test.lua",
        "obj_t_bool: failed Lua assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in a char to obj_t_char()
 */
Test(custom_type, obj_t_new_char)
{
    object_t *ot = obj_t_char('a', NULL);
    cr_assert_eq(ot->type, CHAR_TYPE, "obj_t_char: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_char: failed is_lua assignment");
    cr_assert_eq(ot->data.c, 'a', "obj_t_char: failed char assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_char()
 */
Test(custom_type, obj_t_new_char_lua)
{   
    object_t *ot = obj_t_char('a', "../../../tests/custom-scripts/Lua_file/char_test.lua");
    cr_assert_eq(ot->type, CHAR_TYPE, "obj_t_char: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_char: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/char_test.lua",
        "obj_t_char: failed Lua assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in an integer to obj_t_int()
 */
Test(custom_type, obj_t_new_int)
{
    object_t *ot = obj_t_int(10, NULL);
    cr_assert_eq(ot->type, INT_TYPE, "obj_t_int: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_int: failed is_lua assignment");
    cr_assert_eq(ot->data.i, 10, "obj_t_int: failed integer assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_int()
 */
Test(custom_type, obj_t_new_int_lua)
{   
    object_t *ot = obj_t_int(10, "../../../tests/custom-scripts/Lua_file/int_test.lua");
    cr_assert_eq(ot->type, INT_TYPE, "obj_t_int: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_int: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/int_test.lua",
        "obj_t_int: failed Lua assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in a str to obj_t_str()
 */
Test(custom_type, obj_t_new_str)
{
    object_t *ot = obj_t_str("testing", NULL);
    cr_assert_eq(ot->type, STR_TYPE, "obj_t_str: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_str: failed is_lua assignment");
    cr_assert_eq(ot->data.s, "testing", "obj_t_str: failed str assignment");
}

/** Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_str()
 */
Test(custom_type, obj_t_new_str_lua)
{   
    object_t *ot = obj_t_str("testing", "../../../tests/custom-scripts/Lua_file/string_test.lua");
    cr_assert_eq(ot->type, STR_TYPE, "obj_t_str: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_str: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/string_test.lua",
        "obj_t_str: failed Lua assignment");
}


/** Checks that the object_t struct returns the correct bool value (direct)
 */
Test(custom_type, obj_t_get_bool)
{
    object_t *ot = obj_t_bool(true, NULL);
    bool rv = bool_t_get(ot);
    cr_assert_eq(rv, true, "obj_t_get_bool: failed bool direct retrieval");
}


/** Checks that the object_t struct returns the correct bool value (lua)
 */
Test(custom_type, obj_t_get_bool_lua)
{
    object_t *ot = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_test.lua");
    bool rv = bool_t_get(ot);
    cr_assert_eq((rv ? 1 : 0), 0, "bool_t_get: failed bool Lua retrieval");

}

/** Checks that the object_t struct returns the correct char value (direct)
 */
Test(custom_type, obj_t_get_char)
{
    object_t *ot = obj_t_char('a', NULL);
    char rv = char_t_get(ot);
    cr_assert_eq(rv, 'a', "obj_t_get_char: failed char direct retrieval");
}


/** Checks that the object_t struct returns the correct char value (lua)
 */
Test(custom_type, obj_t_get_char_lua)
{
    object_t *ot = obj_t_char('a', "../../../tests/custom-scripts/Lua_file/char_test.lua");
    char rv = char_t_get(ot);
    cr_assert_eq(rv, 'b', "obj_t_get_char: failed char direct retrieval");
}


/** Checks that the object_t struct returns the correct int value (direct)
 */
Test(custom_type, obj_t_get_int)
{
    object_t *ot = obj_t_int(123, NULL);
    int rv = int_t_get(ot);
    cr_assert_eq(rv, 123, "obj_t_get_int: failed int direct retrieval");
}


/** Checks that the object_t struct returns the correct int value (lua)
 */
Test(custom_type, obj_t_get_int_lua)
{
    object_t *ot = obj_t_int(10, "../../../tests/custom-scripts/Lua_file/int_test.lua");
    int rv = int_t_get (ot);
    cr_assert_eq(rv, 15, "int_t_get: failed int Lua retrieval");
}


/** Checks that the object_t struct returns the correct str value (direct)
 */
Test(custom_type, obj_t_get_str)
{
    object_t *ot = obj_t_str("testing", NULL);
    char *rv = str_t_get(ot);
    cr_assert_eq(rv, "testing", "obj_t_get_str: failed str direct retrieval");
}

/** Checks that the object_t struct returns the correct str value (lua)
 */
Test(custom_type, obj_t_get_str_lua)
{
    object_t *ot = obj_t_str("testing_failed", "../../../tests/custom-scripts/Lua_file/string_test.lua");
    char *rv = str_t_get(ot);
    int result = strcmp(rv, "testing_succeeded");
    cr_assert_eq(result, 0, "string_t_get: failed string Lua retrieval");
}
