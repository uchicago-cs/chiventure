#ifndef _ROOM_H
#define _ROOM_H

#include "game_state_common.h"
#include "item.h"
#include "npc/npc.h"
#include "npc/rooms-npc.h"

#define ITER_ALL_PATHS(room, curr_path) path_t *ITTMP_PATH; \
HASH_ITER(hh, (room)->paths, (curr_path), ITTMP_PATH)

// PATH STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a path from one room to another.
 * It contains:
 *      string direction of path (case-sensitive)
 *      the room_id of the destination room
 *      list of conditions that must be fulfilled to move to the room
 *      essentially, the list of conditions are the "answers"
 * */
typedef struct path {
    UT_hash_handle hh;
    /* direction (north/south/etc) as key */
    char *direction; // *letter case matters*
    struct room *dest;
    /* conditions that must be met in order to be able to use the path */
    list_action_type_t *conditions;
    /* the door item in the path, which has to be
    open (attribute open is set true) to let through */
    item_t *through;
} path_t;

/* This typedef is to distinguish between path_t pointers which are
* used to point to the path_t structs in the traditional sense,
* and those which are used to hash path_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct path path_hash_t;

// ROOM STRUCT DEFINITION -----------------------------------------------------
/* Forward declarations */
typedef struct npcs_in_room npcs_in_room_t;
typedef struct npc npc_t;

/* This struct represents a single room.
 * It contains:
 *      the room_id
 *      short description
 *      long description
 *      a hashtable of items to be found there
 *      a hashtable of paths accessible from the room. */
typedef struct room {
    /* hh is used for hashtable, as provided in uthash.h */
    UT_hash_handle hh;
    char *room_id;
    char *short_desc;
    char *long_desc;
    item_hash_t *items;
    path_hash_t *paths;
    npcs_in_room_t *npcs;
} room_t;

/* This typedef is to distinguish between room_t pointers which are
* used to point to the room_t structs in the traditional sense,
* and those which are used to hash room_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct room room_hash_t;

typedef struct room_wrapped_for_llist {
    struct room_wrapped_for_llist *next;
    room_t *room;
} room_list_t;

// ROOM FUNCTIONS -------------------------------------------------------------
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

int room_init(room_t *new_room, char *room_id, char *short_desc,
    char *long_desc);

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

/* Removes an item from the given room
 * Note that the memory associated with this item is not freed
 * 
 * Parameters:
 *  room struct
 *  item struct
 * 
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int remove_item_from_room(room_t *room, item_t *item);

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
 *  long description string
 */
char *get_ldesc(room_t *room);

//PATH DEFINITIONS AND HEADER

/* Mallocs space for a new path
 *
 * Parameters:
 *  ptr to the room this path leads to
 *  char* direction (will be path key)
 *
 * Returns:
 *  a pointer to new path
 */
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

/* Adds a list of conditions to the path struct
 * 
 * Parameters:
 *  pointer to the path struct
 *  list of conditions
 *
 * Returns:
 *  SUCCESS if successful
 */
int path_new_conditions(path_t *path, list_action_type_t *act);


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

/*
 * Function to get a linked list (utlist) of all the items in the room
 *
 * Parameters:
 *  room
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */
item_list_t *get_all_items_in_room(room_t *room);

/* 
 * Retrieves the pointer to an npc contained within a room
 * Parameters:
 *   pointer to room
 *   string of npc's id
 *
 * Returns:
 *   pointer to npc, NULL if not found
 */
npc_t *get_npc_in_room(room_t *room, char *npc_id);

/*
 * Removes an action from list of conditions, called when action's completed
 * 
 * Parameters:
 * - path
 * - action_type_t: completed action that acts as condition for path
 *
 * Returns:
 * int SUCCESS when action's removed from linked list
 */
int remove_condition(path_t *path, list_action_type_t *a);

/* Deletes a hashtable of rooms
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  a pointer to the hashtable of rooms that need to be deleted
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int delete_all_rooms(room_hash_t **rooms);

#endif
