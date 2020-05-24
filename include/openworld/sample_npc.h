#include "sample_rooms.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum npc_classification {
    NPC_GENERIC = -1,
    NPC_HOSTILE = 0,
    NPC_FRIENDLY = 1
} npc_classification_t;


typedef struct npc
{
    int level;
    item_hash_t *inventory;
    npc_classification_t classification;
    struct npc *next;
    struct npc *prev;
} npc_t;

/* Will get a linked list of hostile npcs
 * makes 2-3 npcs that are hostile and return them 
 * as a linked list
 */
npc_t *get_hostile_npcs();


/*
 * makes 2-3 npcs that are friendly and return them 
 * as a linked list
 */
npc_t *get_friendly_npcs();



/* * makes 2-3 npcs that are generic and return them 
 * as a linked list
 */
npc_t *get_generic_npcs();

