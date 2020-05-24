#ifndef _DEFAULT_ITEM_H
#define _DEFAULT_ITEM_H

#include "../game-state/game_state_common.h"
#include "../game-state/item.h"
#include "../../../include/common/uthash.h"
#include "default_items.h"

/*get_default_items() returns all the default defined
* items in a hash table.
*/
item_hash_t *get_default_items();

/* make_default_items returns the subset of defined default items
* that are allowed for a given room name. If the room name doesn't
* have any default approved items, return the original item list.
* However, if the room name does have approved items, then add
* these additional items to whatever is in llist. If llist is NULL,
* then you'll return only the list of approved items. If for some reason
* you want to add additional items to the allowed items list, then you
* would pass these in through llist.
*
* Input:
*	- char *name: room name
*	- item_hash_t *llist: an empty (or not empty) list of items
*
* Output:
*	- an updated llist
*/
item_hash_t *make_default_items(char *name, item_hash_t *hash);

#endif /* _DEFAULT_ITEM_H */
