#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "custom-actions-cond.h"


/* Checks that check_eq() fails when given attributes with conflicting types */
Test(custom_actions_cond, equals_fail)
{
    attribute_value_t v1, v2;
    attribute_t *a1, *a2;
    int rc;

    v1.str_val = "hi";
    v2.int_val = 6;

    a1 = attribute_new(STRING, v1);
    a2 = attribute_new(INTEGER, v2);

    rc = check_eq(a1, a2);

    cr_assert_eq(rc, FAILS, "check_eq() failed to recognize conflicting "
                 "types");

    attribute_free(a1);
    attribute_free(a2);
}


/* Template function for testing check_eq() */
void test_eq(double d1, double d2, int exp1, bool b1, bool b2, int exp2,
             char c1, char c2, int exp3, char* s1, char* s2, int exp4,
             int i1, int i2, int exp5)
{
    char ret[3][8] = {"TRUE", "FALSE", "FAILS"};
    attribute_value_t v0, v1, v2, v3, v4, v5, v6, v7, v8, v9;
    attribute_t *a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8, *a9;
    int rc1, rc2, rc3, rc4, rc5;

    v0.double_val = d1;
    v1.double_val = d2;
    v2.bool_val = b1;
    v3.bool_val = b2;
    v4.char_val = c1;
    v5.char_val = c2;
    v6.str_val = s1;
    v7.str_val = s2;
    v8.int_val = i1;
    v9.int_val = i2;

    a0 = attribute_new(DOUBLE, v0);
    a1 = attribute_new(DOUBLE, v1);
    a2 = attribute_new(BOOLE, v2);
    a3 = attribute_new(BOOLE, v3);
    a4 = attribute_new(CHARACTER, v4);
    a5 = attribute_new(CHARACTER, v5);
    a6 = attribute_new(STRING, v6);
    a7 = attribute_new(STRING, v7);
    a8 = attribute_new(INTEGER, v8);
    a9 = attribute_new(INTEGER, v9);

    rc1 = check_eq(a0, a1);
    rc2 = check_eq(a2, a3);
    rc3 = check_eq(a4, a5);
    rc4 = check_eq(a6, a7);
    rc5 = check_eq(a8, a9);

    cr_assert_eq(rc1, exp1, "expected %s but check_eq() returned %s",
                 ret[exp1], ret[rc1]);
    cr_assert_eq(rc2, exp2, "expected %s but check_eq() returned %s",
                 ret[exp2], ret[rc2]);
    cr_assert_eq(rc3, exp3, "expected %s but check_eq() returned %s",
                 ret[exp3], ret[rc3]);
    cr_assert_eq(rc4, exp4, "expected %s but check_eq() returned %s",
                 ret[exp4], ret[rc4]);
    cr_assert_eq(rc5, exp5, "expected %s but check_eq() returned %s",
                 ret[exp5], ret[rc5]);

    attribute_free(a0);
    attribute_free(a1);
    attribute_free(a2);
    attribute_free(a3);
    attribute_free(a4);
    attribute_free(a5);
    attribute_free(a6);
    attribute_free(a7);
    attribute_free(a8);
    attribute_free(a9);
}


/* Testing check_eq() for each type of attribute when true */
Test(custom_actions_cond, equals)
{
    test_eq(2.0, 2.0, 1,
            true, true, 1,
            'a', 'a', 1,
            "hi", "hi", 1,
            4, 4, 1);
}


/* Testing check_eq() for each type of attribute when false */
Test(custom_actions_cond, not_equals)
{
    test_eq(1.0, 2.0, 0,
            true, false, 0,
            'a', 'b', 0,
            "hi", "ho", 0,
            4, 3, 0);
}


/* Testing that numerical comparisons fail when given conflicting or
 * non-numerical types
 *
 * Note: characters are being considered as numerical
 */
Test(custom_actions_cond, num_comp_fail)
{
    attribute_value_t v0, v1, v2, v3, v4, v5;
    attribute_t *a0, *a1, *a2, *a3, *a4, *a5;
    int rc1, rc2, rc3;

    v0.double_val = 2.0;
    v1.int_val = 3;
    v2.str_val = "hi";
    v3.str_val = "ho";
    v4.bool_val = true;
    v5.bool_val = true;

    a0 = attribute_new(DOUBLE, v0);
    a1 = attribute_new(INTEGER, v1);
    a2 = attribute_new(STRING, v2);
    a3 = attribute_new(STRING, v3);
    a4 = attribute_new(BOOLE, v4);
    a5 = attribute_new(BOOLE, v5);

    rc1 = check_lt(a0, a1);
    rc2 = check_lt(a2, a3);
    rc3 = check_lt(a4, a5);

    cr_assert_eq(rc1, FAILS, "numerical comparisons fail to recognize "
                 "conflicting types %d, rc1");
    cr_assert_eq(rc2, FAILS, "numerical comparisons fail to recognize "
                 "invalid string type");
    cr_assert_eq(rc3, FAILS, "numerical comparisons fail to recognize "
                 "invalid boolean type");

    attribute_free(a0);
    attribute_free(a1);
    attribute_free(a2);
    attribute_free(a3);
    attribute_free(a4);
    attribute_free(a5);
}


/* Template function for testing numerical comparison functions
 *
 * Note: op argument used to select specific comparative operator
 */
void test_comp(double d1, double d2, int exp1, char c1, char c2, int exp2,
               int i1, int i2, int exp3, num_comp_t op)
{
    char ret[3][8] = {"TRUE", "FALSE", "FAILS"};
    attribute_value_t v0, v1, v2, v3, v4, v5;
    attribute_t *a0, *a1, *a2, *a3, *a4, *a5;
    int rc1, rc2, rc3;

    v0.double_val = d1;
    v1.double_val = d2;
    v2.char_val = c1;
    v3.char_val = c2;
    v4.int_val = i1;
    v5.int_val = i2;

    a0 = attribute_new(DOUBLE, v0);
    a1 = attribute_new(DOUBLE, v1);
    a2 = attribute_new(CHARACTER, v2);
    a3 = attribute_new(CHARACTER, v3);
    a4 = attribute_new(INTEGER, v4);
    a5 = attribute_new(INTEGER, v5);

    switch (op)
    {

    case LT:
        rc1 = check_lt(a0, a1);
        rc2 = check_lt(a2, a3);
        rc3 = check_lt(a4, a5);
        break;
    case GT:
        rc1 = check_gt(a0, a1);
        rc2 = check_gt(a2, a3);
        rc3 = check_gt(a4, a5);
        break;
    case LTE:
        rc1 = check_lte(a0, a1);
        rc2 = check_lte(a2, a3);
        rc3 = check_lte(a4, a5);
        break;
    default:
        rc1 = check_gte(a0, a1);
        rc2 = check_gte(a2, a3);
        rc3 = check_gte(a4, a5);
    }


    cr_assert_eq(rc1, exp1, "expected %s but check_eq() returned %s",
                 ret[exp1], ret[rc1]);
    cr_assert_eq(rc2, exp2, "expected %s but check_eq() returned %s",
                 ret[exp2], ret[rc2]);
    cr_assert_eq(rc3, exp3, "expected %s but check_eq() returned %s",
                 ret[exp3], ret[rc3]);

    attribute_free(a0);
    attribute_free(a1);
    attribute_free(a2);
    attribute_free(a3);
    attribute_free(a4);
    attribute_free(a5);
}


/* Testing check_lt() for each attribute type when true */
Test(custom_actions_cond, less_than)
{
    test_comp(1.0, 2.0, 1,
              'a', 'b', 1,
              2, 3, 1, LT);
}


/* Testing check_lt() for each attribute type when false */
Test(custom_actions_cond, not_less_than)
{
    test_comp(1.0, 1.0, 0,
              'b', 'a', 0,
              3, 2, 0, LT);
}


/* Testing check_gt() for each attribute type when true */
Test(custom_actions_cond, greater_than)
{
    test_comp(2.0, 1.0, 1,
              'b', 'a', 1,
              3, 2, 1, GT);
}


/* Testing check_gt() for each attribute type when false */
Test(custom_actions_cond, not_greater_than)
{
    test_comp(1.0, 2.0, 0,
              'a', 'b', 0,
              2, 3, 0, GT);
}


/* Testing check_lte() for each attribute type when true */
Test(custom_actions_cond, less_than_eq)
{
    test_comp(1.0, 2.0, 1,
              'a', 'a', 1,
              2, 2, 1, LTE);
}


/* Testing check_lte() for each attribute type when false */
Test(custom_actions_cond, not_less_than_eq)
{
    test_comp(2.0, 1.0, 0,
              'b', 'a', 0,
              3, 2, 0, LTE);
}


/* Testing check_gte() for each attribute type when true */
Test(custom_actions_cond, greater_than_eq)
{
    test_comp(2.0, 1.0, 1,
              'b', 'a', 1,
              2, 2, 1, GTE);
}


/* Testing check_gte() for each attribute type when false */
Test(custom_actions_cond, not_greater_than_eq)
{
    test_comp(1.0, 2.0, 0,
              'a', 'b', 0,
              2, 3, 0, GTE);
}
