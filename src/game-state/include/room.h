#ifndef _ROOM_H
#define _ROOM_H

#include "game_state_common.h"
#include "item.h"

#define ITER_ALL_PATHS(room, curr_path) path_t *ITTMP_PATH; HASH_ITER(hh, (room)->paths, (curr_path), ITTMP_PATH)
//#define ITER_ALL_CONDITIONS(path, curr_condi) condition *ITTMP_CONDI; LL_FOREACH_SAFE((path)->conditions, curr_condi, ITTMP_CONDI)

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

typedef struct condition *condition_list_t;

/* This struct represents a path from one room to another. It contains
 * the room_ID string of the room it leads to as well as a linked
 * list of conditions that must be fulfilled to move to the room.
 * essentially, the list of conditions are the "answers"
 * */
typedef struct path {
    UT_hash_handle hh;
    /* direction (north/south/etc) as key */
    char *direction; // *capitalization matters*
    struct room *dest;
    condition_list_t conditions;
} path_t;

typedef struct path* path_hash_t;

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
    item_hash_t items;
    /* a hashtable of all paths from the room */
    path_hash_t paths;
} room_t;

typedef struct room* room_hash_t;


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
room_t *room_new(char *room_id, char *short_desc, char *long_desc);

/* room_init() initializes a room struct with given values
  Parameters:
    a memory allocated new room pointer
    a unique room id
    a short description of the room
    a long description of the room

  Returns:
    FAILURE for failure, SUCCESS for success
*/

int room_init(room_t *new_room, char *room_id, char *short_desc, char *long_desc);

/* Frees the space in memory taken by given room
 *
 * Parameters:
 *  pointer to the room struct to be freed
 *
 * Returns:
 *  Always returns SUCCESS
 */

int room_free(room_t *room);

/* Adds an item to the given room
 *
 * Parameters:
 *  room struct
 *  item struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_item_to_room(room_t *room, item_t *item);

/* Adds a path to the given room
 *
 * Parameters:
 *  room struct
 *  path struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_path_to_room(room_t *room, path_t *path);

/* Get short description of room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  short description string
 */
char *get_sdesc(room_t *room);

/* Get long description of room
 *
 * Parameters:
 *  pointer to room
 *
 * Returns:
 *  short description string
 */
char *get_ldesc(room_t *room);

//PATH DEFINITIONS AND HEADER

/* Deletes the linked list of conditions completely
 *
 * Parameters:
 *  the linked list of conditions that need to be deleted
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int delete_all_conditions(condition_list_t conditions);

/* delete_all_paths() deletes all paths in a path hash
* Parameters:
*  the hash table of paths that needs to be deleted
*
* Returns:
*  SUCCESS if successful, FAILURE if failed
*/
int delete_all_paths(path_hash_t paths);

/* Mallocs space for a new path
 *
 * Parameters:
 *  ptr to the room this path leads to
 *  char* direction (will be path key)
 *
 * Returns:
 *  a pointer to new path
 */
// path_t *path_new(room_t *destination, char* direction);
path_t *path_new(room_t *dest, char *direction);

/* Frees the space in memory taken by given path
 *
 * Parameters:
 *  pointer to the path struct to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int path_free(path_t *path);

/* Adds a condition to the given path
 *
 * Parameters:
 *  path struct
 *  condition struct
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_condition_to_path(path_t *path, condition_t *condition);

/* Returns path given room and direction
 *
 * Parameters:
 * ptr to room, char* direction
 *
 * Returns:
 *  the path struct corresponding to the key, or NULL if not found
 */
path_t *path_search(room_t *room, char* direction);

/* Returns pointer to room given path
* Parameters:
* ptr to path
*
* Returns:
* ptr to room or NULL if not found
*/
room_t *find_room_from_path(path_t *path);

/* Returns ptr to adjacent room given direction
* Parameters:
* ptr to room, char* direction (must follow initialized direction characters)
*
* Returns:
* ptr to room or NULL if not found
*/
room_t *find_room_from_dir(room_t *curr, char* direction);

/* Retrieves the pointer to an item contained within a room
* Parameters:
*   pointer to room
*   string of item's id
*
* Returns:
*   pointer to item, NULL if not found
*/
item_t* get_item_in_room(room_t* room, char* item_id);

#endif
