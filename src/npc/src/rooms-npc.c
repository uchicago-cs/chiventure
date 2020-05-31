#include "npc/rooms-npc.h"
#include "common-item.h"

/* See rooms-npc.h */
int npcs_in_room_init(npcs_in_room_t *npcs_in_room, char* room_id)
{
    assert(npcs_in_room != NULL);
    strncpy(npcs_in_room->room_id, room_id, strlen(room_id));
    npcs_in_room->npc_list = NULL;
    npcs_in_room->num_of_npcs = 0;

    return SUCCESS;
}


/* See rooms-npc.h */
int npc_mov_init(npc_mov_t *npc_mov, char* npc_id, npc_mov_enum_t mov_type,
                room_t *room)
{
    char* room_id  = room->room_id;
    assert(npc_mov != NULL);
    strncpy(npc_mov->npc_id,npc_id,strlen(npc_id));
    npc_mov->mov_type = mov_type;
    strncpy(npc_mov->track,room_id,strlen(room_id));

    room_list_t* room_to_add = malloc(sizeof(room_list_t));
    room_to_add->next = NULL;
    room_to_add->room = room;

    room_list_t* head = NULL;    
    
    if (mov_type == MOV_DEF)
    {
        npc_mov->npc_mov_type.mov_def->npc_path = head;
        LL_APPEND(head,room_to_add);
    }
    else if (mov_type == MOV_INDEF )
    {
        npc_mov->npc_mov_type.mov_indef->npc_path = head;
        LL_APPEND(head,room_to_add);
        npc_mov->npc_mov_type.mov_indef->room_time = NULL;
    }
    

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
npc_mov_t* npc_mov_new(char* npc_id, npc_mov_enum_t mov_type, room_t* room)
{
    npc_mov_t *npc_mov;
    npc_mov = malloc(sizeof(npc_mov_t));
    memset(npc_mov, 0, sizeof(npc_mov_t));
    npc_mov->npc_id = malloc(MAX_ID_LEN);
    npc_mov->track = malloc(MAX_ID_LEN);

    if (mov_type == MOV_DEF)
    {
        npc_mov->npc_mov_type.mov_def = malloc(sizeof(mov_def_t));
        memset(npc_mov->npc_mov_type.mov_def, 0, sizeof(mov_def_t));

    }
    else if (mov_type == MOV_INDEF )
    {
        npc_mov->npc_mov_type.mov_indef = malloc(sizeof(mov_indef_t));
        memset(npc_mov->npc_mov_type.mov_indef, 0, sizeof(mov_indef_t));
    }

    int check = npc_mov_init(npc_mov, npc_id, mov_type, room);

    if (npc_mov == NULL || npc_mov->npc_id == NULL || check != SUCCESS)
    {
        return NULL;
    }
    return npc_mov;
}


/* See rooms-npc.h */
int npcs_in_room_free(npcs_in_room_t *npcs_in_room)
{
    assert(npcs_in_room != NULL);

    free(npcs_in_room->room_id);
    free(npcs_in_room->npc_list);
    free(npcs_in_room);
    return SUCCESS;
}


/* See rooms-npc.h */
int npc_mov_free(npc_mov_t *npc_mov) {

    assert(npc_mov != NULL);

    free(npc_mov->npc_mov_type.mov_indef);
    free(npc_mov->track);
    free(npc_mov->npc_id);
    free(npc_mov);
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
    HASH_FIND(hh, npcs_in_room->npc_list, npc->npc_id, strlen(npc->npc_id),
             check);
 
    if (check != NULL)
    {
        return FAILURE; //this npc is already in the room
    }
    HASH_ADD_KEYPTR(hh, npcs_in_room->npc_list, npc->npc_id,
                    strlen(npc->npc_id), npc);
    npcs_in_room->num_of_npcs++;

    return SUCCESS;
}

/* See rooms-npc.h */
int register_time_in_room(npc_mov_t *npc_mov, room_t *room, int time)
{
    assert(room != NULL);
    
    time_in_room_t *return_time;
    //HASH_FIND(hh, npc_mov->npc_mov_type.mov_indef->room_time,
    //            &room->room_id, strlen(room->room_id), return_time);

    time_in_room_t *new_time_in_room;
    new_time_in_room = malloc(sizeof(time_in_room_t));
    strcpy(new_time_in_room->room_id, room->room_id); 
    new_time_in_room->time = time;

    HASH_REPLACE_PTR(npc_mov->npc_mov_type.mov_indef->room_time,
                    room_id, new_time_in_room, return_time);
    
    free(return_time);
    /*
   if (return_time != NULL)
   {
       
   }
   else
   {
       HASH_ADD_KEYPTR(hh, npc_mov->npc_mov_type.mov_indef->room_time,
                    room->room_id,strlen(room->room_id), new_time_in_room);
   }
   */
   
   return SUCCESS;
}


/* See rooms-npc.h */
int extend_path_def(npc_mov_t *npc_mov, room_t *room_to_add) {
    
    assert(room_to_add != NULL);

    room_list_t* room_to_add2 = malloc(sizeof(room_list_t));
    room_to_add2->next  = NULL;
    room_to_add2->room = room_to_add;
    
    room_list_t* head = npc_mov->npc_mov_type.mov_def->npc_path;

    LL_APPEND(head, room_to_add2);

    return SUCCESS;
}  


/* See rooms-npc.h */
int extend_path_indef(npc_mov_t *npc_mov, room_t *room_to_add, int time) {
   
    assert(room_to_add != NULL);

    room_list_t* room_to_add2 = malloc(sizeof(room_list_t));
    room_to_add2->next  = NULL;
    room_to_add2->room = room_to_add;

    room_list_t *head = npc_mov->npc_mov_type.mov_indef->npc_path;

    LL_APPEND(head, room_to_add2);

    int check = register_time_in_room(npc_mov, room_to_add, time);

    if (check != SUCCESS)
        return FAILURE;
    else
        return SUCCESS;
}


/* See rooms-npc.h */
char* track_room(npc_mov_t *npc_mov) {
    return npc_mov->track;
}


/* See rooms-npc.h */
int reverse_path(npc_mov_t *npc_mov) {
    int type = npc_mov->mov_type;

    if (type != 1)
        return FAILURE;
    else
    {
        room_list_t *reversed_path = malloc(sizeof(room_list_t));

        room_list_t *def_path = npc_mov->npc_mov_type.mov_def->npc_path;
        room_list_t *tmp;
        LL_FOREACH(def_path, tmp) {
            LL_PREPEND(reversed_path, tmp);
        }
        free(def_path);
        npc_mov->npc_mov_type.mov_def->npc_path = reversed_path;
    }
}