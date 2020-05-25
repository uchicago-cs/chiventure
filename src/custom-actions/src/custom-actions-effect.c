#include <stdio.h>
#include <stdlib.h>
#include "game-state/item.h"
#include "custom-actions-common.h"
#include "custom-actions-effect.h"


/*
 * custom-actions-effect.c: effect-applying functions
 *
 * Use these fundamental effect-applying functions to define a custom
 * action
 *
 * Author: Brent DeVries
 */


/* See custom-actions-effect.h */
int set_attr(attribute_t *a1, attribute_t *a2)
{
    if (a1->attribute_tag != a2->attribute_tag) {
        return FAIL;
    }

    switch (a1->attribute_tag) {

        case DOUBLE:
            a1->attribute_value.double_val = a2->attribute_value.double_val;
            return SUCCESS;
        case BOOLE:
            a1->attribute_value.bool_val = a2->attribute_value.bool_val;
            return SUCCESS;
        case CHARACTER:
            a1->attribute_value.char_val = a2->attribute_value.char_val;
            return SUCCESS;
        case STRING:
            a1->attribute_value.str_val = a2->attribute_value.str_val;
            return SUCCESS;
        default:
            a1->attribute_value.int_val = a2->attribute_value.int_val;
            return SUCCESS;
    }
}


/*
 * double_arithmetic - helper to perform arithmetic operations on attribute
 *  values of type double
 *
 * Arguments:
 *  - a1, a2: respective operator arguments
 *  - a3: attribute to store result of operation
 *  - op: type of arithmetic operation
 *
 * Returns:
 *  - void
 */
void double_arithmetic(attribute_t *a1, attribute_t *a2, attribute_t *a3,
                      arithmetic_op_t op)
{
    switch (op) {

        case ADD:
            a3->attribute_value.double_val =
                a1->attribute_value.double_val + a2->attribute_value.double_val;
        case SUB:
            a3->attribute_value.double_val =
                a1->attribute_value.double_val - a2->attribute_value.double_val;
        case MULT:
            a3->attribute_value.double_val =
                a1->attribute_value.double_val * a2->attribute_value.double_val;
        default:
            a3->attribute_value.double_val =
                a1->attribute_value.double_val / a2->attribute_value.double_val;
    }
}


/*
 * int_arithmetic - helper to perform arithmetic operations on attribute
 *  values of type int
 *
 * Arguments:
 *  - a1, a2: respective operator arguments
 *  - a3: attribute to store result of operation
 *  - op: type of arithmetic operation
 *
 * Returns:
 *  - void
 */
void int_arithmetic(attribute_t *a1, attribute_t *a2, attribute_t *a3,
                      arithmetic_op_t op)
{
    switch (op) {

        case ADD:
            a3->attribute_value.int_val =
                a1->attribute_value.int_val + a2->attribute_value.int_val;
        case SUB:
            a3->attribute_value.int_val =
                a1->attribute_value.int_val - a2->attribute_value.int_val;
        case MULT:
            a3->attribute_value.int_val =
                a1->attribute_value.int_val * a2->attribute_value.int_val;
        default:
            a3->attribute_value.int_val =
                a1->attribute_value.int_val / a2->attribute_value.int_val;
    }
}


/* attr_arithmetic - helper to perform arithmetic operations on attribute
 *  values
 *
 * Arguments:
 *  - a1, a2: respective operator arguments
 *  - a3: attribute to store result of operation
 *  - op: type of arithmetic operation
 *  
 * Returns:
 *  - SUCCESS/FAIL int status code
 */
int attr_arithmetic(attribute_t *a1, attribute_t *a2, attribute_t *a3,
                    arithmetic_op_t op)
{
    if (a1->attribute_tag != a2->attribute_tag) {
        return FAIL;
    }

    if (a1->attribute_tag != INTEGER && a1->attribute_tag != DOUBLE) {
        return FAIL;
    }

    a3->attribute_tag = a1->attribute_tag;

    switch (a1->attribute_tag) {

        case DOUBLE:
            double_arithmetic(a1, a2, a3, op);
            return SUCCESS;
        default:
            int_arithmetic(a1, a2, a3, op);
            return SUCCESS;
    }
}


/* See custom-actions-effect.h */
int add_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    attr_arithmetic(a1, a2, a3, ADD);
}


/* See custom-actions-effect.h */
int sub_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    attr_arithmetic(a1, a2, a3, SUB);
}


/* See custom-actions-effect.h */
int mult_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    attr_arithmetic(a1, a2, a3, MULT);
}


/* See custom-actions-effect.h */
int div_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    attr_arithmetic(a1, a2, a3, DIV);
}


/* See custom-actions-effect.h */
int gen_attrval(int min, int max, attribute_t *a)
{
    if (a->attribute_tag != INTEGER && a->attribute_tag != DOUBLE) {
        return FAIL;
    }

    int rand;

    rand = (rand() % (max - min + 1)) + min;

    switch (a->attribute_tag) {

        case DOUBLE:
            a->attribute_value.double_val = rand;
            return SUCCESS;
        default:
            a->attribute_value.int_val = rand;
            return SUCCESS;
    }
}


/* TO BE IMPLEMENTED:
 *
 * int say_phrase(attribute_t *a);
 * int move_player(player_t *p, room_t *r);
 */
