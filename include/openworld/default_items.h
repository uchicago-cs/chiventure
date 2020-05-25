#ifndef _DEFAULT_ITEM_H
#define _DEFAULT_ITEM_H

#include "common/uthash.h"
#include "default_items.h"
#include "game-state/game_state_common.h"
#include "game-state/item.h"

/*get_default_items() returns all the default defined
* items in a hash table.
*/
item_hash_t *get_default_items();

#endif /* _DEFAULT_ITEM_H */
