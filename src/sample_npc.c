#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "game-state/item.h"
//#include "game-state/game_action.h"
#include "sample_npc.h"



/* See samples_npc.h */
int npc_init(npc_t *new_player, char *player_id, char *short_desc,
              char *long_desc)
{
   // plyr->level = 1;
    assert(new_player != NULL);
    strcpy(new_player->npc_id, player_id);
    strcpy(new_player->npc_sdesc, short_desc);
    strcpy(new_player->npc_ldesc, long_desc);

    return SUCCESS;
}

/* See samples_npc.h */
npc_t* new_npc(char *npc_id, char *npc_ldesc, char *npc_sdesc, char *npc_qdesc)

{
    npc_t *new_player = malloc(sizeof(npc_t));
    memset(new_player, 0, sizeof(npc_t));
    new_player->npc_id = malloc(MAX_ID_LEN * sizeof(char)); // tentative size allocation
    new_player->short_desc = malloc(MAX_SDESC_LEN * sizeof(char));
    new_player->long_desc = malloc(MAX_LDESC_LEN * sizeof(char));
   // new_player->npc_qdesc = malloc(MAX_QDESC_LEN * sizeof(char));

    int check = npc_init(new_player, npc_id, short_desc, long_desc);

    if (new_player == NULL || new_player->npc_id == NULL ||
            new_player->short_desc == NULL || new_player->long_desc == NULL)
    {
        return NULL; //npc struct not properly malloced
    }
    if(check != SUCCESS)
    {
        return NULL;
    }
   
    return new_player;

}

