#ifndef _ROOM_H
#define _ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utlist.h"
#include "uthash.h"
#include "item.h"

//typedef struct condition_t {
//    /* fields used for linked list of condition_t */
//    condition_t cond;
//    struct condition_t *next;
//} condition_llist_t;

/* This struct represents a single condition that must be
 * met for a path to be taken. It includes an item, an
 * attribute of the item, and the value of that attribute
 * which can be a string or integer, as defined in item.h */
typedef struct condition {
    /* fields used for linked list of condition_t */
    struct condition *next;

    item_t *item;
    char *attribute;
    attribute_value_t value;
} condition_t;

/* This struct represents a path from one room to another. It contains
 * the room_ID string of the room it leads to as well as a linked
 * list of conditions that must be fulfilled to move to the room. */
typedef struct path {
    UT_hash_handle hh;
    /* path_id means the room_id this path goes to */
    /* for hashtable consistency (e.g. player hash uses player_id), */
    /* we use path_id here in order to use uthash functions more easily */
    char *path_id;
    condition_llist_t *conditions;
} path_t;

typedef struct path* all_paths_t;

/* This struct represents a single room, which includes a
 * short and long description of the room, a hashtable of items to be
 * found there, and a hashtable of paths accessible from the room. */
typedef struct room {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;

    char *room_id;
    char *short_desc;
    char *long_desc;
    /* a hashtable of all items in the room */
    all_items_t items;
    /* a hashtable of all paths from the room */
    all_paths_t paths;
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
room_t *room_new(char *short_desc, char *long_desc, all_items_t *items, exit_t *exits);

/* Frees the space in memory taken by given room
 *
 * Parameters:
 *  pointer to the room struct to be freed
 *
 * Returns:
 *  1 if successful, 0 if failed
 */
int room_free(room_t *room);

/* Adds a room to the given hashtable of rooms
 *
 * Parameters:
 *  hashtable the room is added to
 *  room id
 *  pointer to the room
 * Returns:
 *  1 if successful, 0 if failed
 */
int add_room_to_hash(all_rooms_t all_rooms, char *room_id, room_t *room);

/* Deletes a hashtable of rooms
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of rooms that need to be deleted
 * Returns:
 *  1 if successful, 0 if failed
 */
int delete_all_rooms(all_rooms_t rooms);

/* Mallocs space for a new path
 *
 * Parameters:
 *  id of the room this path leads to
 *  linked list of conditions
 *
 * Returns:
 *  a pointer to new path
 */
path_t *path_new(char *room_id, condition_llist_t conditions);

/* Frees the space in memory taken by given path
 *
 * Parameters:
 *  pointer to the path struct to be freed
 *
 * Returns:
 *  1 if successful, 0 if failed
 */
int path_free(path_t *path);

/* Adds a path to the given hashtable of paths
 *
 * Parameters:
 *  hashtable the path is added to
 *  path id
 *  pointer to the path
 * Returns:
 *  1 if successful, 0 if failed
 */
int add_path_to_hash(all_paths_t all_paths, char* path_id, path_t *path);

/* Deletes a hashtable of paths
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of paths that need to be deleted
 * Returns:
 *  1 if successful, 0 if failed
 */
int delete_all_paths(all_paths_t paths);


#endif
