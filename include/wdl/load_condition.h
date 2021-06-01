/*
 * Header file for loading condition objects into game struct
 */

#ifndef INCLUDE_LOAD_CONDITION_H
#define INCLUDE_LOAD_CONDITION_H

#include "wdl_common.h"
#include "validate.h"

/* build_conditions
 * converts a conditions object into a condition list, which it returns
 * 
 * parameters:
 * - conditions_obj: the conditions object
 * - g: the game
 *
 * returns:
 * - the condition list
 * - NULL if unsuccessful
 */
condition_t *build_conditions(obj_t *conditions_obj, game_t *g);


#endif /* INCLUDE_LOAD_CONDITION_H */
