/*
 * Header file for loading quest objects into game struct
 */

#ifndef INCLUDE_LOAD_QUESTS_H
#define INCLUDE_LOAD_QUESTS_H

#include "wdl_common.h"
#include "quests/quests_state.h"
#include "validate.h"
#include <assert.h>

/* 
 * Accesses the document object and obtain list of quests to parse into the
 * game struct
 * 
 * parameters:
 * - doc: the document object
 * - game: a game pointer as a return parameter
 *
 * side effects:
 * - adds quests from doc into the g->all_quests 
 *
 * returns:
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_quests(obj_t *doc, game_t *game);


#endif /* INCLUDE_LOAD_QUESTS_H */
