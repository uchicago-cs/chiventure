#ifndef _DEFAULT_ROOM_H
#define _DEFAULT_ROOM_H

#include "../game-state/game_state_common.h"
#include "../game-state/room.h"
#include "default_items.h"
#include "gen_structs.h"

/*Get_allowed_rooms returns an array of roomspec_t for a default (or unknown) room
* for DEFAULT rooms: give as input the themed room "bucket". This can be
* 'school', 'farmhouse', or 'castle'. In each of these three themed "buckets"
* there are 5 different room types that can be assigned. Return the hard-coded 
* strings it corresponds to { room_name, short_desc, long_desc } in roomspec.
*
* for UNKNOWN rooms: this means either the given "bucket" is not recognized
* as one of the three already defined. "bucket" cannot be NULL. In this case,
* bucket is still a string, so use this as the room_id assignment instead.
* Also assign short_desc, long_desc to the given sh_desc and l_desc strings
* respectively. Return a singuar roomspec with this information
*
* Input: 
*	- char *bucket: the string naming the theme of a set of rooms
*	- char *sh_desc: an optional input, will be used as short_desc
*	- char *l_desc: an optional input, will be used as l_desc
*	-- note: if bucket is defined, it doesn't matter what sh_desc, l_desc are.
*			we already have fixed definitions for the rooms in this theme.--
* Output:
*	- roomspec **: an array of roomspecs with 3 hardcoded strings in a roomspec
*					in the following order: {room_id, short_desc, long_desc}
*
*/
roomspec_t **get_allowed_rooms(char *bucket, char *sh_desc, char *l_desc);


/*make_default_rooms adds all the defined default rooms for a themed 
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
*
* Output:
*	- roomspec_t updated hash
*/
roomspec_t *make_default_room(char *bucket, char *sh_desc, char *l_desc);

#endif /* _DEFAULT_ROOM_H */
