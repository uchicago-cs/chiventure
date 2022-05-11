#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "custom-actions-effect.h"


/* Test that set_attr() fails when given non-matching types */
Test(custom_actions_effect, set_fail)
{

    attribute_value_t v1, v2;
    attribute_t *a1, *a2;
    int rc;

    v1.bool_val = true;
    v2.int_val = 6;

    a1 = attribute_new(BOOLE, v1);
    a2 = attribute_new(INTEGER, v2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, FAILS, "set_attr() failed to recognize conflicting types");

    attribute_free(a1);
    attribute_free(a2);
}


/* Test that set_attr() successfully sets attribute of type double */
Test(custom_actions_effect, set_double)
{
    attribute_value_t v1, v2;
    attribute_t *a1, *a2;
    int rc;

    v1.double_val = 1.0;
    v2.double_val = 2.0;

    a1 = attribute_new(DOUBLE, v1);
    a2 = attribute_new(DOUBLE, v2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_eq(a1->attribute_value.double_val, 2.0,
                 "expected a1 value to be 2.0 but attr_set() set to %.1f",
                 a1->attribute_value.double_val);

    attribute_free(a1);
    attribute_free(a2);
}


/* Test that set_attr() successfully sets attribute of type boolean */
Test(custom_actions_effect, set_bool)
{
    attribute_value_t v1, v2;
    attribute_t *a1, *a2;
    int rc;

    v1.bool_val = false;
    v2.bool_val = true;

    a1 = attribute_new(BOOLE, v1);
    a2 = attribute_new(BOOLE, v2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_eq(a1->attribute_value.bool_val, true,
                 "expected a1 value to be true but attr_set() set to false");

    attribute_free(a1);
    attribute_free(a2);
}


/* Test that set_attr() successfully sets attribute of type char */
Test(custom_actions_effect, set_char)
{
    attribute_value_t v1, v2;
    attribute_t *a1, *a2;
    int rc;

    v1.char_val = 'a';
    v2.char_val = 'b';

    a1 = attribute_new(CHARACTER, v1);
    a2 = attribute_new(CHARACTER, v2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_eq(a1->attribute_value.char_val, 'b',
                 "expected a1 value to be 'b' but attr_set() set to %c",
                 a1->attribute_value.char_val);

    attribute_free(a1);
    attribute_free(a2);
}


/* Test that set_attr() successfully sets attribute of type string */
Test(custom_actions_effect, set_string)
{
    attribute_value_t v1, v2;
    attribute_t *a1, *a2;
    int rc;

    v1.str_val = "ho";
    v2.str_val = "hi";

    a1 = attribute_new(STRING, v1);
    a2 = attribute_new(STRING, v2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_str_eq(a1->attribute_value.str_val, "hi",
                     "expected a1 value to be \"hi\" but attr_set() set to %s",
                     a1->attribute_value.str_val);

    attribute_free(a1);
    attribute_free(a2);
}


/* Test that set_attr() successfully sets attribute of type int */
Test(custom_actions_effect, set_int)
{
    attribute_value_t v1, v2;
    attribute_t *a1, *a2;
    int rc;

    v1.int_val = 1;
    v2.int_val = 2;

    a1 = attribute_new(INTEGER, v1);
    a2 = attribute_new(INTEGER, v2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_eq(a1->attribute_value.int_val, 2,
                 "expected a1 value to be 2 but attr_set() set to %d",
                 a1->attribute_value.int_val);

    attribute_free(a1);
    attribute_free(a2);
}


/* Test that attribute arithmetic functions fail when given non-matching
 *  types or invalid types */
Test(custom_actions_effect, attr_arithmetic_fail)
{
    attribute_value_t v1, v2, v3, v4, v5;
    attribute_t *a1, *a2, *a3, *a4, *a5;
    int rc1, rc2;

    v1.int_val = 1;
    v2.double_val = 3;
    v3.char_val = 'a';
    v4.char_val = 'b';
    v5.int_val = 0;

    a1 = attribute_new(INTEGER, v1);
    a2 = attribute_new(DOUBLE, v2);
    a3 = attribute_new(CHARACTER, v3);
    a4 = attribute_new(CHARACTER, v4);
    a5 = attribute_new(INTEGER, v5);

    rc1 = add_attr(a1, a2, a5);
    rc2 = add_attr(a3, a4, a5);

    cr_assert_eq(rc1, FAILS, "attribute arithmetic failed to recognize "
                 "conflicting types");
    cr_assert_eq(rc2, FAILS, "attribute arithmetic failed to recognized "
                 "invalid attribute type (bool)");

    attribute_free(a1);
    attribute_free(a2);
    attribute_free(a3);
    attribute_free(a4);
    attribute_free(a5);
}


/* Template function for testing attribute arithmetic functions */
void test_attr_arithmetic(double d1, double d2, double exp1,
                          int i1, int i2, int exp2, arithmetic_op_t op)
{
    char ops[4][5] = {"ADD", "SUB", "MULT", "DIV"};
    attribute_value_t v1, v2, v3, v4, v5, v6;
    attribute_t *a1, *a2, *a3, *a4, *a5, *a6;
    int rc1, rc2;

    v1.double_val = d1;
    v2.double_val = d2;
    v3.double_val = 0;
    v4.int_val = i1;
    v5.int_val = i2;
    v6.int_val = 0;

    a1 = attribute_new(DOUBLE, v1);
    a2 = attribute_new(DOUBLE, v2);
    a3 = attribute_new(DOUBLE, v3);
    a4 = attribute_new(INTEGER, v4);
    a5 = attribute_new(INTEGER, v5);
    a6 = attribute_new(INTEGER, v6);

    switch (op)
    {

    case ADD:
        rc1 = add_attr(a1, a2, a3);
        rc2 = add_attr(a4, a5, a6);
        break;
    case SUB:
        rc1 = sub_attr(a1, a2, a3);
        rc2 = sub_attr(a4, a5, a6);
        break;
    case MULT:
        rc1 = mult_attr(a1, a2, a3);
        rc2 = mult_attr(a4, a5, a6);
        break;
    default:
        rc1 = div_attr(a1, a2, a3);
        rc2 = div_attr(a4, a5, a6);
    }

    cr_assert_eq(rc1, SUCCEEDS, "attribute arithmetic failed unexpectedly "
                 "with type double and operation %s", ops[op]);
    cr_assert_eq(rc2, SUCCEEDS, "attribute arithmetic failed unexpectedly "
                 "with type int and operation %s", ops[op]);

    cr_assert_float_eq(a3->attribute_value.double_val, exp1, 1E-4,
                       "expected %.2f but attribute arithmetic returned %.2f"
                       " with type double and operation %s",
                       exp1, a3->attribute_value.double_val, ops[op]);
    cr_assert_eq(a6->attribute_value.int_val, exp2,
                 "expected %d but attribute arithmetic returned %d"
                 " with type int and operation %s",
                 exp2, a3->attribute_value.int_val, ops[op]);

    attribute_free(a1);
    attribute_free(a2);
    attribute_free(a3);
    attribute_free(a4);
    attribute_free(a5);
    attribute_free(a6);
}


/* Testing that add_attr() succeeds and sets proper value of result attribute
 */
Test(custom_actions_effect, add_attr)
{
    test_attr_arithmetic(1.0, 2.0, 3.0,
                         1, 2, 3, ADD);
}


/* Testing that sub_attr() succeeds and sets proper value of result attribute
 */
Test(custom_actions_effect, sub_attr)
{
    test_attr_arithmetic(5.0, 2.0, 3.0,
                         5, 2, 3, SUB);
}


/* Testing that mult_attr() succeeds and sets proper value of result attribute
 */
Test(custom_actions_effect, mult_attr)
{
    test_attr_arithmetic(5.0, 4.0, 20.0,
                         5, 4, 20, MULT);
}


/* Testing that div_attr() succeeds and sets proper value of result attribute
 */
Test(custom_actions_effect, div_attr)
{
    test_attr_arithmetic(10.0, 2.0, 5.0,
                         10, 2, 5, DIV);
}


/* Testing that gen_attrval() fails when given an invalid type */
Test(custom_actions_effect, gen_attrval_fail)
{
    attribute_value_t v;
    attribute_t *a;
    int rc;

    v.char_val = 'a';

    a = attribute_new(CHARACTER, v);

    rc = gen_attrval(0, 10, a);

    cr_assert_eq(rc, FAILS, "gen_attrval() failed to recognized invalid "
                 "attribute type (char)");

    attribute_free(a);
}


/* Testing that gen_attrval() succeeds and produces a value within the
 *  specified range for an attribute value of type double */
Test(custom_actions_effect, gen_attrval_double)
{
    attribute_value_t v;
    attribute_t *a;
    int rc;

    v.double_val = 0;

    a = attribute_new(DOUBLE, v);

    rc = gen_attrval(20, 50, a);

    cr_assert_eq(rc, SUCCEEDS, "gen_attrval() failed unexpectedly");
    cr_assert_geq(a->attribute_value.double_val, 20,
                  "gen_attrval() produced a value less than lower bound 20");
    cr_assert_leq(a->attribute_value.double_val, 50,
                  "gen_attrval() produced a value greater than upper bound 50");

    attribute_free(a);
}


/* Testing that gen_attrval() succeeds and produces a value within the
 *  specified range for an attribute value of type int */
Test(custom_actions_effect, gen_attrval_int)
{
    attribute_value_t v;
    attribute_t *a;
    int rc;

    v.int_val = 0;

    a = attribute_new(INTEGER, v);

    rc = gen_attrval(20, 50, a);

    cr_assert_eq(rc, SUCCEEDS, "gen_attrval() failed unexpectedly");
    cr_assert_geq(a->attribute_value.int_val, 20,
                  "gen_attrval() produced a value less than lower bound 20");
    cr_assert_leq(a->attribute_value.int_val, 50,
                  "gen_attrval() produced a value greater than upper bound 50");

    attribute_free(a);
}
