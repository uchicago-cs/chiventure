#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/custom-actions-cond.h"
#include "../../../include/game-state/item.h"


/*
 * Atomic Conditionals: functions to check different conditions of an action
 */ 


/* Enumerative type for numerically comparative conditions */
typedef enum {
    LT,
    GT,
    LTE,
    GTE
} num_comp;


/* See custom-actions-cond.h */
int check_eq(attribute_t *a1, attribute_t *a2)
{
    if (a1->attribute_tag != a2->attribute_tag) {
        return FAILURE;
    }

    switch (a1->attribute_tag) {

        case STRING:
            int strcmp = strcmp(a1->attribute_value, a2->attribute_value);
            return strcmp ? FALSE : TRUE;
        
        default:
            int cmp = (a1->attribute_value == a2->attribute_value);
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
 *  - FAILURE status code if attribute types cannot be compared
 */
int num_comp(attribute_t *a1, attribute_t *a2, num_comp op)
{
    if (a1->attribute_tag != a2->attribute_tag) {
        return FAILURE;
    }

    if (a1->attribute_tag == BOOLEAN || a1->attribute_tag == STRING) {
        return FAILURE;
    }

    switch (op) {

        case LT:
            int lt = (a1->attribute_value < a2->attribute_value);
            return lt ? TRUE : FALSE;
        
        case GT:
            int gt = (a1->attribute_value > a2->attribute_value);
            return gt ? TRUE : FALSE;

        case LTE:
            int lte = (a1->attribute_value <= a2->attribute_value);
            return lte ? TRUE : FALSE;

        default:
            int gte = (a1->attribute_value >= a2->attribute_value);
            return gte ? TRUE : FALSE;
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


/* See custom-actions-cond.h */
int check_in(attribute_t *a, item_t *c)
{
        return 0;
}
