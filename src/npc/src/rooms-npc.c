#include "npc/rooms-npc.h"

/* See rooms-npc.h */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, char* room_id)
{
    assert(npcs_in_room != NULL);
    strncpy(npcs_in_room->room_id, room_id, MAX_ID_LEN);
    npcs_in_room->npc_list = NULL;
    npcs_in_room->num_of_npcs = 0;

    return SUCCESS;
}


/* See rooms-npc.h */
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


/* See rooms-npc.h */
int npcs_in_room_free(npcs_in_room_t *npcs_in_room)
{
    assert(npcs_in_room != NULL);

    free(npcs_in_room->room_id);
    HASH_CLEAR(hh_room, npcs_in_room->npc_list);
    free(npcs_in_room);

    return SUCCESS;
}


/* See rooms-npc.h */
int npcs_in_room_get_number(npcs_in_room_t *npcs_in_room)
{
    return npcs_in_room->num_of_npcs;
}


/* See rooms-npc.h */
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

/* See rooms-npc.h */
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

/* Helper function for npc_one_move function */
int room_id_cmp2(room_list_t *room1, room_list_t *room2)
{
    return (strcmp(room1->room->room_id, room2->room->room_id));
}

/* See rooms-npc.h */
int npc_one_move(npc_t *npc)
{

    if(npc->movement == NULL)
    {
        return FAILURE;
    }

    room_t *current_room;
    room_t *next_room;
    npcs_in_room_t *current_npcs_in_room;
    npcs_in_room_t *next_npcs_in_room;


    /* adapted from move_npc_(in)definite functions
     * in npc_move module
     *
     * This adaptation will obtain the list of rooms in an npc's path
     * which will be stored in *current_room_list
     * Thus, we will be able to obtain the current and next room structs
     */
    room_list_t *test = malloc(sizeof(room_list_t));
    test->next = NULL;
    test->room = room_new(npc->movement->track,"test","test");
    room_list_t *current_room_list = malloc(sizeof(room_list_t));

    if(npc->movement->mov_type == NPC_MOV_DEFINITE)
    {
        LL_SEARCH(npc->movement->npc_mov_type.npc_mov_definite->npc_path,
                        current_room_list,test,room_id_cmp2);
    }
    else if(npc->movement->mov_type == NPC_MOV_INDEFINITE)
    {
        LL_SEARCH(npc->movement->npc_mov_type.npc_mov_indefinite->npc_path,
                        current_room_list,test,room_id_cmp2);
    }

    current_room = current_room_list->room;
    next_room = current_room_list->next->room;

    // end of adaptation

    current_npcs_in_room = current_room->npcs;
    next_npcs_in_room = next_room->npcs;

    int rc;

    // this call does all of the moving
    rc = npc_one_move_helper(npc, current_npcs_in_room, next_npcs_in_room);

    return rc;
}

/* See rooms-npc.h */
int npc_one_move_helper(npc_t *npc, npcs_in_room_t *old_npc_room, npcs_in_room_t *new_npc_room)
{
    assert(npc->movement->mov_type == NPC_MOV_INDEFINITE || npc->movement->mov_type == NPC_MOV_DEFINITE );

    if (npc->movement->mov_type == NPC_MOV_INDEFINITE)
        move_npc_indefinite(npc->movement);
    else
        move_npc_definite(npc->movement);

    add_npc_to_room(new_npc_room,npc);
    delete_npc_from_room(old_npc_room,npc);

    return SUCCESS;
}
