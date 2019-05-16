#ifndef _ROOM_H
#define _ROOM_H

#include "game_state_common.h"
#include "item.h"
#include "path.h"

#define ITER_ALL_ROOMS(game, curr_room) room_t *ITTMP_ROOM; HASH_ITER(hh, (game)->all_rooms, (curr_room), ITTMP_ROOM)

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
room_t *room_new(char *room_id, char *short_desc, char *long_desc, item_hash_t items, path_hash_t paths);

/* Frees the space in memory taken by given room
 *
 * Parameters:
 *  pointer to the room struct to be freed
 *
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int room_free(room_t *room);

/* Adds a room to the given hashtable of rooms
 *
 * Parameters:
 *  hashtable the room is added to
 *  room id
 *  pointer to the room
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_room_to_hash(room_hash_t all_rooms, char *room_id, room_t *room);

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

/* Deletes a hashtable of rooms
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of rooms that need to be deleted
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int delete_all_rooms(room_hash_t rooms);


#endif
