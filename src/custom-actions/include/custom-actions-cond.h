#ifndef CUSTOM_ACTIONS_COND_H
#define CUSTOM_ACTIONS_COND_H

#include "game-state/item.h"
#include "custom-actions-common.h"

/* Enumerative type for numerically comparative conditions */
typedef enum {
    LT,
    GT,
    LTE,
    GTE
} num_comp_t;


/*
 * Atomic Conditionals: functions to check differerent conditions of an action
 */ 


/* 
 * check_eq - determine whether the value of an attribute is equal to another
 *
 * Arguments:
 *  - a1, a2: pointers to attributes to be compared
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILS status code if attribute types cannot be compared
 */
int check_eq(attribute_t *a1, attribute_t *a2);


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
 *  - FAILS status code if attribute types cannot be compared
 */
int check_lt(attribute_t *a1, attribute_t *a2);


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
 *  - FAILS status code if attribute types cannot be compared
 */
int check_gt(attribute_t *a1, attribute_t *a2);


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
 *  - FAILS status code if attribute types cannot be compared
 */
int check_lte(attribute_t *a1, attribute_t *a2);


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
 *  - FAILS status code if attribute types cannot be compared
 */
int check_gte(attribute_t *a1, attribute_t *a2);


/*
 * check_in - determine whether a certain item is in the container
 *
 * Arguments:
 *  - a: string attribute with the name of the item to be checked for
 *  - c: container item to be checked in
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILS status code if invalid input
 *
 * int check_in(attribute_t *a, item_t *c); TO BE IMPLEMENTED
 */


#endif /* CUSTOM_ACTIONS_COND_H */
