#ifndef _DEFAULT_ROOM_H
#define _DEFAULT_ROOM_H

#include "default_items.h"
#include "game-state/game_state_common.h"
#include "game-state/room.h"
#include "gen_structs.h"

/* copy_item_to_hash is a helper function to deep copy
*  items from the src hash to the dest hash using name
*  as the key for lookup.
* 
*  Uses item-stacking (details https://github.com/uchicago-cs/chiventure/issues/703)
*  to add duplicate items to dest hash.
*  Input:
*  - item_hash_t *dst, *src: the source and destination hash tables
*  - char *name: the key for look up
*  Output: SUCCESS or FAILURE
*/
int copy_item_to_hash(item_hash_t **dst, item_hash_t *src, char *name);


/*make_default_rooms adds all the defined default rooms+items for a themed
* "bucket" (a name for a group of related rooms). In the case where the
* "bucket" IS NOT part of the default definitions, there are optional
* parameters for a short_desc, long_desc that will be used to define a
* new roomspec. In future springs, the npc struct will be added.
*
* Input:
*    - char *bucket: the string identifier for the theme of the set of rooms
*    -char **sh_desc: optional , unless "bucket" IS NOT default defn, use as a room short_desc.
*    - char *l_desc: similar purpose to sh_desc but for long_desc
*
* Output:
*    - roomspec_t updated hash
*/
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc);

#endif /* _DEFAULT_ROOM_H */
