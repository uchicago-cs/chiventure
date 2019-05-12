#ifndef _ROOM_H
#define _ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utlist.h"
#include "uthash.h"
#include "item.h"

/* Forward declaration of linked list */
typedef struct exit {
    /* fields used for linked list */
    struct exit *next, *prev;

    /* add necessary exit/door info here */

} exit_t;

/* This struct represents a single room, which includes a
 * short and long description of the room, a list of objects to be
 * found there, and a list of doors accessible from the room.
 * Each exit will be an object (door) struct that connects to another room
 * and has a locked/unlocked quality.
 */

typedef struct coord {
    int x;
    int y;
} coord_t;

typedef struct room {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;

    int room_id;
    coord_t coord;
    char *short_desc;
    char *long_desc;
    /* a hashtable of all items in the room */
    all_items_t items;
    /* an adjacency list (using linked list) of adjacent rooms */
    exit_t *exits;
} room_t;

typedef struct room* all_rooms_t;

/* Mallocs space for a new room
 *
 * Parameters:
 *  short string description
 *  long string description
 *  linked list of items in room
 *  linked list of exits accessible from room
 *
 * Returns:
 *  a pointer to new room
 */
room_t *room_new(char *short_desc, char *long_desc, all_objects_t *items, exit_t *exits);

/* Frees the space in memory taken by given room
 *
 * Parameters:
 *  pointer to the room struct to be freed
 *
 * Returns:
 *  1 if successful, 0 if failed
 */
int free_room(room_t *room);


/* Adds a room to the given hashtable of rooms
 *
 * Parameters:
 *  hashtable the room is added to
 *  room id
 *  pointer to the room
 * Returns:
 *  1 if successful, 0 if failed
 */
int add_room_to_hash(all_rooms_t all_rooms, int room_id, room_t *room);

/* Deletes a hashtable of rooms
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of rooms that need to be deleted
 * Returns:
 *  1 if successful, 0 if failed
 */
int delete_all_rooms(all_rooms_t rooms);


#endif
