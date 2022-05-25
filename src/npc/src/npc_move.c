#include "npc/npc_move.h"

// STRUCT FUNCTIONS -----------------------------------------------------------
/* See npc_move.h */
int npc_mov_init(npc_mov_t *npc_mov, npc_mov_enum_t mov_type, char *room_id)
{
    assert(npc_mov != NULL);
    npc_mov->mov_type = mov_type;
    strncpy(npc_mov->track, room_id, MAX_ID_LEN);
    npc_mov->npc_path_pos = 0;
    npc_mov->npc_path_direction = NPC_MOV_ORIGINAL;

    room_id_dll_t *room_to_add = malloc(sizeof(room_id_dll_t));
    room_to_add->next = NULL;
    room_to_add->prev = NULL;
    room_to_add->room_id = room_id;

    if (mov_type == NPC_MOV_DEFINITE)
    {

        DL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                  room_to_add);
    }
    else if (mov_type == NPC_MOV_INDEFINITE )
    {
        DL_APPEND(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path,
                  room_to_add);
        npc_mov->npc_mov_type.npc_mov_indefinite->room_time = NULL;
    }

    return SUCCESS;
}


/* See npc_move.h */
npc_mov_t *npc_mov_new(npc_mov_enum_t mov_type, char *room_id)
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

    int check = npc_mov_init(npc_mov, mov_type, room_id);

    if (npc_mov == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc_mov;
}


/* See npc_move.h */
int npc_mov_free(npc_mov_t *npc_mov)
{

    assert(npc_mov != NULL);

    if (npc_mov->mov_type == NPC_MOV_DEFINITE)
    {
        free(npc_mov->npc_mov_type.npc_mov_definite);
    }
    else if (npc_mov->mov_type == NPC_MOV_INDEFINITE)
    {
        free(npc_mov->npc_mov_type.npc_mov_indefinite);
    }

    free(npc_mov->track);
    free(npc_mov);

    return SUCCESS;
}


/* See npc_move.h */
int register_npc_room_time(npc_mov_t *npc_mov, char *room_id, int time)
{
    assert(room_id != NULL);

    npc_room_time_t *return_time;

    npc_room_time_t *new_npc_room_time;
    new_npc_room_time = malloc(sizeof(npc_room_time_t));
    memset(new_npc_room_time, 0, sizeof(npc_room_time_t));
    new_npc_room_time->room_id = malloc(MAX_ID_LEN);
    strcpy(new_npc_room_time->room_id, room_id);
    new_npc_room_time->time = time;

    HASH_REPLACE(hh, npc_mov->npc_mov_type.npc_mov_indefinite->room_time,
                 room_id, strlen(room_id),
                 new_npc_room_time, return_time);
    free(return_time);

    HASH_ADD_KEYPTR(hh, npc_mov->npc_mov_type.npc_mov_indefinite->room_time,
                    room_id, strlen(room_id), new_npc_room_time);

    return SUCCESS;
}


/* See npc_move.h */
int extend_path_definite(npc_mov_t *npc_mov, char *room_id_to_add)
{
    assert(room_id_to_add != NULL);
    assert(npc_mov != NULL);

    room_id_dll_t *room_id_to_add2 = malloc(sizeof(room_id_dll_t));
    room_id_to_add2->room_id = room_id_to_add;

    DL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
              room_id_to_add2);

    return SUCCESS;
}


/* See npc_move.h */
int extend_path_indefinite(npc_mov_t *npc_mov, char *room_id_to_add, int time)
{
    assert(room_id_to_add != NULL);

    room_id_dll_t *room_id_to_add2 = malloc(sizeof(room_id_dll_t));
    room_id_to_add2->room_id = room_id_to_add;

    DL_APPEND(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path,
              room_id_to_add2);

    int check = register_npc_room_time(npc_mov, room_id_to_add, time);

    if (check != SUCCESS)
    {
        return FAILURE;
    }
    else
    {
        return SUCCESS;
    }
}


/* See npc_move.h */
char* get_npc_curr_room_id(npc_mov_t *npc_mov)
{
    return npc_mov->track;
}

/* See npc_move.h */
char *get_next_npc_room_id(npc_mov_t *npc_mov)
{
    room_id_dll_t *current_room;

    if (npc_mov->mov_type == NPC_MOV_INDEFINITE)
    {
        current_room = npc_mov->npc_mov_type.npc_mov_indefinite->npc_path;
    }
    else
    {
        current_room = npc_mov->npc_mov_type.npc_mov_definite->npc_path;
    }

    npc_path_direction_t direction = npc_mov->npc_path_direction;
    unsigned int path_pos = npc_mov->npc_path_pos;

    if (path_pos != 0)
    {
        for (int i = 0; i < path_pos; i++)
        {
            current_room = current_room->next;
        }
    }
    else
    {
        if ((direction == NPC_MOV_ORIGINAL) && (current_room->next != NULL))
        {
            return current_room->next->room_id;
        }
        else
        {
            return NULL;
        }
    }

    if (direction == NPC_MOV_ORIGINAL)
    {
        if (current_room->next == NULL)
        {
            return NULL;
        }
        else
        {
            return current_room->next->room_id;
        }
    }
    else
    {
        return current_room->prev->room_id;
    }
}

/* See npc_move.h */
unsigned int get_npc_path_pos(npc_mov_t *npc_mov)
{
    return npc_mov->npc_path_pos;
}

/* See npc_move.h */
unsigned int get_npc_path_direction(npc_mov_t *npc_mov)
{
    return npc_mov->npc_path_direction;
}

/* See npc_move.h */
int flip_npc_path_direction(npc_mov_t *npc_mov)
{
    if (npc_mov->npc_path_direction == NPC_MOV_ORIGINAL)
    {
        npc_mov->npc_path_direction = NPC_MOV_REVERSED;
    }
    else if (npc_mov->npc_path_direction == NPC_MOV_REVERSED)
    {
        npc_mov->npc_path_direction = NPC_MOV_ORIGINAL;
    }
    else
    {
        return FAILURE;
    }

    return SUCCESS;
}

/* See npc_move.h */
int get_npc_num_rooms(npc_mov_t *npc_mov)
{
    room_id_dll_t *elt;
    int count = 0;

    if (npc_mov->mov_type == NPC_MOV_DEFINITE)
    {
        DL_COUNT(npc_mov->npc_mov_type.npc_mov_definite->npc_path, elt, count);
    }
    else if (npc_mov->mov_type == NPC_MOV_INDEFINITE)
    {
        DL_COUNT(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path, elt, count);
    }
    return count;
}

/* See npc_move.h */
int room_id_cmp(room_id_dll_t *room1, room_id_dll_t *room2)
{
    return strcmp(room1->room_id, room2->room_id);
}

/* See npc_move.h */
int move_npc_definite(npc_mov_t *npc_mov)
{
    assert(npc_mov->mov_type == NPC_MOV_DEFINITE);

    room_id_dll_t *current_room;
    current_room = npc_mov->npc_mov_type.npc_mov_definite->npc_path;
    npc_path_direction_t direction = npc_mov->npc_path_direction;
    unsigned int path_pos = npc_mov->npc_path_pos;

    if ((current_room->next == NULL) && (current_room->prev == NULL))
        return 3; // NPC has nowhere to move

    if (path_pos != 0)
    {
        for (int i = 0; i < path_pos; i++)
        {
            current_room = current_room->next;
        }
    }

    if(((direction == NPC_MOV_ORIGINAL) && (current_room->next == NULL))
            || ((direction == NPC_MOV_REVERSED) && (current_room->prev == NULL)))
    {
        return 1;
    }

    if((strcmp(current_room->room_id, npc_mov->track)) == 0)
    {
        if (direction == NPC_MOV_ORIGINAL)
        {
            npc_mov->track = current_room->next->room_id;
            npc_mov->npc_path_pos++;
        }
        else if (direction == NPC_MOV_REVERSED)
        {
            npc_mov->track = current_room->prev->room_id;
            npc_mov->npc_path_pos--;
        }
        else
        {
            return 0;
        }

        return 2;
    }
    else
    {
        return 0;
    }
}

/* See npc_move.h */
int move_npc_indefinite(npc_mov_t *npc_mov)
{
    assert(npc_mov->mov_type == NPC_MOV_INDEFINITE);

    room_id_dll_t *current_room;
    current_room = npc_mov->npc_mov_type.npc_mov_indefinite->npc_path;
    npc_path_direction_t direction = npc_mov->npc_path_direction;
    unsigned int path_pos = npc_mov->npc_path_pos;

    if ((current_room->next == NULL) && (current_room->prev == NULL))
        return 3; // NPC has nowhere to move

    if (path_pos != 0)
    {
        for (int i = 0; i < path_pos; i++)
        {
            current_room = current_room->next;
        }
    }

    if(((direction == NPC_MOV_ORIGINAL) && (current_room->next == NULL))
            || ((direction == NPC_MOV_REVERSED) && (current_room->prev == NULL)))
    {
        assert(flip_npc_path_direction(npc_mov) == SUCCESS);
        return 1;
    }
    if((strcmp(current_room->room_id, npc_mov->track)) == 0)
    {
        if (direction == NPC_MOV_ORIGINAL)
        {
            npc_mov->track = current_room->next->room_id;
            npc_mov->npc_path_pos++;
        }
        else if (direction == NPC_MOV_REVERSED)
        {
            npc_mov->track = current_room->prev->room_id;
            npc_mov->npc_path_pos--;
        }
        else
        {
            return 0;
        }

        return 2;
    }
    else
    {
        return 0;
    }
}

/* See npc_move.h */
int move_npc_mov(npc_mov_t *npc_mov)
{
    npc_mov_enum_t mov_type = npc_mov->mov_type;

    if (mov_type == NPC_MOV_DEFINITE)
    {
        return move_npc_definite(npc_mov);
    }
    else if (mov_type == NPC_MOV_INDEFINITE)
    {
        return move_npc_indefinite(npc_mov);
    }
    else
    {
        return 0;
    }
}

/* See npc_move.h */
int delete_room_id_dll(room_id_dll_t *head)
{
    room_id_dll_t *elt, *tmp;
    DL_FOREACH_SAFE(head, elt, tmp)
    {
        DL_DELETE(head, elt);
        free(elt);
    }
    return SUCCESS;
}
