#include <math.h>

#include "common/uthash.h"
#include "npc/npc_move.h"

// STRUCT FUNCTIONS -----------------------------------------------------------
/* Initializes time_ray_t struct
 * Parameters
 *  - time_ray: pointer to malloc'd time_ray_t
 *  - assigned_time: the number of seconds the phenomenon is supposed to occur
 *
 * Returns
 *  - SUCCESS: if successful
 *  - FAILURE: if unsuccessful
 */
int time_ray_init(time_ray_t *time_ray, double assigned_time)
{
<<<<<<< HEAD
    if (time_ray == NULL)
    {
        return FAILURE;
    }
    time_t start;
    time_ray->start = time(&start);
    time_ray->assigned_time = assigned_time;
    return SUCCESS;
}
=======
    char *room_id  = room->room_id;
    assert(npc_mov != NULL);
    npc_mov->mov_type = mov_type;
    strncpy(npc_mov->track,room_id, MAX_ID_LEN);
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock

/* Creates and allocates a new time_ray_t struct
 * Parameters
 *  - assigned_time: the number of seconds the phenomenon is supposed to occur
 *
 * Returns
 *  - pointer to the time_ray_t
 */
time_ray_t *time_ray_new(double assigned_time)
{
    time_ray_t *time_ray;
    time_ray = malloc(sizeof(time_ray_t));
    memset(time_ray, 0, sizeof(time_ray_t));
    assert(time_ray_init(time_ray, assigned_time) == SUCCESS);
    return time_ray;
}

/* Frees a time_ray_t struct
 * Parameters
 *  - time_ray: pointer to a time_ray_t struct
 *
 * Returns:
 *  - SUCCESS: if successful
 *  - FAILURE: if unsuccessful
 */
int time_ray_free(time_ray_t *time_ray)
{
    if (time_ray != NULL)
    {
        free(time_ray);
    }
    return SUCCESS;
}

/* Initializes npc_path_dll_t struct
 * Parameters
 *  - head: pointer to the npc_path_dll being initialized
 *  - mov_type: NPC_MOV_DEFINITE or NPC_MOV_INDEFINITE
 *  - room_id: room id of the room being represented in this step of the path
 *  - room_time: the number of seconds the npc should spend in the room
 *
 * Returns
 *  - SUCCESS: if successful
 *  - FAILURE: if unsuccessful
 */
int npc_path_dll_init(npc_path_dll_t *head, npc_mov_enum_t mov_type,
                      char *room_id, double room_time)
{
    if (head == NULL)
    {
        return FAILURE;
    }
    strcpy(head->room_id, room_id);
    if (mov_type == NPC_MOV_INDEFINITE)
    {
        head->room_time = time_ray_new(room_time);
    }
    else if (mov_type == NPC_MOV_DEFINITE)
    {
<<<<<<< HEAD
        head->room_time = NULL;
=======
        LL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
        room_to_add);
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
    }
    else
    {
<<<<<<< HEAD
        return FAILURE;
=======
        LL_APPEND(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path
        ,room_to_add);
        npc_mov->npc_mov_type.npc_mov_indefinite->room_time = NULL;
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
    }
    head->prev = NULL;
    head->next = NULL;

    return SUCCESS;
}

/* Creates and allocates a new npc_path_dll_t struct
 * Parameters
 *  - mov_type: NPC_MOV_DEFINITE or NPC_MOV_INDEFINITE
 *  - room_id: room id of the room being represented in this step of the path
 *  - room_time: the number of seconds the npc should spend in the room
 *
 * Returns
 *  - pointer to the npc_path_dll_t struct
 */
npc_path_dll_t *npc_path_dll_new(npc_mov_enum_t mov_type, char *room_id,
                                 double room_time)
{
    npc_path_dll_t *path = NULL;
    path = malloc(sizeof(npc_path_dll_t));
    memset(path, 0, sizeof(npc_path_dll_t));
    path->room_id = malloc(MAX_ID_LEN);
    assert(npc_path_dll_init(path, mov_type, room_id, room_time) == SUCCESS);
    return path;
}

/* Frees a (doubly-linked) list of npc_path_dll_t's
 * Parameters
 *  - head: pointer to the head of the list of npc_path_dll_t being freed
 *
 * Returns:
 *  - SUCCESS: if successful
 *  - FAILURE: if unsuccessful
 */
int npc_path_dll_free(npc_path_dll_t *head)
{
    npc_path_dll_t *tmp;
    while (head != NULL)
    {
        tmp = head->next;
        free(head->room_id);
        assert(time_ray_free(head->room_time) == SUCCESS);
        free(head);
        head = tmp;
    }
    return SUCCESS;
}

/* See npc_move.h */
int npc_mov_init(npc_mov_t *npc_mov, npc_mov_enum_t mov_type, char *room_id,
                 double room_time)
{
    assert(npc_mov != NULL);
    npc_mov->mov_type = mov_type;
    strcpy(npc_mov->track, room_id);
    npc_mov->npc_path_pos = 0;
    npc_mov->npc_path_direction = NPC_MOV_ORIGINAL;
    
    /* These next four (4) lines correctly initialize a utlish doubly-linked
     * list. Initializing the head of the list to NULL is essential, and then
     * the next step is appending the first real "element" of the list to the
     * NULL-initialized head.
     */
    npc_path_dll_t *head = NULL;
    npc_path_dll_t *elt = npc_path_dll_new(mov_type, room_id, room_time);
    DL_APPEND(head, elt);
    npc_mov->path = head;
    
    return SUCCESS;
}


/* See npc_move.h */
npc_mov_t *npc_mov_new(npc_mov_enum_t mov_type, char *room_id, double room_time)
{
    npc_mov_t *npc_mov;
    npc_mov = malloc(sizeof(npc_mov_t));
    memset(npc_mov, 0, sizeof(npc_mov_t));
    npc_mov->track = malloc(MAX_ID_LEN);

    int check = npc_mov_init(npc_mov, mov_type, room_id, room_time);

    if (npc_mov == NULL || check != SUCCESS)
    {
        return NULL;
    }

    return npc_mov;
}

/* See npc_move.h */
<<<<<<< HEAD
int npc_mov_free(npc_mov_t *npc_mov)
{
    assert(npc_mov != NULL);
    npc_path_dll_free(npc_mov->path);
=======
int npc_mov_free(npc_mov_t *npc_mov) {

    assert(npc_mov != NULL);

    if (npc_mov->mov_type == NPC_MOV_DEFINITE) {
        free(npc_mov->npc_mov_type.npc_mov_definite);
    } else if (npc_mov->mov_type == NPC_MOV_INDEFINITE) {
        free(npc_mov->npc_mov_type.npc_mov_indefinite);
    }

>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
    free(npc_mov->track);
    free(npc_mov);
    return SUCCESS;
}

// FUNCTIONS TO EXTEND PATHS --------------------------------------------------
/* See npc_move.h */
int extend_path_definite(npc_mov_t *npc_mov, char *room_id)
{
<<<<<<< HEAD
    assert(room_id != NULL);
    assert(npc_mov != NULL);

    npc_path_dll_t *new = npc_path_dll_new(NPC_MOV_DEFINITE, room_id, 0);
    DL_APPEND(npc_mov->path, new);
=======
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
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock

    return SUCCESS;
}


/* See npc_move.h */
int extend_path_indefinite(npc_mov_t *npc_mov, char *room_id, double room_time)
{
    assert(room_id != NULL);

<<<<<<< HEAD
    npc_path_dll_t *new;
    new = npc_path_dll_new(NPC_MOV_INDEFINITE, room_id, room_time);
    DL_APPEND(npc_mov->path, new);
=======
    LL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
            room_to_add2);
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock

    return SUCCESS;
}

// "GET" FUNCTIONS ------------------------------------------------------------
/* See npc_move.h */
npc_path_dll_t *get_npc_curr_path_step(npc_mov_t *npc_mov)
{
<<<<<<< HEAD
    npc_path_dll_t *curr = npc_mov->path;
    unsigned int pos = npc_mov->npc_path_pos;
    if (pos != 0)
    {
        for (int i = 0; i < pos; i++)
        {
            curr = curr->next;
        }
    }
    return curr;
=======
    assert(room_to_add != NULL);

    room_list_t *room_to_add2 = malloc(sizeof(room_list_t));
    room_to_add2->next = NULL;
    room_to_add2->room = room_to_add;

    LL_APPEND(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path,
         room_to_add2);

    int check = register_npc_room_time(npc_mov, room_to_add, time);

    if (check != SUCCESS)
        return FAILURE;
    else
        return SUCCESS;
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
}

/* See npc_move.h */
char* track_room(npc_mov_t *npc_mov)
{
    return npc_mov->track;
}

/* See npc_move.h */
char *get_next_npc_room_id(npc_mov_t *npc_mov)
{
    npc_path_dll_t *current_room = get_npc_curr_path_step(npc_mov);
    npc_path_direction_t direction = npc_mov->npc_path_direction;
    unsigned int path_pos = npc_mov->npc_path_pos;

    if (direction == NPC_MOV_ORIGINAL)
    {
        if (current_room->next != NULL)
        {
            return current_room->next->room_id;
        }
        else
        {
            return current_room->room_id;
        }
    }
    else
    {
        if (current_room->prev != NULL)
        {
            return current_room->prev->room_id;
        }
        else
        {
            return current_room->room_id;
        }
    }
}

/* See npc_move.h */
int reverse_path(npc_mov_t *npc_mov)
{
    assert(npc_mov->mov_type == NPC_MOV_DEFINITE);

    room_list_t *reversed_path_head = NULL;

<<<<<<< HEAD
/* See npc_move.h */
int get_npc_num_rooms(npc_mov_t *npc_mov)
{
    npc_path_dll_t *elt;
    int count = 0;
    DL_COUNT(npc_mov->path, elt, count);
    return count;
}

// "SET" FUNCTIONS ------------------------------------------------------------
/* See npc_move.h */
int reset_indefinite_npc_room_start_time(npc_mov_t *npc_mov)
{
    if (npc_mov->mov_type == NPC_MOV_DEFINITE)
    {
        return FAILURE;
    }
    npc_path_dll_t *curr = npc_mov->path;
    curr = get_npc_curr_path_step(npc_mov);
    assert(time_ray_init(curr->room_time, curr->room_time->assigned_time) == SUCCESS);
=======
    room_list_t *room_elt, *room_tmp;
    LL_FOREACH_SAFE(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                room_elt,room_tmp)
    {
        room_list_t *append_room = malloc(sizeof(room_list_t));
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
        room_list_t *reappend_room = malloc(sizeof(room_list_t));
        reappend_room->next = NULL;
        reappend_room->room = tmp2->room;
        LL_APPEND(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                reappend_room);
    }

>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
    return SUCCESS;
}

// COMPARISON FUNCTIONS -------------------------------------------------------
/* See npc_move.h */
int room_id_cmp(npc_path_dll_t *room1, npc_path_dll_t *room2)
{
<<<<<<< HEAD
    return strcmp(room1->room_id, room2->room_id);
=======
	room_t *curr_room;
  room_list_t *elt;

	int count = 0;

	if(npc_mov->mov_type == NPC_MOV_DEFINITE)
	{
        LL_FOREACH(npc_mov->npc_mov_type.npc_mov_definite->npc_path, elt)
        {
            count++;
            curr_room = elt->room;
        }
	}
	else if(npc_mov->mov_type == NPC_MOV_INDEFINITE)
	{
        LL_FOREACH(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path, elt)
        {
            count++;
            curr_room = elt->room;
        }
	}

	return count;
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
}

// CHECKING FUNCTIONS ---------------------------------------------------------
/* Helper Function for check_if_npc_mov_indefinite_needs_moved()
 * Just returns the number of seconds an NPC has overstayed their current
 * location, with negative values indicating they still have time left
 */
double seconds_past_room_time(time_ray_t *time_ray)
{
    time_t curr;
    return (difftime(time(&curr), time_ray->start) - time_ray->assigned_time);
}

/* See npc_move.h */
bool check_if_npc_mov_indefinite_needs_moved(npc_mov_t *npc_mov)
{
<<<<<<< HEAD
    assert(npc_mov->mov_type == NPC_MOV_INDEFINITE);
    npc_path_dll_t *curr_room = get_npc_curr_path_step(npc_mov);
    if (seconds_past_room_time(curr_room->room_time) >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
=======
    assert(npc_mov->mov_type == NPC_MOV_DEFINITE);

    room_list_t *test = malloc(sizeof(room_list_t));
    test->next = NULL;
    test->room = room_new(npc_mov->track,"test","test");
    room_list_t *current_room = malloc(sizeof(room_list_t));

    LL_SEARCH(npc_mov->npc_mov_type.npc_mov_definite->npc_path,
                current_room,test,room_id_cmp);
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock

// DO SOMETHING FUNCTIONS -----------------------------------------------------
/* See npc_move.h */
int flip_npc_path_direction(npc_mov_t *npc_mov)
{
    if (npc_mov->npc_path_direction == NPC_MOV_ORIGINAL)
    {
        npc_mov->npc_path_direction = NPC_MOV_REVERSED;
    }
    else if (npc_mov->npc_path_direction == NPC_MOV_REVERSED)
    {
<<<<<<< HEAD
        npc_mov->npc_path_direction = NPC_MOV_ORIGINAL;
=======
        room_t *next_room = current_room->next->room;
        npc_mov->track = next_room->room_id;
        return 2;
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
    }
    else
    {
        return FAILURE;
    }

    return SUCCESS;
}

/* See npc_move.h */
int move_npc_mov(npc_mov_t *npc_mov)
{
<<<<<<< HEAD
    npc_path_dll_t *current_room = npc_mov->path;
    current_room = get_npc_curr_path_step(npc_mov);
    npc_path_direction_t direction = npc_mov->npc_path_direction;
    npc_mov_enum_t mov_type = npc_mov->mov_type;
    unsigned int pos = npc_mov->npc_path_pos;
    int num_steps = get_npc_num_rooms(npc_mov);
    assert(strcmp(current_room->room_id, npc_mov->track) == 0);

    if (num_steps == 1)
    {
        if (mov_type == NPC_MOV_INDEFINITE)
        {
            assert(reset_indefinite_npc_room_start_time(npc_mov) == SUCCESS);
        }
        return FAILURE; // NPC has nowhere to move
    }
=======

    assert(npc_mov->mov_type == NPC_MOV_INDEFINITE);

    room_list_t *test = malloc(sizeof(room_list_t));
    test->next = NULL;
    test->room = room_new(npc_mov->track,"test","test");
    room_list_t *current_room = malloc(sizeof(room_list_t));

    LL_SEARCH(npc_mov->npc_mov_type.npc_mov_indefinite->npc_path,
                current_room,test,room_id_cmp);
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock

    if (((direction == NPC_MOV_REVERSED) && (pos == 0))
            || ((direction == NPC_MOV_ORIGINAL) && (pos == (num_steps - 1))))
    {
<<<<<<< HEAD
        if (mov_type == NPC_MOV_INDEFINITE)
        {
            assert(flip_npc_path_direction(npc_mov) == SUCCESS);
            assert(reset_indefinite_npc_room_start_time(npc_mov) == SUCCESS);
            return SUCCESS;
        }
        else
        {
            return FAILURE;
        }
=======
        return 1;
    }
    if((strcmp(current_room->room->room_id,npc_mov->track)) == 0)
    {
        room_t *next_room = current_room->next->room;
        npc_mov->track = next_room->room_id;
        return 2;
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
    }

    if (direction == NPC_MOV_ORIGINAL)
    {
        npc_mov->track = current_room->next->room_id;
        npc_mov->npc_path_pos += 1;
    }
    else if (direction == NPC_MOV_REVERSED)
    {
        npc_mov->track = current_room->prev->room_id;
        npc_mov->npc_path_pos -= 1;
    }
<<<<<<< HEAD
    else
    {
        return FAILURE;
    }

    if (mov_type == NPC_MOV_INDEFINITE)
    {
        assert(reset_indefinite_npc_room_start_time(npc_mov) == SUCCESS);
=======
    return count;
}

/* See npc_move.h */
int auto_gen_movement(npc_mov_t *npc_mov, game_t *game)
{
    room_list_t *head = get_all_rooms(game); // from include/game-state/game.h
    int rc = 0;
    int num_rooms, num_rooms_to_add;

	if(npc_mov == NULL || head == NULL) {
		return FAILURE;
	}

    num_rooms = get_num_rooms(game);
    num_rooms_to_add = (rand() % num_rooms) + 1;

    for (int i = 0; i < num_rooms_to_add; i++) {
        room_t *room_to_add = malloc(sizeof(room_t));

        room_to_add = head->room;
        head->room = head->next->room;
        if(npc_mov->mov_type == NPC_MOV_DEFINITE) {
        	rc = extend_path_definite(npc_mov, room_to_add);
        }
        else if(npc_mov->mov_type == NPC_MOV_INDEFINITE) {
            int mintime_in_room = 30000; // min time in room in ms, 30000 ms = 30 s
            int maxtime_in_room = 90000; // max time in room in ms, 90000 ms = 90 s
            int time_in_room = (rand() % (maxtime_in_room - mintime_in_room + 1)) + mintime_in_room;
            rc = extend_path_indefinite(npc_mov, room_to_add, time_in_room);
	      }

        if(rc == FAILURE) {
          return rc;
        }
>>>>>>> parent of 811528446... Merge branch 'dev' into time/1353-designing-and-implementing-a-time-module-for-in-game-clock
    }

    return SUCCESS;
}
