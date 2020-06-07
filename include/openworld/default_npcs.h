#ifndef _DEFAULT_NPCS_H
#define _DEFAULT_NPCS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game-state/game_state_common.h"

/*
* Classification of the type of NPC characters to be found
* within the rooms. Where friendly means NPC doesn't engage in fights,
* Hostile means engages in fights, and generic means can engage in fights
*/

typedef enum npc_classification {
	NPC_GENERIC = -1,
	NPC_HOSTILE = 0,
	NPC_FRIENDLY = 1
} npc_classification_t;


/* NPC mock struct that contains the bare minimum to add a NPC in a
* openworld room.Consists of player level, char *npc_name, NPC type, and item inventory
*/
typedef struct npc
{
	char *npc_name;
	int level;
	item_hash_t *inventory;
	npc_classification_t classification;
	struct npc *next;
	struct npc *prev;
	UT_hash_handle hh;
} npc_t;

/* get_hostile_npcs
* Will get a linked list of hostile npcs and includes the items that
* each NPC carries with them  makes 3 npcs that are hostile and return them
* as a linked list
*/
npc_t *get_hostile_npcs();


/* get_friendly_npcs
* makes 3 npcs that are friendly and includes the items that
* each NPC carries with them. 
* Return them as a hash list
*/
npc_t *get_friendly_npcs();



/* get_generic_npcs
* makes 3 npcs that are generic 
* Return them as a hash list
*/
npc_t *get_generic_npcs();


#endif
