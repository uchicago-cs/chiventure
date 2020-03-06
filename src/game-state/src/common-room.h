#ifndef _COMMON_ROOM_H
#define _COMMON_ROOM_H

#include "game-state/room.h"

/* Deletes a hashtable of rooms
 * Implemented with macros provided by uthash.h
 *
 * Parameters:
 *  hashtable of rooms that need to be deleted
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int delete_all_rooms(room_hash_t* rooms);


#endif