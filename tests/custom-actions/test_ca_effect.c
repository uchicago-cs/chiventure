#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "custom-actions-effect.h"


/* Test that set_attr() fails when given non-matching types */
Test(custom_actions_effect, set_fail) {
    attribute_t *a1, *a2;
    int rc;

    bool b1 = true;
    int i1 = 6;
    char *temp_attr_name = "temp";

    a1 = bool_attr_new(temp_attr_name, b1);
    a2 = int_attr_new(temp_attr_name, i1);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, FAILS, "set_attr() failed to recognize conflicting types");

    attribute_free(a1);
    attribute_free(a2);
}

/* Test that set_attr() successfully sets attribute of type double */
Test(custom_actions_effect, set_double) {
    attribute_t *a1, *a2;
    int rc;

    double d1 = 1.0;
    double d2 = 2.0;
    char *temp_attr_name = "temp";

    a1 = double_attr_new(temp_attr_name, d1);
    a2 = double_attr_new(temp_attr_name, d2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_eq(a1->attribute_value.double_val, 2.0,
                 "expected a1 value to be 2.0 but attr_set() set to %.1f",
                 a1->attribute_value.double_val);

    attribute_free(a1);
    attribute_free(a2);
}

/* Test that set_attr() successfully sets attribute of type boolean */
Test(custom_actions_effect, set_bool) {
    attribute_t *a1, *a2;
    int rc;

    bool b1 = false;
    bool b2 = true;
    char *temp_attr_name = "temp";

    a1 = bool_attr_new(temp_attr_name, b1);
    a2 = bool_attr_new(temp_attr_name, b2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_eq(a1->attribute_value.bool_val, true,
                 "expected a1 value to be true but attr_set() set to false");

    attribute_free(a1);
    attribute_free(a2);
}

/* Test that set_attr() successfully sets attribute of type char */
Test(custom_actions_effect, set_char) {
    attribute_t *a1, *a2;
    int rc;

    char c1 = 'a';
    char c2 = 'b';
    char *temp_attr_name = "temp";

    a1 = char_attr_new(temp_attr_name, c1);
    a2 = char_attr_new(temp_attr_name, c2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_eq(a1->attribute_value.char_val, 'b',
                 "expected a1 value to be 'b' but attr_set() set to %c",
                 a1->attribute_value.char_val);

    attribute_free(a1);
    attribute_free(a2);
}

/* Test that set_attr() successfully sets attribute of type string */
Test(custom_actions_effect, set_string) {
    attribute_t *a1, *a2;
    int rc;

    char *s1 = "ho";
    char *s2 = "hi";
    char *temp_attr_name = "temp";

    a1 = str_attr_new(temp_attr_name, s1);
    a2 = str_attr_new(temp_attr_name, s2);

    rc = set_attr(a1, a2);

    cr_assert_eq(rc, SUCCEEDS, "set_attr() failed unexpectedely");
    cr_assert_str_eq(a1->attribute_value.str_val, "hi",
                     "expected a1 value to be \"hi\" but attr_set() set to %s",
                     a1->attribute_value.str_val);

    attribute_free(a1);
    attribute_free(a2);
}

/* Test that set_attr() successfully sets attribute of type int */
Test(custom_actions_effect, set_int) {
    attribute_t *a1, *a2;
    int rc;

    int i1 = 1;
    int i2 = 2;
    char *temp_attr_name = "temp";

    a1 = int_attr_new(temp_attr_name, i1);
    a2 = int_attr_new(temp_attr_name, i2);

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
Test(custom_actions_effect, attr_arithmetic_fail) {
    attribute_t *a1, *a2, *a3, *a4, *a5;
    int rc1, rc2;

    int i1 = 1;
    double d1 = 3;
    char c1 = 'a';
    char c2 = 'n';
    int i2 = 0;
    char *temp_attr_name = "temp";

    a1 = int_attr_new(temp_attr_name, i1);
    a2 = double_attr_new(temp_attr_name, d1);
    a3 = char_attr_new(temp_attr_name, c1);
    a4 = char_attr_new(temp_attr_name, c2);
    a5 = int_attr_new(temp_attr_name, i2);

    rc1 = add_attr(a1, a2, a5);
    rc2 = add_attr(a3, a4, a5);

    cr_assert_eq(rc1, FAILS,
                 "attribute arithmetic failed to recognize "
                 "conflicting types");
    cr_assert_eq(rc2, FAILS,
                 "attribute arithmetic failed to recognized "
                 "invalid attribute type (bool)");

    attribute_free(a1);
    attribute_free(a2);
    attribute_free(a3);
    attribute_free(a4);
    attribute_free(a5);
}

/* Template function for testing attribute arithmetic functions */
void test_attr_arithmetic(double d1, double d2, double exp1,
                          int i1, int i2, int exp2, arithmetic_op_t op) {
    char ops[4][5] = {"ADD", "SUB", "MULT", "DIV"};
    attribute_t *a1, *a2, *a3, *a4, *a5, *a6;
    int rc1, rc2;

    double d3 = 0;
    int i3 = 0;
    char *temp_attr_name = "temp";

    a1 = double_attr_new(temp_attr_name, d1);
    a2 = double_attr_new(temp_attr_name, d2);
    a3 = double_attr_new(temp_attr_name, d3);
    a4 = int_attr_new(temp_attr_name, i1);
    a5 = int_attr_new(temp_attr_name, i2);
    a6 = int_attr_new(temp_attr_name, i3);

    switch (op) {
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

    cr_assert_eq(rc1, SUCCEEDS,
                 "attribute arithmetic failed unexpectedly "
                 "with type double and operation %s",
                 ops[op]);
    cr_assert_eq(rc2, SUCCEEDS,
                 "attribute arithmetic failed unexpectedly "
                 "with type int and operation %s",
                 ops[op]);

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
Test(custom_actions_effect, add_attr) {
    test_attr_arithmetic(1.0, 2.0, 3.0,
                         1, 2, 3, ADD);
}

/* Testing that sub_attr() succeeds and sets proper value of result attribute
 */
Test(custom_actions_effect, sub_attr) {
    test_attr_arithmetic(5.0, 2.0, 3.0,
                         5, 2, 3, SUB);
}

/* Testing that mult_attr() succeeds and sets proper value of result attribute
 */
Test(custom_actions_effect, mult_attr) {
    test_attr_arithmetic(5.0, 4.0, 20.0,
                         5, 4, 20, MULT);
}

/* Testing that div_attr() succeeds and sets proper value of result attribute
 */
Test(custom_actions_effect, div_attr) {
    test_attr_arithmetic(10.0, 2.0, 5.0,
                         10, 2, 5, DIV);
}

/* Testing that gen_attrval() fails when given an invalid type */
Test(custom_actions_effect, gen_attrval_fail) {
    attribute_t *a;
    int rc;

    char c1 = 'a';
    char *temp_attr_name = "temp";

    a = char_attr_new(temp_attr_name, c1);

    rc = gen_attrval(0, 10, a);

    cr_assert_eq(rc, FAILS,
                 "gen_attrval() failed to recognized invalid "
                 "attribute type (char)");

    attribute_free(a);
}

/* Testing that gen_attrval() succeeds and produces a value within the
 *  specified range for an attribute value of type double */
Test(custom_actions_effect, gen_attrval_double) {
    attribute_t *a;
    int rc;

    double d1 = 0;
    char *temp_attr_name = "temp";

    a = double_attr_new(temp_attr_name, d1);

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
Test(custom_actions_effect, gen_attrval_int) {
    attribute_t *a;
    int rc;

    int i1 = 0;
    char *temp_attr_name = "temp";

    a = int_attr_new(temp_attr_name, i1);

    rc = gen_attrval(20, 50, a);

    cr_assert_eq(rc, SUCCEEDS, "gen_attrval() failed unexpectedly");
    cr_assert_geq(a->attribute_value.int_val, 20,
                  "gen_attrval() produced a value less than lower bound 20");
    cr_assert_leq(a->attribute_value.int_val, 50,
                  "gen_attrval() produced a value greater than upper bound 50");

    attribute_free(a);
}