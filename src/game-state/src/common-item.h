#ifndef _COMMON_ITEM_H
#define _COMMON_ITEM_H

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


#endif