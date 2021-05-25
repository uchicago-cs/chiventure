/*
 * Header file for loading NPC objects into game struct
 */

#ifndef INCLUDE_LOAD_NPC_H
#define INCLUDE_LOAD_NPC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wdl_common.h"
#include "validate.h"
#include "game-state/game.h"
#include "npc/npc.h"

/* load_npcs
 * accesses the document object and obtain list of NPCs to parse into the
 * game_state structs and adds to the inputted game pointer
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
int load_npcs(obj_t *doc, game_t *g);

/* load_npc_inventory
 * loads the NPC's inventory
 *
 * parameters:
 * - inventory_lst_obj: list of item IDs
 * - npc: an NPC
 * - g: game (required for access to all_items)
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_npc_inventory(obj_t *inventory_lst_obj, npc_t *npc, game_t *g);

/* load_dialogue
 * loads dialogue into the given NPC
 *
 * parameters:
 * - npc_obj: the NPC object
 * - npc: an NPC
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_dialogue(obj_t *npc_obj, npc_t *npc);

/* load_node_actions
 * loads node actions into the given node
 *
 * parameters:
 * - actions_obj: the actions object
 * - convo: a convo
 * - node_id: the node's ID
 * - npc: the NPC (for item checking)
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_node_actions(obj_t *actions_obj, convo_t *convo, char *node_id,
                      npc_t *npc);

#endif /* INCLUDE_LOAD_NPC_H */
