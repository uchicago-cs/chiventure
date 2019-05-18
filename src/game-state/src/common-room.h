#ifndef _ROOM_COMMON_H
#define _ROOM_COMMON_H

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

#endif