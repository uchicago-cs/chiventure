#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "custom-scripts/custom_types.h"

/** Checks that the string_is_lua() correctly differentiates between a
 * normal string and a Lua directory string, given the requirements
 */
Test(custom_types, string_is_lua)
{
    char* s = "LUA ./testing.lua";
    cr_assert_eq(string_is_lua(s), true, "string_is_lua: failed to determine Lua script");

    char* s2 = "LU ./testing.lua";
    cr_assert_eq(string_is_lua(s2), false, "string_is_lua: failed to determine normal string");
}

/** Checks that extract_lua() correctly extracts just the Lua directory from a string
 * that is determined to contain a Lua directory
 */
Test(custom_types, extract_lua)
{
    char* s = "LUA ./testing.lua";
    cr_assert_eq(string_is_lua(s), true, "string_is_lua: failed to determine Lua script");
    char* res = extract_lua(s);
    printf("string = %s\n", res);
    cr_assert_str_eq(res, "./testing.lua", "extract_lua: failed to extract Lua script dir");
}
