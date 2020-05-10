#ifndef _ROOM_H
#define _ROOM_H

#include "../game-state/game_state_common.h"
#include "sample_items.h"

#define ITER_ALL_PATHS(room, curr_path) path_t *ITTMP_PATH; \
HASH_ITER(hh, (room)->paths, (curr_path), ITTMP_PATH)

// PATH STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a path from one room to another.
* It contains:
*      string direction of path (case-sensitive)
*      the room_id of the destination room
*      list of conditions that must be fulfilled to move to the room
*      essentially, the list of conditions are the "answers"
* */
typedef struct path {
	UT_hash_handle hh;
	/* direction (north/south/etc) as key */
	char *direction; // *letter case matters*
	struct room *dest;
	/* the door item in the path, which has to be
	open (attribute open is set true) to let through */
	item_t *through;
} path_t;

/* This typedef is to distinguish between path_t pointers which are
* used to point to the path_t structs in the traditional sense,
* and those which are used to hash path_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct path path_hash_t;

// ROOM STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a 3 types of rooms: library, dungeon, open field..
* It contains:
*      the room_tag (this is the enum type)
*      the room_id
*      short description
*      long description
*      a hashtable of items to be found there
*      a hashtable of paths accessible from the room. */
typedef enum room_tag { LIBRARY, DUNGEON, OPEN_FIELD } room_tag_t;

typedef struct room {
	/* hh is used for hashtable, as provided in uthash.h */
	UT_hash_handle hh;
	room_tag_t room_tag;
	char *room_id;
	char *short_desc;
	char *long_desc;
	item_list_t *items;
	path_hash_t *paths;
} room_t;

/* This typedef is to distinguish between room_t pointers which are
* used to point to the room_t structs in the traditional sense,
* and those which are used to hash room_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct room room_hash_t;

typedef struct room_wrapped_for_llist {
	struct room_wrapped_for_llist *next;
	room_t *room;
} room_list_t;

// ROOM FUNCTIONS -------------------------------------------------------------
/* Mallocs space for a new room
*
* Parameters:
*  room_tag_t room_tag that specifies what kind of room
*
* Returns:
*  a pointer to new room
*/
room_t *room_new(room_tag_t room_tag);

/* room_init() initializes a room struct with given values
* Parameters:
* a memory allocated new room pointer
* room_tag_t room_tag which specifies room type
* 
* Returns:
* FAILURE for failure, SUCCESS for success
*/

int room_init(room_t *new_room, room_tag_t room_tag);

/* Frees the space in memory taken by given room
*
* Parameters:
*  pointer to the room struct to be freed
*
* Returns:
*  Always returns SUCCESS
*/

int room_free(room_t *room);

/* Get short description of room
*
* Parameters:
*  pointer to room
*
* Returns:
*  short description string
*/
char *get_sdesc(room_t *room);

/* Get long description of room
*
* Parameters:
*  pointer to room
*
* Returns:
*  long description string
*/
char *get_ldesc(room_t *room);


/* Get list (implemented with hashtable) of items in room
*
* Parameters:
*  pointer to room
*
* Returns:
*  hashtable of items in room
*/
item_hash_t* list_items(room_t *room);	

/* Get list of paths from room
*
* Parameters:
*  pointer to room
*
* Returns:
*  pointer to hashtable of paths from room
*/
path_t *list_paths(room_t *room);

#endif
