#include "game_state_common.h"
#include "item.h"
#include "room.h"
#include "npc.h"
#include "game-state/rooms-npcs.h"
#include "custom-scripts/custom_type.h"

/* See npc.h */

/*Object_t Description: object_t is the generic custom scripts struct 
that can hold a variety of different types including "char*".*/

/*Changes to Room_ID: We are using this struct to modify the room_id 
which will enable custom scripts and lua files to be loaded*/ 
int npc_in_room_init(npcs_in_room_t *npcs_in_room, object_t room_id) {
    assert(npcs_in_room != NULL);

    npcs_in_room->room_id = room_id;
    npcs_in_room->npc_list = NULL;
    npcs_in_room->num_of_npcs = 0;

    return SUCCESS;
}

/* See npc.h */
/*Changes to Room_ID: We are using this struct to modify the room_id 
which will enable custom scripts and lua files to be loaded*/ 
int npc_mov_init(npc_mov_t *npc_mov, object_t npc_id, npc_mov_type_e mov_type,
                object_t room_id)
{
    assert(npc_mov != NULL);

    npcs_in_room->npc_id = room_id;
    npcs_in_room->npc_list = NULL;
    npcs_in_room->num_of_npcs = 0;

    return SUCCESS;
}

/* See npc.h */
/*Changes to Room_ID: We are using this struct to modify the room_id 
which will enable custom scripts and lua files to be loaded*/ 
npcs_in_room_t *npcs_in_room_new(object_t room_id){
    npcs_in_room_t *npcs_in_room;
    npcs_in_room = malloc(sizeof(npcs_in_room_t));
    memset(npcs_in_room, 0, sizeof(npcs_in_room_t));
    npcs_in_room->room_id = room_id;
    npcs_in_room->num_of_npcs = 0;
    
    int check = npcs_in_room_init(npcs_in_room, room_id);

    if (npcs_in_room == NULL || str_t_get(npcs_in_room->room_id) == NULL || check != SUCCESS)
    {
        return NULL;
    }
    return npcs_in_room;
}

/* See npc.h */
int npcs_in_room_free(npcs_in_roomt_t *npcs_in_room){
    //free(npcs_in_room->room_id);
    free(npcs_in_room->npc_list);
    free(npcs_in_room->num_of_npcs);
    free(npcs_in_room);
    return SUCCESS;
}


/* See npc.h */
int get_num_of_npcs(npcs_in_room_t *npcs_in_room){
    return npcs_in_room->num_of_npcs;
}


/* See npc.h */
int add_npc_to_room(npcs_in_room_t *npcs_in_room, npc_t *npc){
    npc_t *check;
    HASH_FIND(hh, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check);
 
    if (check != NULL){
        return FAILURE; //this item id is already in use
    }
    HASH_ADD_KEYPTR(hh, npcs_in_room->npc_list, npc->npc_id,
                    strlen(npc->npc_id), npc);
    npcs_in_room->num_of_npcs++;

    return SUCCESS;
}

/* See npc.h */
int extend_path_def(npc_mov_t *npc_mov, room_t *room_to_add){
    //npc_mov_type_e mov_type = npc_mov->mov_type;
    //mov_def_t *mov_def = npc_mov->npc_mov_type_u->mov_def;
    room_list_t *def_path = npc_mov->npc_mov_type->mov_def->npc_path;
    if (def_path == NULL)
        return 0;
    else {
        room_list_t *tmp = def_path;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next->room = room_to_add;
        tmp->next->next = NULL;
        return 1;
    }
}
    

/* See npc.h */
int extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time){
    //npc_mov_type_e mov_type = npc_mov->mov_type;
    //mov_def_t *mov_def = npc_mov->npc_mov_type_u->mov_def;
    room_list_t *indef_path = npc_mov->npc_mov_type->mov_indef->npc_path;
    if (indef_path == NULL)
        return 0;
    else {
        room_list_t *tmp = indef_path;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next->room = room_to_add;
        tmp->next->next = NULL;

        time_in_room_hash_t *check;
        HASH_FIND (hh, npc_mov->npc_mov_type->mov_indef->room_time, 
            npc_mov->npc_mov_type->mov_indef->room_time->sec, check);

        if (check){
            HASH_ADD_KEYPTR (hh, npc_mov->npc_mov_type->mov_indef->room_time, 
                npc_mov->npc_mov_type->mov_indef->room_time->sec, time);
            return 1;
        }
        else
            return 0;
    }
}
