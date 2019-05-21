#ifndef _COMMON_ROOM_H
#define _COMMON_ROOM_H

#include "room.h"

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

/* Deletes a hashtable of rooms
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of rooms that need to be deleted
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int delete_all_rooms(room_hash_t rooms);

/* Returns path given hashtable of paths and key
 *
 * Parameters:
 *  hashtable of paths
 *  the key (direction) of hashtable
 * Returns:
 *  the path struct corresponding to the key, or NULL if not found
 */
path_t *path_search(path_hash_t paths, char* direction);

#endif