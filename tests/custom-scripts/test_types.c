#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
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
    int_t it = int_t_new(0, "./testing.lua");
    cr_assert_eq(it.isInt, 0, "int_t_new: failed isInt assignment");
    cr_assert_eq(it.p.luaDirectory, "./testing.lua", "int_t_new: failed lua assignment");
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
    it = int_t_init(it, 0, "./testing.lua");
    cr_assert_eq(it.isInt, 0, "int_t_init: failed isInt assignment");
    cr_assert_eq(it.p.luaDirectory, "./testing.lua", "int_t_init: failed lua assignment");
}



