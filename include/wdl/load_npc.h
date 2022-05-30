/*
 * Header file for loading NPC objects into game struct
 */

#ifndef INCLUDE_LOAD_NPC_H
#define INCLUDE_LOAD_NPC_H

#include "wdl_common.h"
#include "validate.h"
#include "load_condition.h"
#include "npc/rooms_npc.h"

/* load_npcs
 * accesses the document object and obtain list of NPCs to parse into the
 * game struct
 * 
 * parameters:
 * - obj: the document object
 * - g: a game pointer as a return parameter
 *
 * side effects:
 * - adds NPCs into the inputted game pointer and their respective rooms
 *
 * returns:
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_npcs(obj_t *doc, game_t *g);


#endif /* INCLUDE_LOAD_NPC_H */
