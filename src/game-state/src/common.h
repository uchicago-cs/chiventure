#ifndef _COMMON_H
#define _COMMON_H

#include "room.h"
#include "item.h"

/* add_item_to_hash() adds an item to the hash table of items
 * Parameters:
 *  a unique item id
 *  a pointer to the item
 *  the hash table of items
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 */
int add_item_to_hash(item_hash_t item_hash, char *item_id, item_t *item);

/* this has to be in the interface as room and player modules use this */
/* delete_all_items() deletes and frees all items in a hash table
 * Parameters:
 *  hash table of items
 * Returns:
 *  SUCCESS if successful
 */
int delete_all_items(item_hash_t items);

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