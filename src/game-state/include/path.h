#ifndef _PATH_H
#define _PATH_H

#include "game_state_common.h"
#include "item.h"

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
    /* we use path_id here to avoid bugs when using uthash functions */
    char *path_id; // ***** MEANS ROOM_ID *****
    condition_t *conditions_list;
} path_t;

typedef struct path* path_hash_t;

/* Deletes the linked list of conditions completely
 *
 * Parameters:
 *  the linked list of conditions that need to be deleted
 *
 * Returns:
 *  1 if successful, 0 if failed
 */
int delete_all_conditions(condition_t *conditions_list);

/* Mallocs space for a new path
 *
 * Parameters:
 *  id of the room this path leads to
 *
 * Returns:
 *  a pointer to new path
 */
path_t *path_new(char *room_id);

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
int add_path_to_hash(path_hash_t all_paths, char* path_id, path_t *path);

/* Deletes a hashtable of paths
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of paths that need to be deleted
 * Returns:
 *  1 if successful, 0 if failed
 */
int delete_all_paths(path_hash_t paths);

#endif
