#ifndef _DEFAULT_ROOM_H
#define _DEFAULT_ROOM_H

#include "../game-state/game_state_common.h"
#include "../game-state/room.h"
#include "default_items.h"
#include "gen_structs.h"

/*make_default_rooms adds all the defined default rooms+items for a themed 
* "bucket" (a name for a group of related rooms). In the case where the 
* "bucket" IS NOT part of the default definitions, there are optional
* parameters for a short_desc, long_desc that will be used to define a
* new roomspec. In the case where "bucket" IS part of the default
* definitions (i.e. "bucket" is "school", "farmhouse", "castle"), then 
* add all the related rooms and all their related items to the roomspec hash.
* First, load an array of arrays of all the string descriptions for all the 
* related rooms to the "bucket". Then, assign each set of string descriptions
* to a  new roomspec, and assign all their allowed items to the hash as well.
* Iterate through all the appropriate rooms and all their allowed items. 
*
* Input:
*	- char *bucket: the string identifier for the theme of the set of rooms
*					if bucket is not already defined in default, just create
*					one room called bucket and add it to the hash.
*	- char *sh_desc: if "bucket" is part of default definitions, this parameter
*					is not necessary, and it can be NULL. (Will be disregarded anyway).
*					if "bucket" IS NOT part of default defn, use this as a room
*					short_desc.
*	- char *l_desc: similar purpose to sh_desc but for long_desc
*	- item_list_t *allowed: similar purpose to sh_desc but for allowed_items
*
* Output:
*	- roomspec_t updated hash
*/
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc,
	item_list_t *allowed);

#endif /* _DEFAULT_ROOM_H */
