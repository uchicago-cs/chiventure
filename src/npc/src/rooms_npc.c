#include "npc/rooms_npc.h"

/* See rooms_npc.h */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, char* room_id)
{
    assert(npcs_in_room != NULL);
    strncpy(npcs_in_room->room_id, room_id, MAX_ID_LEN);
    npc_hash_t *npcs = NULL;
    npcs_in_room->npc_list = npcs;
    npcs_in_room->num_of_npcs = 0;

    return SUCCESS;
}


/* See rooms_npc.h */
npcs_in_room_t *npcs_in_room_new(char* room_id)
{
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = malloc(sizeof(npcs_in_room_t));
    memset(npcs_in_room, 0, sizeof(npcs_in_room_t));
    npcs_in_room->room_id = malloc(MAX_ID_LEN);

    int check = npcs_in_room_init(npcs_in_room, room_id);

    if (npcs_in_room == NULL || npcs_in_room->room_id == 0 || check != SUCCESS)
    {
        return NULL;
    }

    return npcs_in_room;
}


/* See rooms_npc.h */
int npcs_in_room_free(npcs_in_room_t *npcs_in_room)
{
    assert(npcs_in_room != NULL);

    free(npcs_in_room->room_id);
    HASH_CLEAR(hh_room, npcs_in_room->npc_list);
    free(npcs_in_room);

    return SUCCESS;
}


/* See rooms_npc.h */
int npcs_in_room_get_number(npcs_in_room_t *npcs_in_room)
{
    return npcs_in_room->num_of_npcs;
}


/* See rooms_npc.h */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc)
{
    npc_t *check;
    HASH_FIND(hh_room, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
              check);

    if (check != NULL)
    {
        return FAILURE;
    }
    HASH_ADD_KEYPTR(hh_room, npcs_in_room->npc_list, npc->npc_id,
                    strlen(npc->npc_id), npc);
    npcs_in_room->num_of_npcs++;

    return SUCCESS;
}


/* See rooms_npc.h */
int delete_npc_from_room(npcs_in_room_t *npcs_in_room, npc_t *npc)
{
    npc_t *check;
    HASH_FIND(hh_room, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
              check);

    if (check == NULL)
    {
        return FAILURE;
    }
    HASH_DELETE(hh_room, npcs_in_room->npc_list, check);
    npcs_in_room->num_of_npcs--;

    return SUCCESS;
}