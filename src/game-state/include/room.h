#ifndef _ROOM_H
#define _ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include "utlist.h"
#include "uthash.h"
#include "object.h"

/* Forward declaration of linked list */
typedef struct llist llist_t;

/* This struct represents a single room, which includes a                                                                                                                                                   * short and long description of the room, a list of objects                                                                                                                                                * to be found there, and a list of doors accessible from the room.                                                                                                                                         * Each exit will be an object (door) struct that connects to another room                                                                                                                                  * and has a locked/unlocked quality.                                                                                                                                                                       */
typedef struct room {
    /* hh is used for hashtable, as provided in uthash.h*/
    UT_hash_handle hh;

    int room_id;
    char *short_desc;
    char *long_desc;
    llist_t *items;
    llist_t *exits;
} room_t;

/* Mallocs space for a new room                                                                                                                                                                             *                                                                                                                                                                                                          * Parameters:                                                                                                                                                                                              *  short string description                                                                                                                                                                                *  long string description                                                                                                                                                                                 *  linked list of items in room                                                                                                                                                                            *  linked list of exits accessible from room                                                                                                                                                               *                                                                                                                                                                                                          * Returns:                                                                                                                                                                                                 *  a pointer to new room                                                                                                                                                                                   */
room_t *room_new(char *short_desc, char *long_desc, llist_t *items, llist_t *exits);

/* Frees the space in memory taken by given room                                                                                                                                                            *                                                                                                                                                                                                          * Parameters:                                                                                                                                                                                              *  pointer to the room struct to be freed                                                                                                                                                                  *                                                                                                                                                                                                          * Returns:                                                                                                                                                                                                 *  1 if success, 0 if error                                                                                                                                                                                */
int free_room(room_t *room);

#endif
