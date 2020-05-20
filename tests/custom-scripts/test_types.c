#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "custom-scripts/custom_types.h"

/** Checks that the int_t struct contains the right data when passed
 * in an integer to int_t_new()
 */
Test(custom_types, int_t_new_int)
{
    int_t it = int_t_new(10, NULL);
    cr_assert_eq(it.isInt, 1, "int_t_new: failed isInt assignment");
    cr_assert_eq(it.p.i, 10, "int_t_new: failed integer assignment");
}

/** Checks that the int_t struct contains the right data when passed
 * in a lua directory to int_t_new()
 */
Test(custom_types, int_t_new_lua)
{
    int_t it = int_t_new(0, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
    cr_assert_eq(it.isInt, 0, "int_t_new: failed isInt assignment");
    cr_assert_eq(it.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/int_t_test.lua", "int_t_new: failed lua assignment");
}

/** Checks that the int_t struct contains the right data when passed
 * in an integer to int_t_init()
 */
Test(custom_types, int_t_init_int)
{
    int_t it;
    it = int_t_init(it, 10, NULL);
    cr_assert_eq(it.isInt, 1, "int_t_init: failed isInt assignment");
    cr_assert_eq(it.p.i, 10, "int_t_init: failed integer assignment");
}

/** Checks that the int_t struct contains the right data when passed
 * in a lua directory to int_t_init()
 */
Test(custom_types, int_t_init_lua)
{
    int_t it;
    it = int_t_init(it, 0, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
    cr_assert_eq(it.isInt, 0, "int_t_init: failed isInt assignment");
    cr_assert_eq(it.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/int_t_test.lua", "int_t_init: failed lua assignment");
}

/** Checks that the int_t struct returns the correct integer value (direct)
 */
Test(custom_types, int_t_get_int)
{
    int_t it = int_t_new(10, NULL);
    int rv = int_t_get(it);
    cr_assert_eq(rv, 10, "int_t_get: failed int direct retrieval");
}


/** Checks that the int_t struct returns the correct integer value (lua)
 */
Test(custom_types, int_t_get_lua)
{
    int_t it = int_t_new(10, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
    int rv = int_t_get (it);
    cr_assert_eq(rv, 15, "int_t_get: failed int Lua retrieval");
}

/** Checks that the bool_t struct contains the right data when passed
 * in a bool to bool_t_new()
 */
Test(custom_types, bool_t_new_bool)
{
    bool_t bt = bool_t_new(false, NULL);
    cr_assert_eq(bt.isBool, 1, "bool_t_new: failed isBool assignment");
    cr_assert_eq(bt.p.luaDirectory, false, "bool_t_new: failed bool assignment");
}

/** Checks that the bool_t struct contains the right data when passed
 * in a lua directory to bool_t_new()
 */
Test(custom_types, bool_t_new_lua)
{
    bool_t bt = bool_t_new(false, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
    cr_assert_eq(bt.isBool, 0, "bool_t_new: failed isBool assignment");
    cr_assert_eq(bt.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua", "bool_t_new: failed lua assignment");
}

/** Checks that the bool_t struct contains the right data when passed
 * in a bool to bool_t_init()
 */
Test(custom_types, bool_t_init_int)
{
    bool_t bt;
    bt = bool_t_init(bt, true, NULL);
    cr_assert_eq(bt.isBool, 1, "bool_t_init: failed isBool assignment");
    cr_assert_eq(bt.p.b, true, "bool_t_init: failed isBool assignment");
}

/** Checks that the bool_t struct contains the right data when passed
 * in a lua directory to bool_t_init()
 */
Test(custom_types, bool_t_init_lua)
{
    bool_t bt;
    bt = bool_t_init(bt, false, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
    cr_assert_eq(bt.isBool, 0, "bool_t_init: failed isBool assignment");
    cr_assert_eq(bt.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua", "bool_t_init: failed lua assignment");
}

/** Checks that the bool_t struct returns the correct boolean value (direct)
 */
Test(custom_types, bool_t_get_bool)
{
    bool_t bt = bool_t_new(true, NULL);
    bool rv = bool_t_get(bt);
    cr_assert_eq((rv ? 1 : 0), 1, "bool_t_get: failed bool direct retrieval");
}


/** Checks that the bool_t struct returns the correct boolean value (lua)
 */
Test(custom_types, bool_t_get_lua)
{
    bool_t bt = bool_t_new(true, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
    bool rv = bool_t_get(bt);
    cr_assert_eq((rv ? 1 : 0), 0, "bool_t_get: failed bool Lua retrieval");
}

/** Checks that the string_t struct contains the right data when passed
 * in a string to string_t_new()
 */
Test(custom_types, string_t_new_string)
{
    string_t st = string_t_new("testing", NULL);
    cr_assert_eq(st.isString, 1, "string_t_new: failed isString assignment");
    cr_assert_eq(st.p.s, "testing", "string_t_new: failed integer assignment");
}

/** Checks that the string_t struct contains the right data when passed
 * in a lua directory to string_t_new()
 */
Test(custom_types, string_t_new_lua)
{
    string_t st = string_t_new(NULL, "../../../tests/custom-scripts/Lua_file/string_t_test.lua");
    cr_assert_eq(st.isString, 0, "string_t_new: failed isString assignment");
    cr_assert_eq(st.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/string_t_test.lua", "string_t_new: failed lua assignment");
}

/** Checks that the string_t struct contains the right data when passed
 * in an string to string_t_init()
 */
Test(custom_types, string_t_init_int)
{
    string_t st;
    st = string_t_init(st, "testing", NULL);
    cr_assert_eq(st.isString, 1, "string_t_init: failed isString assignment");
    cr_assert_eq(st.p.s, "testing", "string_t_init: failed integer assignment");
}

/** Checks that the string_t struct contains the right data when passed
 * in a lua directory to string_t_init()
 */
Test(custom_types, string_t_init_lua)
{
    string_t st;
    st = string_t_init(st, false, "../../../tests/custom-scripts/Lua_file/string_t_test.lua");
    cr_assert_eq(st.isString, 0, "string_t_init: failed isString assignment");
    cr_assert_eq(st.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/string_t_test.lua", "string_t_init: failed lua assignment");
}

/** Checks that the string_t struct returns the correct string value (direct)
 */
Test(custom_types, string_t_get_string)
{
    string_t st = string_t_new("testing", NULL);
    const char *rv = string_t_get(st);
    cr_assert_eq(rv, "testing", "string_t_get: failed string direct retrieval");
}


/** Checks that the string_t struct returns the correct string value (lua)
 */
Test(custom_types, string_t_get_lua)
{
    string_t st = string_t_new("testing_failed", "../../../tests/custom-scripts/Lua_file/string_t_test.lua");
    const char *rv = string_t_get(st);
    int result = strcmp(rv, "testing_succeeded");
    cr_assert_eq(result, 0, "string_t_get: failed string Lua retrieval");
}


