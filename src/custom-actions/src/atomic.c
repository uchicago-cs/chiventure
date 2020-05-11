/*
 * atomic.c: fundamental condition and effect functions
 *
 * Use these functions to check conditions of an action and to apply the
 * effects of an action. The term atomic refers to the fact that the
 * operations performed by these functions cannot be further broken down.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "../structs.h"

/*
 * Atomic Conditionals: functions to check different conditions of an action
 *
 */


/* 
 * check_eq - determine whether an attribute is equal to another
 *
 * Arguments:
 *  - a1, a2: pointers to attributes to be compared
 *
 * Returns:
 *  - TRUE/FALSE int status code
 *  - FAILURE status code if attribute types cannot be compared
 *
 */
int check_eq(attribute_t *a1, attribute_t *a2)
{
    return 0;
}


/* 
 * check_lt - determine whether attribute a1 is less than attribute a2
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
 *
 */
int check_lt(attribute_t *a1, attribute_t *a2)
{
    return 0;
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
 *
 */
int check_gt(attribute_t *a1, attribute_t *a2)
{
    return 0;
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
 *
 */
int check_lte(attribute_t *a1, attribute_t *a2)
{
    return 0;
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
 *
 */
int check_gte(attribute_t *a1, attribute_t *a2)
{
    return 0;
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
 *
 */
int check_in(attribute_t *a, item_t *c)
{
    return 0;
}





/*
 * Atomic Effects: functions to apply effects of an action
 *
 */


/* set_attr - set attribute a1 to the value of attribute a2
 *
 * Arguments
 *  - a1: attribute to be modified
 *  - a2: attribute of desired value
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int set_attr(attribute_t *a1, attribut_t *a2)
{
    return 0;
}


/* say_phrase - print the given phrase to user interface
 *
 * Arguments
 *  - a: attribute containing string with phrase to say
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int say_phrase(attribute_t *a)
{
    return 0;
}


/* move_player - move player to a room
 *
 * Arguments
 *  - p: player
 *  - r: destination room
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int move_player(player_t *p, room_t *r)
{
    return 0;
}


/* add_attr - store sum of first two attributes in third attribute
 *
 * Note: supports attributes of type int or double only (must match)
 *
 * Arguments
 *  - a1, a2: attributes to be summed
 *  - a3: attribute in which to store sum value
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int add_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    return 0;
}


/* sub_attr - subtract second attribute from first attribute and store
 *  difference in third attribute
 *
 * Note: supports attributes of type int or double only (must match)
 *
 * Arguments
 *  - a1, a2: attributes to be differenced
 *  - a3: attribute in which to store difference
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int sub_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    return 0;
}


/* mult_attr - store product of first two attributes in third attribute 
 *
 * Note: supports attributes of type int or double only (must match)
 *
 * Arguments
 *  - a1, a2: attributes to be multiplied
 *  - a3: attribute in which to store product
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int mult_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    return 0;
}


/* div_attr - divide first attribute by second attribute and store quotient in
 *  third
 *
 * Note: supports attributes of type int or double only (must match)
 *
 * Arguments
 *  - a1, a2: attributes to be divided
 *  - a3: attribute in which to store quotient
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int div_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3)
{
    return 0;
}


/* gen_attrval - generates a random integer between min and max and stores it
 *  in the attribute
 *
 * Arguments
 *  - min: lower bound of random value
 *  - max: upper bound of random value
 *  - a: attribute in which random value will be stored
 *
 * Returns
 *  - SUCCESS/FAILURE int status code
 *
 */
int gen_attrval(int min, int max, attribute_t *a)
{
    return 0;
}
