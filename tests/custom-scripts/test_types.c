#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "custom-scripts/custom_types.h"
#include "custom-scripts/custom_type.h"

/** Checks that the obj_t struct contains the right data when obj_t_new() called
 */
Test(custom_type, obj_t_new)
{
    obj_t ot = obj_t_new();
    cr_assert_eq(ot.type, TYPE_NONE, "obj_t_new: failed type assignment");
    cr_assert_eq(ot.is_lua, false, "obj_t_new: failed is_lua assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in a bool to obj_t_bool()
 */
Test(custom_type, obj_t_new_bool)
{
    obj_t ot = obj_t_bool(true, NULL);
    cr_assert_eq(ot.type, TYPE_BOOL, "obj_t_bool: failed type assignment");
    cr_assert_eq(ot.is_lua, false, "obj_t_bool: failed is_lua assignment");
    cr_assert_eq(ot.data.b, true, "obj_t_bool: failed bool assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in a Lua directory to obj_t_bool()
 */
Test(custom_type, obj_t_new_bool_lua)
{   
    obj_t ot = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
    cr_assert_eq(ot.type, TYPE_BOOL, "obj_t_bool: failed type assignment");
    cr_assert_eq(ot.is_lua, true, "obj_t_bool: failed is_lua assignment");
    cr_assert_eq(ot.data.lua, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua",
        "obj_t_bool: failed Lua assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in a char to obj_t_char()
 */
Test(custom_type, obj_t_new_char)
{
    obj_t ot = obj_t_char('a', NULL);
    cr_assert_eq(ot.type, TYPE_CHAR, "obj_t_char: failed type assignment");
    cr_assert_eq(ot.is_lua, false, "obj_t_char: failed is_lua assignment");
    cr_assert_eq(ot.data.c, 'a', "obj_t_char: failed char assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in a Lua directory to obj_t_char()
 */
Test(custom_type, obj_t_new_char_lua)
{   
    obj_t ot = obj_t_char('a', "../../../tests/custom-scripts/Lua_file/char_t_test.lua");
    cr_assert_eq(ot.type, TYPE_CHAR, "obj_t_char: failed type assignment");
    cr_assert_eq(ot.is_lua, true, "obj_t_char: failed is_lua assignment");
    cr_assert_eq(ot.data.lua, "../../../tests/custom-scripts/Lua_file/char_t_test.lua",
        "obj_t_char: failed Lua assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in an integer to obj_t_int()
 */
Test(custom_type, obj_t_new_int)
{
    obj_t ot = obj_t_int(10, NULL);
    cr_assert_eq(ot.type, TYPE_INT, "obj_t_int: failed type assignment");
    cr_assert_eq(ot.is_lua, false, "obj_t_int: failed is_lua assignment");
    cr_assert_eq(ot.data.i, 10, "obj_t_int: failed integer assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in a Lua directory to obj_t_int()
 */
Test(custom_type, obj_t_new_int_lua)
{   
    obj_t ot = obj_t_int(10, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
    cr_assert_eq(ot.type, TYPE_INT, "obj_t_int: failed type assignment");
    cr_assert_eq(ot.is_lua, true, "obj_t_int: failed is_lua assignment");
    cr_assert_eq(ot.data.lua, 10, "../../../tests/custom-scripts/Lua_file/int_t_test.lua",
        "obj_t_int: failed Lua assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in a str to obj_t_str()
 */
Test(custom_type, obj_t_new_str)
{
    obj_t ot = obj_t_str('testing', NULL);
    cr_assert_eq(ot.type, TYPE_STR, "obj_t_str: failed type assignment");
    cr_assert_eq(ot.is_lua, false, "obj_t_str: failed is_lua assignment");
    cr_assert_eq(ot.data.s, 'testing', "obj_t_str: failed str assignment");
}

/** Checks that the obj_t struct contains the right data when passed
 * in a Lua directory to obj_t_str()
 */
Test(custom_type, obj_t_new_str_lua)
{   
    obj_t ot = obj_t_str('testing', "../../../tests/custom-scripts/Lua_file/str_t_test.lua");
    cr_assert_eq(ot.type, TYPE_STR, "obj_t_str: failed type assignment");
    cr_assert_eq(ot.is_lua, true, "obj_t_str: failed is_lua assignment");
    cr_assert_eq(ot.data.lua, "../../../tests/custom-scripts/Lua_file/str_t_test.lua",
        "obj_t_str: failed Lua assignment");
}



/** Checks that the obj_t struct returns the correct bool value (direct)
 */
Test(custom_type, obj_t_get_bool)
{
    obj_t ot = obj_t_bool(true, NULL)
    bool rv = int_t_get(ot);
    cr_assert_eq(rv, true, "obj_t_get_bool: failed bool direct retrieval");
}


/** Checks that the obj_t struct returns the correct bool value (lua)
 */
Test(custom_type, obj_t_get_bool_lua)
{
    obj_t ot = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
    bool rv = bool_t_get(ot);
    cr_assert_eq((rv ? 1 : 0), 0, "bool_t_get: failed bool Lua retrieval");

}

/** Checks that the obj_t struct returns the correct char value (direct)
 */
Test(custom_type, obj_t_get_char)
{
    obj_t ot = obj_t_char('a', NULL)
    char rv = int_t_get(ot);
    cr_assert_eq(rv, 'a', "obj_t_get_char: failed char direct retrieval");
}


/** Checks that the obj_t struct returns the correct char value (lua)
 */
Test(custom_type, obj_t_get_char_lua)
{
    obj_t ot = obj_t_char('a', "../../../tests/custom-scripts/Lua_file/char_t_test.lua");
    char rv = int_t_get(ot);
    cr_assert_eq(rv, 'b', "obj_t_get_char: failed char direct retrieval");
}


/** Checks that the obj_t struct returns the correct int value (direct)
 */
Test(custom_type, obj_t_get_int)
{
    obj_t ot = obj_t_int(123, NULL)
    int rv = int_t_get(ot);
    cr_assert_eq(rv, 123, "obj_t_get_int: failed int direct retrieval");
}


/** Checks that the obj_t struct returns the correct int value (lua)
 */
Test(custom_type, obj_t_get_int_lua)
{
    obj_t ot = int_t_new(10, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
    int rv = int_t_get (ot);
    cr_assert_eq(rv, 15, "int_t_get: failed int Lua retrieval");
}


/** Checks that the obj_t struct returns the correct str value (direct)
 */
Test(custom_type, obj_t_get_str)
{
    obj_t ot = obj_t_str('testing', NULL)
    char *rv = int_t_get(ot);
    cr_assert_eq(rv, 'testing', "obj_t_get_str: failed str direct retrieval");
}

/** Checks that the obj_t struct returns the correct str value (lua)
 */
Test(custom_type, obj_t_get_str_lua)
{
    obj_t  ot = obj_t_str("testing_failed", "../../../tests/custom-scripts/Lua_file/string_t_test.lua");
    const char *rv = string_t_get(ot);
    int result = strcmp(rv, "testing_succeeded");
    cr_assert_eq(result, 0, "string_t_get: failed string Lua retrieval");
}


// /** Checks that the int_t struct contains the right data when passed
//  * in an integer to int_t_new()
//  */
// Test(custom_types, int_t_new_int)
// {
//     int_t it = int_t_new(10, NULL);
//     cr_assert_eq(it.isInt, 1, "int_t_new: failed isInt assignment");
//     cr_assert_eq(it.p.i, 10, "int_t_new: failed integer assignment");
// }

// /** Checks that the int_t struct contains the right data when passed
//  * in a lua directory to int_t_new()
//  */
// Test(custom_types, int_t_new_lua)
// {
//     int_t it = int_t_new(0, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
//     cr_assert_eq(it.isInt, 0, "int_t_new: failed isInt assignment");
//     cr_assert_eq(it.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/int_t_test.lua", "int_t_new: failed lua assignment");
// }

// /** Checks that the int_t struct contains the right data when passed
//  * in an integer to int_t_init()
//  */
// Test(custom_types, int_t_init_int)
// {
//     int_t it;
//     it = int_t_init(it, 10, NULL);
//     cr_assert_eq(it.isInt, 1, "int_t_init: failed isInt assignment");
//     cr_assert_eq(it.p.i, 10, "int_t_init: failed integer assignment");
// }

// /** Checks that the int_t struct contains the right data when passed
//  * in a lua directory to int_t_init()
//  */
// Test(custom_types, int_t_init_lua)
// {
//     int_t it;
//     it = int_t_init(it, 0, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
//     cr_assert_eq(it.isInt, 0, "int_t_init: failed isInt assignment");
//     cr_assert_eq(it.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/int_t_test.lua", "int_t_init: failed lua assignment");
// }

// /** Checks that the int_t struct returns the correct integer value (direct)
//  */
// Test(custom_types, int_t_get_int)
// {
//     int_t it = int_t_new(10, NULL);
//     int rv = int_t_get(it);
//     cr_assert_eq(rv, 10, "int_t_get: failed int direct retrieval");
// }


// /** Checks that the int_t struct returns the correct integer value (lua)
//  */
// Test(custom_types, int_t_get_lua)
// {
//     int_t it = int_t_new(10, "../../../tests/custom-scripts/Lua_file/int_t_test.lua");
//     int rv = int_t_get (it);
//     cr_assert_eq(rv, 15, "int_t_get: failed int Lua retrieval");
// }

// /** Checks that the bool_t struct contains the right data when passed
//  * in a bool to bool_t_new()
//  */
// Test(custom_types, bool_t_new_bool)
// {
//     bool_t bt = bool_t_new(false, NULL);
//     cr_assert_eq(bt.isBool, 1, "bool_t_new: failed isBool assignment");
//     cr_assert_eq(bt.p.luaDirectory, false, "bool_t_new: failed bool assignment");
// }

// /** Checks that the bool_t struct contains the right data when passed
//  * in a lua directory to bool_t_new()
//  */
// Test(custom_types, bool_t_new_lua)
// {
//     bool_t bt = bool_t_new(false, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
//     cr_assert_eq(bt.isBool, 0, "bool_t_new: failed isBool assignment");
//     cr_assert_eq(bt.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua", "bool_t_new: failed lua assignment");
// }

// /** Checks that the bool_t struct contains the right data when passed
//  * in a bool to bool_t_init()
//  */
// Test(custom_types, bool_t_init_int)
// {
//     bool_t bt;
//     bt = bool_t_init(bt, true, NULL);
//     cr_assert_eq(bt.isBool, 1, "bool_t_init: failed isBool assignment");
//     cr_assert_eq(bt.p.b, true, "bool_t_init: failed isBool assignment");
// }

// /** Checks that the bool_t struct contains the right data when passed
//  * in a lua directory to bool_t_init()
//  */
// Test(custom_types, bool_t_init_lua)
// {
//     bool_t bt;
//     bt = bool_t_init(bt, false, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
//     cr_assert_eq(bt.isBool, 0, "bool_t_init: failed isBool assignment");
//     cr_assert_eq(bt.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua", "bool_t_init: failed lua assignment");
// }

// /** Checks that the bool_t struct returns the correct boolean value (direct)
//  */
// Test(custom_types, bool_t_get_bool)
// {
//     bool_t bt = bool_t_new(true, NULL);
//     bool rv = bool_t_get(bt);
//     cr_assert_eq((rv ? 1 : 0), 1, "bool_t_get: failed bool direct retrieval");
// }


// /** Checks that the bool_t struct returns the correct boolean value (lua)
//  */
// Test(custom_types, bool_t_get_lua)
// {
//     bool_t bt = bool_t_new(true, "../../../tests/custom-scripts/Lua_file/bool_t_test.lua");
//     bool rv = bool_t_get(bt);
//     cr_assert_eq((rv ? 1 : 0), 0, "bool_t_get: failed bool Lua retrieval");
// }

// /** Checks that the string_t struct contains the right data when passed
//  * in a string to string_t_new()
//  */
// Test(custom_types, string_t_new_string)
// {
//     string_t st = string_t_new("testing", NULL);
//     cr_assert_eq(st.isString, 1, "string_t_new: failed isString assignment");
//     cr_assert_eq(st.p.s, "testing", "string_t_new: failed integer assignment");
// }

// /** Checks that the string_t struct contains the right data when passed
//  * in a lua directory to string_t_new()
//  */
// Test(custom_types, string_t_new_lua)
// {
//     string_t st = string_t_new(NULL, "../../../tests/custom-scripts/Lua_file/string_t_test.lua");
//     cr_assert_eq(st.isString, 0, "string_t_new: failed isString assignment");
//     cr_assert_eq(st.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/string_t_test.lua", "string_t_new: failed lua assignment");
// }

// /** Checks that the string_t struct contains the right data when passed
//  * in an string to string_t_init()
//  */
// Test(custom_types, string_t_init_int)
// {
//     string_t st;
//     st = string_t_init(st, "testing", NULL);
//     cr_assert_eq(st.isString, 1, "string_t_init: failed isString assignment");
//     cr_assert_eq(st.p.s, "testing", "string_t_init: failed integer assignment");
// }

// /** Checks that the string_t struct contains the right data when passed
//  * in a lua directory to string_t_init()
//  */
// Test(custom_types, string_t_init_lua)
// {
//     string_t st;
//     st = string_t_init(st, false, "../../../tests/custom-scripts/Lua_file/string_t_test.lua");
//     cr_assert_eq(st.isString, 0, "string_t_init: failed isString assignment");
//     cr_assert_eq(st.p.luaDirectory, "../../../tests/custom-scripts/Lua_file/string_t_test.lua", "string_t_init: failed lua assignment");
// }

// /** Checks that the string_t struct returns the correct string value (direct)
//  */
// Test(custom_types, string_t_get_string)
// {
//     string_t st = string_t_new("testing", NULL);
//     const char *rv = string_t_get(st);
//     cr_assert_eq(rv, "testing", "string_t_get: failed string direct retrieval");
// }


// /** Checks that the string_t struct returns the correct string value (lua)
//  */
// Test(custom_types, string_t_get_lua)
// {
//     string_t st = string_t_new("testing_failed", "../../../tests/custom-scripts/Lua_file/string_t_test.lua");
//     const char *rv = string_t_get(st);
//     int result = strcmp(rv, "testing_succeeded");
//     cr_assert_eq(result, 0, "string_t_get: failed string Lua retrieval");
// }


