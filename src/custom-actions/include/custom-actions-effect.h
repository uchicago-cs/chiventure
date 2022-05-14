#ifndef CUSTOM_ACTIONS_EFFECT_H
#define CUSTOM_ACTIONS_EFFECT_H

#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/room.h"
#include "custom-actions-common.h"

/*
 * custom-actions-effect.h: effect-applying functions
 *
 * Use these fundamental effect-applying functions to define a custom
 * action
 *
 * Author: Brent DeVries
 */

/* Enumerative type for arithmetic effects */
typedef enum
{
    ADD,
    SUB,
    MULT,
    DIV
} arithmetic_op_t;

/* set_attr - set attribute a1 to the value of attribute a2
 *
 * Arguments
 *  - a1: attribute to be modified
 *  - a2: attribute of desired value
 *
 * Returns
 *  - SUCCEEDS/FAILS int status code
 */
int set_attr(attribute_t *a1, attribute_t *a2);

/* add_attr - store sum of first two attributes in third attribute
 *
 * Note: supports attributes of type int or double only (must match)
 *
 * Arguments
 *  - a1, a2: attributes to be summed
 *  - a3: attribute in which to store sum value
 *
 * Returns
 *  - SUCCEEDS/FAILS int status code
 */
int add_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3);

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
 *  - SUCCEEDS/FAILS int status code
 */
int sub_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3);

/* mult_attr - store product of first two attributes in third attribute
 *
 * Note: supports attributes of type int or double only (must match)
 *
 * Arguments
 *  - a1, a2: attributes to be multiplied
 *  - a3: attribute in which to store product
 *
 * Returns
 *  - SUCCEEDS/FAILS int status code
 */
int mult_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3);

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
 *  - SUCCEEDS/FAILS int status code
 */
int div_attr(attribute_t *a1, attribute_t *a2, attribute_t *a3);

/* gen_attrval - generates a random integer between min and max and stores it
 *  in the attribute
 *
 * Arguments
 *  - min: lower bound of random value
 *  - max: upper bound of random value
 *  - a: attribute in which random value will be stored
 *
 * Returns
 *  - SUCCEEDS/FAILS int status code
 */
int gen_attrval(int min, int max, attribute_t *a);

/* TO BE IMPLEMENTED
 *
 *
 * say_phrase - print the given phrase to user interface
 *
 * Arguments
 *  - a: attribute containing string with phrase to say
 *
 * Returns
 *  - SUCCEEDS/FAILS int status code
 *
 * int say_phrase(attribute_t *a);
 */ 

#endif /* CUSTOM_ACTIONS_EFFECT_H */
