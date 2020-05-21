  
#include "game-state/rpg_npc.h"
#include "common-item.h"

/* See rpg_npc.h */
int npc_init(npc_t *npc, char *npc_id, int health, convo_t *dialogue, stats_hash_t *stats)
{
    assert(npc != NULL);
    strncpy(npc->npc_id, npc_id, strlen(npc_id));
    npc->health = health;
    npc->dialogue = dialogue;
    npc->inventory = NULL;
    npc->stats = stats;

    return SUCCESS;
}

/* See rpg_npc.h */
npc_t *npc_new(char *npc_id, int health, convo_t *dialogue, stats_hash_t *stats)
{
    npc_t *npc;
    npc = malloc(sizeof(npc_t));
    memset(npc, 0, sizeof(npc_t));
    npc->npc_id = malloc(MAX_ID_LEN);

    int check = npc_init(npc, npc_id, health, dialogue, stats); /* where to malloc stats? */

    if (npc == NULL || npc->npc_id == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc;
}