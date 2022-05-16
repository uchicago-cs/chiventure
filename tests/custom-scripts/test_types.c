#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "custom-scripts/get_custom_type.h"

/** 
 * Checks that the object_t struct contains the right data when obj_t_new() called
 */
Test(custom_type, obj_t_new)
{
    object_t *ot = obj_t_new();
    cr_assert_eq(ot->type, NONE_TYPE, "obj_t_new: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_new: failed is_lua assignment");
    cr_assert_null(ot->args, "obj_t_new: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in a bool to obj_t_bool()
 */
Test(custom_type, obj_t_new_bool)
{
    object_t *ot = obj_t_bool(true, NULL);
    cr_assert_eq(ot->type, BOOL_TYPE, "obj_t_bool: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_bool: failed is_lua assignment");
    cr_assert_eq(ot->data.b, true, "obj_t_bool: failed bool assignment");
    cr_assert_null(ot->args, "obj_t_bool: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_bool()
 */
Test(custom_type, obj_t_new_bool_lua)
{   
    object_t *ot = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_test.lua");
    cr_assert_eq(ot->type, BOOL_TYPE, "obj_t_bool: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_bool: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/bool_test.lua",
        "obj_t_bool: failed Lua assignment");
    cr_assert_null(ot->args, "obj_t_bool: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in a char to obj_t_char()
 */
Test(custom_type, obj_t_new_char)
{
    object_t *ot = obj_t_char('a', NULL);
    cr_assert_eq(ot->type, CHAR_TYPE, "obj_t_char: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_char: failed is_lua assignment");
    cr_assert_eq(ot->data.c, 'a', "obj_t_char: failed char assignment");
    cr_assert_null(ot->args, "obj_t_char: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_char()
 */
Test(custom_type, obj_t_new_char_lua)
{   
    object_t *ot = obj_t_char('a', "../../../tests/custom-scripts/Lua_file/char_test.lua");
    cr_assert_eq(ot->type, CHAR_TYPE, "obj_t_char: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_char: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/char_test.lua",
        "obj_t_char: failed Lua assignment");
    cr_assert_null(ot->args, "obj_t_char: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in an integer to obj_t_int()
 */
Test(custom_type, obj_t_new_int)
{
    object_t *ot = obj_t_int(10, NULL);
    cr_assert_eq(ot->type, INT_TYPE, "obj_t_int: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_int: failed is_lua assignment");
    cr_assert_eq(ot->data.i, 10, "obj_t_int: failed integer assignment");
    cr_assert_null(ot->args, "obj_t_int: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_int()
 */
Test(custom_type, obj_t_new_int_lua)
{   
    object_t *ot = obj_t_int(10, "../../../tests/custom-scripts/Lua_file/int_test.lua");
    cr_assert_eq(ot->type, INT_TYPE, "obj_t_int: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_int: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/int_test.lua",
        "obj_t_int: failed Lua assignment");
    cr_assert_null(ot->args, "obj_t_int: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in a str to obj_t_str()
 */
Test(custom_type, obj_t_new_str)
{
    object_t *ot = obj_t_str("testing", NULL);
    cr_assert_eq(ot->type, STR_TYPE, "obj_t_str: failed type assignment");
    cr_assert_eq(ot->is_lua, false, "obj_t_str: failed is_lua assignment");
    cr_assert_eq(ot->data.s, "testing", "obj_t_str: failed str assignment");
    cr_assert_null(ot->args, "obj_t_str: failed args null initialization");
}

/** 
 * Checks that the object_t struct contains the right data when passed
 * in a Lua directory to obj_t_str()
 */
Test(custom_type, obj_t_new_str_lua)
{   
    object_t *ot = obj_t_str("testing", "../../../tests/custom-scripts/Lua_file/string_test.lua");
    cr_assert_eq(ot->type, STR_TYPE, "obj_t_str: failed type assignment");
    cr_assert_eq(ot->is_lua, true, "obj_t_str: failed is_lua assignment");
    cr_assert_eq(ot->data.lua, "../../../tests/custom-scripts/Lua_file/string_test.lua",
        "obj_t_str: failed Lua assignment");
    cr_assert_null(ot->args, "obj_t_str: failed args null initialization");
}

// ============================================================================

/** 
* Checks that the arg_t struct contains a boolean value when arg_t_bool() is called
*/
Test(custom_type, arg_t_new_bool)
{
    // Placeholder object_t
    object_t *ot = obj_t_str("Placeholder object", NULL);
    ot = obj_add_arg_bool(ot, true);
    
    arg_t *at = ot->args;
    cr_assert_eq(at->type, BOOL_TYPE, "arg_t_bool: failed type assignment");
    cr_assert_eq(at->data.b, true, "arg_t_bool: failed bool assignment");
    cr_assert_eq(at->next, NULL, "arg_t_bool next failed assignment");
}

/** 
* Checks that the arg_t struct contains a char value when arg_t_char() is called
*/
Test(custom_type, arg_t_new_char)
{
    object_t *ot = obj_t_str("Placeholder object", NULL);
    ot = obj_add_arg_char(ot, 'a');
    
    arg_t *at = ot->args;
    cr_assert_eq(at->type, CHAR_TYPE, "arg_t_char: failed type assignment");
    cr_assert_eq(at->data.c, 'a', "arg_t_char: failed char assignment");
    cr_assert_eq(at->next, NULL, "arg_t_char next failed assignment");
}

/** 
* Checks that the arg_t struct contains a int value when arg_t_int() is called
*/
Test(custom_type, arg_t_new_int)
{
    object_t *ot = obj_t_str("Placeholder object", NULL);
    ot = obj_add_arg_int(ot, 10);
    
    arg_t *at = ot->args;
    cr_assert_eq(at->type, INT_TYPE, "arg_t_int: failed type assignment");
    cr_assert_eq(at->data.i, 10, "arg_t_int: failed integer assignment");
    cr_assert_eq(at->next, NULL, "arg_t_int next failed assignment");
}

/** 
* Checks that the arg_t struct  contains a string  value when arg_t_str() is called
*/
Test(custom_type, arg_t_new_str)
{
    object_t *ot = obj_t_str("Placeholder object", NULL);
    ot = obj_add_arg_str(ot, "testing");
    
    arg_t *at = ot->args;
    cr_assert_eq(at->type, STR_TYPE, "arg_t_str: failed type assignment");
    cr_assert_eq(at->data.s, "testing", "arg_t_str: failed integer assignment");
    cr_assert_eq(at->next, NULL, "arg_t_str next failed assignment");
}

/** 
* Checks that the obj_add_arg_<type> correctly adds arg_t structs to the linked list
*/
Test(custom_type, obj_add_args)
{
    object_t *ot = obj_t_bool(true, NULL);
    ot = obj_add_arg_str(ot, "I am head");
    ot = obj_add_arg_int(ot, 2);
    ot = obj_add_arg_char(ot, '3');
    ot = obj_add_arg_bool(ot, true);
    arg_t *head = ot->args;

    cr_assert_str_eq(head->data.s, "I am head", "arg_t_add: failed head initialization");
    cr_assert_eq(head->next->data.i, 2, "arg_t_add: failed arg_t addition");
    cr_assert_eq(head->next->next->data.c, '3', "arg_t_add: failed arg_t addition");
    cr_assert_eq(head->next->next->next->data.b, true, "arg_t_add: failed arg_t addition");
    cr_assert_null(head->next->next->next->next, "arg_t_add: failed to terminate linked list");
}

/** 
* Checks that the obj_add_arg_<type> correctly assigns prev pointers in doubly linked list
*/
Test(custom_type, obj_add_args_prev)
{
    object_t *ot = obj_t_bool(true, NULL);
    ot = obj_add_arg_str(ot, "I am head");
    ot = obj_add_arg_int(ot, 2);
    ot = obj_add_arg_char(ot, '3');
    ot = obj_add_arg_bool(ot, true);
    arg_t *end = ot->args->next->next->next;

    cr_assert_eq(end->prev->data.c, '3', "arg_t_add: failed arg_t addition (prev)");
    cr_assert_eq(end->prev->prev->data.i, 2, "arg_t_add: failed arg_t addition (prev)");
    cr_assert_str_eq(end->prev->prev->prev->data.s, "I am head", "arg_t_add: failed arg_t addition (prev)");
}

// ============================================================================

/** 
 * Checks that the object_t struct returns the correct bool value (direct)
 */
Test(custom_type, obj_t_get_bool)
{
    object_t *ot = obj_t_bool(true, NULL);
    bool rv = bool_t_get(ot);
    cr_assert_eq(rv, true, "obj_t_get_bool: failed bool direct retrieval");
}

/** 
 * Checks that the object_t struct returns the correct bool value (lua)
 */
Test(custom_type, obj_t_get_bool_lua)
{
    object_t *ot = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_test.lua");
    bool rv = bool_t_get(ot);
    cr_assert_eq((rv ? 1 : 0), 0, "bool_t_get: failed bool Lua retrieval");
}

/** 
 * Checks that the object_t struct returns the correct bool value (lua)
 * When arguments are passed into the script
 */
Test(custom_type, obj_t_get_bool_lua_args)
{
    object_t *ot = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_test_args.lua");
    ot = obj_add_arg_bool(obj_add_arg_bool(obj_add_arg_bool(ot, true), true), true);
    bool rv = bool_t_get(ot);
    cr_assert_eq((rv ? 1 : 0), 1, "bool_t_get: failed bool Lua retrieval");

    object_t *ot2 = obj_t_bool(true, "../../../tests/custom-scripts/Lua_file/bool_test_args.lua");
    ot2 = obj_add_arg_bool(obj_add_arg_bool(obj_add_arg_bool(ot2, true), false), true);
    bool rv2 = bool_t_get(ot2);
    cr_assert_eq((rv2 ? 1 : 0), 0, "bool_t_get: failed bool Lua retrieval");
}

/** 
 * Checks that the object_t struct returns the correct char value (direct)
 */
Test(custom_type, obj_t_get_char)
{
    object_t *ot = obj_t_char('a', NULL);
    char rv = char_t_get(ot);
    cr_assert_eq(rv, 'a', "obj_t_get_char: failed char direct retrieval");
}

/** 
 * Checks that the object_t struct returns the correct char value (lua)
 */
Test(custom_type, obj_t_get_char_lua)
{
    object_t *ot = obj_t_char('a', "../../../tests/custom-scripts/Lua_file/char_test.lua");
    char rv = char_t_get(ot);
    cr_assert_eq(rv, 'b', "obj_t_get_char: failed char direct retrieval");
}

/** 
 * Checks that the object_t struct returns the correct char value (lua)
 * When arguments are passed in Lua
 */
Test(custom_type, obj_t_get_char_lua_args)
{
    object_t *ot = obj_t_char('q', 
        "../../../tests/custom-scripts/Lua_file/char_test_args.lua");
    ot = obj_add_arg_char(obj_add_arg_char(ot, 'a'), 'Z');
    char rv = char_t_get(ot);
    cr_assert_eq(rv, 'c', "obj_t_get_char: failed char direct retrieval");

    object_t *ot2 = obj_t_char('q', 
        "../../../tests/custom-scripts/Lua_file/char_test_args.lua");
    ot2 = obj_add_arg_char(obj_add_arg_char(ot2, 'Z'), 'b');
    char rv2 = char_t_get(ot2);
    cr_assert_eq(rv2, 'd', "obj_t_get_char: failed char direct retrieval");

    object_t *ot3 = obj_t_char('q', 
        "../../../tests/custom-scripts/Lua_file/char_test_args.lua");
    ot3 = obj_add_arg_char(obj_add_arg_char(ot3, 'a'), 'b');
    char rv3 = char_t_get(ot3);
    cr_assert_eq(rv3, 'e', "obj_t_get_char: failed char direct retrieval");
}

/** 
 * Checks that the object_t struct returns the correct int value (direct)
 */
Test(custom_type, obj_t_get_int)
{
    object_t *ot = obj_t_int(123, NULL);
    int rv = int_t_get(ot);
    cr_assert_eq(rv, 123, "obj_t_get_int: failed int direct retrieval");
}

/** 
 * Checks that the object_t struct returns the correct int value (lua)
 */
Test(custom_type, obj_t_get_int_lua)
{
    object_t *ot = obj_t_int(10, "../../../tests/custom-scripts/Lua_file/int_test.lua");
    int rv = int_t_get (ot);
    cr_assert_eq(rv, 15, "int_t_get: failed int Lua retrieval");
}

/** 
 * Checks that the object_t struct returns the correct int value (lua)
 * When arguments are passed in Lua
 */
Test(custom_type, obj_t_get_int_lua_args)
{
    object_t *ot = obj_t_int(99, 
        "../../../tests/custom-scripts/Lua_file/int_test_args.lua");
    ot = obj_add_arg_int(obj_add_arg_int(ot, 5), 10);
    int rv = int_t_get(ot);
    cr_assert_eq(rv, 15, "obj_t_get_int: failed int direct retrieval");

    // Arguments of an object don't have to be of the same type!
    object_t *ot2 = obj_t_int(99,
        "../../../tests/custom-scripts/Lua_file/int_test_args.lua");
    ot2 = obj_add_arg_char(obj_add_arg_char(ot2, 'X'), 'Y');
    int rv2 = int_t_get(ot2);
    cr_assert_eq(rv2, 100, "obj_t_get_int: failed int direct retrieval");
}

/** 
 * Checks that the object_t struct returns the correct str value (direct)
 */
Test(custom_type, obj_t_get_str)
{
    object_t *ot = obj_t_str("testing", NULL);
    char *rv = str_t_get(ot);
    cr_assert_str_eq(rv, "testing", "obj_t_get_str: failed str direct retrieval");
}

/** 
 * Checks that the object_t struct returns the correct str value (lua)
 */
Test(custom_type, obj_t_get_str_lua)
{
    object_t *ot = obj_t_str("testing_failed", "../../../tests/custom-scripts/Lua_file/string_test.lua");
    char *rv = str_t_get(ot);
    cr_assert_str_eq(rv, "testing_succeeded", "string_t_get: failed string Lua retrieval");
}

/** 
 * Checks that the object_t struct returns the correct string (lua)
 * When arguments are passed in Lua
 */
Test(custom_type, obj_t_get_str_lua_args)
{
    object_t *ot = obj_t_str(" ", "../../../tests/custom-scripts/Lua_file/string_test_args.lua");
    ot = obj_add_arg_str(obj_add_arg_str(ot, "Test "), "passes!");
    char *rv = str_t_get(ot);
    cr_assert_str_eq(rv, "Test passes!", "obj_t_get_int: failed string direct retrieval");

}