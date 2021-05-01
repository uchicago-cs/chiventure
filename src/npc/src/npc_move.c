#include "npc/npc_move.h"

// STRUCT FUNCTIONS -----------------------------------------------------------
/* See npc_move.h */
int npc_mov_init(npc_mov_t *npc_mov, npc_mov_enum_t mov_type,
                room_t *room)
{
    char* room_id  = room->room_id;
    assert(npc_mov != NULL);
    npc_mov->mov_type = mov_type;
    strncpy(npc_mov->track,room_id, MAX_ID_LEN);

    room_list_t* room_to_add = malloc(sizeof(room_list_t));
    room_to_add->next = NULL;
    room_to_add->room = room;

    room_list_t* head = NULL;    
    
    if (mov_type == NPC_MOV_DEFINITE)
    {
        LL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
        room_to_add);
    }
    else if (mov_type == NPC_MOV_INDEFINITE )
    {
        LL_APPEND(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path
        ,room_to_add);
        npc_mov->npc_mov_type.npc_mov_indefinite->room_time = NULL;
    }
    
    return SUCCESS;
}


/* See npc_move.h */
npc_mov_t* npc_mov_new(npc_mov_enum_t mov_type, room_t* room)
{
    npc_mov_t *npc_mov;
    npc_mov = malloc(sizeof(npc_mov_t));
    memset(npc_mov, 0, sizeof(npc_mov_t));
    npc_mov->track = malloc(MAX_ID_LEN);

    if (mov_type == NPC_MOV_DEFINITE)
    {
        npc_mov->npc_mov_type.npc_mov_definite = malloc(sizeof(npc_mov_definite_t));
        memset(npc_mov->npc_mov_type.npc_mov_definite, 0, sizeof(npc_mov_definite_t));

    }
    else if (mov_type == NPC_MOV_INDEFINITE )
    {
        npc_mov->npc_mov_type.npc_mov_indefinite = malloc(sizeof(npc_mov_indefinite_t));
        memset(npc_mov->npc_mov_type.npc_mov_indefinite, 0, sizeof(npc_mov_indefinite_t));
    }

    int check = npc_mov_init(npc_mov, mov_type, room);

    if (npc_mov == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc_mov;
}


/* See npc_move.h */
int npc_mov_free(npc_mov_t *npc_mov) {

    assert(npc_mov != NULL);

    free(npc_mov->npc_mov_type.npc_mov_indefinite);
    free(npc_mov->track);
    free(npc_mov);
}


/* See npc_move.h */
int register_npc_room_time(npc_mov_t *npc_mov, room_t *room, int time)
{
    assert(room != NULL);
    
    npc_room_time_t *return_time;

    npc_room_time_t *new_npc_room_time;
    new_npc_room_time = malloc(sizeof(npc_room_time_t));
    memset(new_npc_room_time, 0, sizeof(npc_room_time_t));
    new_npc_room_time->room_id = malloc(MAX_ID_LEN);
    strcpy(new_npc_room_time->room_id, room->room_id); 
    new_npc_room_time->time = time;

    HASH_REPLACE(hh, npc_mov->npc_mov_type.npc_mov_indefinite->room_time,
                    room_id, strlen(room->room_id), 
                    new_npc_room_time, return_time);
    
    free(return_time);

    HASH_ADD_KEYPTR(hh, npc_mov->npc_mov_type.npc_mov_indefinite->room_time,
            room->room_id, strlen(room->room_id), new_npc_room_time);
   
    return SUCCESS;
}


/* See npc_move.h */
int extend_path_definite(npc_mov_t *npc_mov, room_t *room_to_add) 
{
    assert(room_to_add != NULL);
    assert(npc_mov != NULL);

    room_list_t* room_to_add2 = (room_list_t*)malloc(sizeof(room_list_t));
    room_to_add2->next = NULL;
    room_to_add2->room = room_to_add;

    LL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
            room_to_add2);

    return SUCCESS;
}  


/* See npc_move.h */
int extend_path_indefinite(npc_mov_t *npc_mov, room_t *room_to_add, int time) 
{   
    assert(room_to_add != NULL);

    room_list_t* room_to_add2 = malloc(sizeof(room_list_t));
    room_to_add2->next = NULL;
    room_to_add2->room = room_to_add;

    LL_APPEND(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path,
         room_to_add2);

    int check = register_npc_room_time(npc_mov, room_to_add, time);

    if (check != SUCCESS)
        return FAILURE;
    else
        return SUCCESS;
}


/* See npc_move.h */
char* track_room(npc_mov_t *npc_mov) 
{
    return npc_mov->track;
}


/* See npc_move.h */
int reverse_path(npc_mov_t *npc_mov) 
{
    assert(npc_mov->mov_type == NPC_MOV_DEFINITE);

    room_list_t *reversed_path_head = NULL;

    room_list_t *room_elt, *room_tmp;
    LL_FOREACH_SAFE(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                room_elt,room_tmp)
    {
        room_list_t* append_room = malloc(sizeof(room_list_t));
        append_room->next = NULL;
        append_room->room = room_elt->room;
        LL_PREPEND(reversed_path_head, append_room);
        LL_DELETE(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                  room_elt);
        free(room_elt);
    }

    room_list_t *tmp2;
    LL_FOREACH(reversed_path_head, tmp2)
    {
        room_list_t* reappend_room = malloc(sizeof(room_list_t));
        reappend_room->next = NULL;
        reappend_room->room = tmp2->room;
        LL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                reappend_room);
    }

    return SUCCESS;
}

/* Helper function for move_npc_def function */
int room_id_cmp(room_list_t *room1, room_list_t *room2)
{
    return (strcmp(room1->room->room_id, room2->room->room_id));
}

/* See npc_move.h */
int move_npc_definite(npc_mov_t *npc_mov)
{

    assert(npc_mov->mov_type == NPC_MOV_DEFINITE);

    room_list_t *test = malloc(sizeof(room_list_t));
    test->next = NULL;
    test->room = room_new(npc_mov->track,"test","test");
    room_list_t *current_room = malloc(sizeof(room_list_t));

    LL_SEARCH(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                current_room,test,room_id_cmp);

    if(current_room->next == NULL)
    {
        return 1;
    }
    if((strcmp(current_room->room->room_id,npc_mov->track)) == 0)
    {
        room_t *next_room = current_room->next->room;
        npc_mov->track = next_room->room_id;
        return 2;
    }
    else
    {
        return 0;
    }
}