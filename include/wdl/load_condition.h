/*
 * Header file for loading condition objects into game struct
 */

#ifndef INCLUDE_LOAD_CONDITION_H
#define INCLUDE_LOAD_CONDITION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wdl_common.h"
#include "validate.h"
#include "load_condition.h"

/* build_condition
 * converts a condition object into a condition struct, which it returns
 * 
 * parameters:
 * - obj: the document object
 * - g: a game pointer as a return parameter
 *
 * side effects:
 * - adds NPCs into the inputted game pointer and 
 *   their respective rooms
 *
 * returns:
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
condition_t *build_condition(obj_t *condition_obj, game_t *g);

#endif /* INCLUDE_LOAD_CONDITION_H */
