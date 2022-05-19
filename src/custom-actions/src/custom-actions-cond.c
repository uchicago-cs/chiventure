#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game-state/item.h"
#include "custom-actions-common.h"
#include "custom-actions-cond.h"

/*
 * Atomic Conditionals: functions to check different conditions of an action
 */ 


/* See custom-actions-cond.h */
int check_eq(attribute_t *a1, attribute_t *a2)
{
    if (a1->attribute_tag != a2->attribute_tag) {
        return FAILS;
    }

    int cmp;

    switch (a1->attribute_tag) {

        case DOUBLE:
            cmp = (a1->attribute_value.double_val ==
                   a2->attribute_value.double_val);
            return cmp ? TRUE : FALSE;

        case BOOLE:
            cmp = (a1->attribute_value.bool_val ==
                   a2->attribute_value.bool_val);
            return cmp ? TRUE : FALSE;

        case CHARACTER:
            cmp = (a1->attribute_value.char_val ==
                   a2->attribute_value.char_val);
            return cmp ? TRUE : FALSE;

        case STRING:
            cmp = strcmp(a1->attribute_value.str_val,
                         a2->attribute_value.str_val);
            return cmp ? FALSE : TRUE;
        
        default:
            cmp = (a1->attribute_value.int_val == a2->attribute_value.int_val);
            return cmp ? TRUE : FALSE;
    }
}


/* int_comp - compares two attributes with values of type int
 *
 * Arguments:
 *  - a1, a2: attributes to be compared
 *  - op: comparative operator to be used
 *
 * Returns:
 *  - TRUE/FALSE int status code
 */
int int_comp(attribute_t *a1, attribute_t *a2, num_comp_t op)
{
    int cmp;
    
    switch (op) {

        case LT:
            cmp = (a1->attribute_value.int_val < a2->attribute_value.int_val);
            return cmp ? TRUE : FALSE;
        
        case GT:
            cmp = (a1->attribute_value.int_val > a2->attribute_value.int_val);
            return cmp ? TRUE : FALSE;

        case LTE:
            cmp = (a1->attribute_value.int_val <= a2->attribute_value.int_val);
            return cmp ? TRUE : FALSE;

        default:
            cmp = (a1->attribute_value.int_val >= a2->attribute_value.int_val);
            return cmp ? TRUE : FALSE;
    }
}


/* double_comp - compares two attributes with values of type double
 *
 * Arguments:
 *  - a1, a2: attributes to be compared
 *  - op: comparative operator to be used
 *
 * Returns:
 *  - TRUE/FALSE int status code
 */
int double_comp(attribute_t *a1, attribute_t *a2, num_comp_t op)
{
    int cmp;
    
    switch (op) {

        case LT:
            cmp = (a1->attribute_value.double_val <
                   a2->attribute_value.double_val);
            return cmp ? TRUE : FALSE;
        
        case GT:
            cmp = (a1->attribute_value.double_val >
                   a2->attribute_value.double_val);
            return cmp ? TRUE : FALSE;

        case LTE:
            cmp = (a1->attribute_value.double_val <=
                   a2->attribute_value.double_val);
            return cmp ? TRUE : FALSE;

        default:
            cmp = (a1->attribute_value.double_val >=
                   a2->attribute_value.double_val);
            return cmp ? TRUE : FALSE;
    }
}


/* char_comp - compares two attributes with values of type char
 *
 * Arguments:
 *  - a1, a2: attributes to be compared
 *  - op: comparative operator to be used
 *
 * Returns:
 *  - TRUE/FALSE int status code
 */

int char_comp(attribute_t *a1, attribute_t *a2, num_comp_t op)
{
    int cmp;

    switch (op) {

        case LT:
            cmp = (a1->attribute_value.char_val <
                   a2->attribute_value.char_val);
            return cmp ? TRUE : FALSE;
        
        case GT:
            cmp = (a1->attribute_value.char_val >
                   a2->attribute_value.char_val);
            return cmp ? TRUE : FALSE;

        case LTE:
            cmp = (a1->attribute_value.char_val <=
                   a2->attribute_value.char_val);
            return cmp ? TRUE : FALSE;

        default:
            cmp = (a1->attribute_value.char_val >=
                   a2->attribute_value.char_val);
            return cmp ? TRUE : FALSE;
    }
}


/* num_comp - compares two attributes with numerical values
 *
 * Arguments:
 *  - a1, a2: attributes to be compared
 *  - op: comparative operator to be used
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILS status code if attribute types cannot be compared
 */
int num_comp(attribute_t *a1, attribute_t *a2, num_comp_t op)
{
    if (a1->attribute_tag != a2->attribute_tag) {
        return FAILS;
    }

    if (a1->attribute_tag == BOOLE || a1->attribute_tag == STRING) {
        return FAILS;
    }

    switch (a1->attribute_tag) {

        case INTEGER:
            return int_comp(a1, a2, op);
        
        case DOUBLE:
            return double_comp(a1, a2, op);

        default:
            return char_comp(a1, a2, op);
    }
}


/* See custom-actions-cond.h */
int check_lt(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, LT);
}


/* See custom-actions-cond.h */
int check_gt(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, GT);
}


/* See custom-actions-cond.h */
int check_lte(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, LTE);
}


/* See custom-actions-cond.h */
int check_gte(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, GTE);
}


/* To be implemented:
 *
 * int check_in(attribute_t *a, item_t *c)
 */

