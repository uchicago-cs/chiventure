#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


typedef enum {
    LT,
    GT,
    LTE,
    GTE
} num_comp;


/*
 * Atomic Conditionals: functions to check different conditions of an action
 */ 


/* 
 * check_eq - determine whether the value of an attribute is equal to another
 *
 * Arguments:
 *  - a1, a2: pointers to attributes to be compared
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILURE status code if attribute types cannot be compared
 */
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


/* 
 * check_lt - determine whether attribute a1 is less than attribute a2
 *
 * Notes:
 *  - supports attributes of type int, double, or character
 *
 * Arguments:
 *  - a1, a2: pointers to attributes to be compared
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILURE status code if attribute types cannot be compared
 */
int check_lt(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, LT);
}


/* 
 * check_gt - determine whether attribute a1 is greater than attribute a2
 *
 * Notes:
 *  - supports attributes of type int or double only
 *
 * Arguments:
 *  - a1, a2: pointers to attributes to be compared
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILURE status code if attribute types cannot be compared
 */
int check_gt(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, GT);
}


/* 
 * check_lte - determine whether attribute a1 is less than or equal to
 *  attribute a2
 *
 * Notes:
 *  - supports attributes of type int or double only
 *
 * Arguments:
 *  - a1, a2: pointers to attributes to be compared
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILURE status code if attribute types cannot be compared
 */
int check_lte(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, LTE);
}


/* 
 * check_gte - determine whether attribute a1 is greater than or equal to
 *  attribute a2
 *
 * Notes:
 *  - supports attributes of type int or double only
 *
 * Arguments:
 *  - a1, a2: pointers to attributes to be compared
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILURE status code if attribute types cannot be compared
 */
int check_gte(attribute_t *a1, attribute_t *a2)
{
    num_comp(a1, a2, GTE);
}


/*
 * check_in - determine whether a certain item is in the container
 *
 * Arguments:
 *  - a: string attribute with the name of the item to be checked for
 *  - c: container item to be checked in
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILURE status code if invalid input
 */
int check_in(attribute_t *a, item_t *c)
{
        return 0;
}
