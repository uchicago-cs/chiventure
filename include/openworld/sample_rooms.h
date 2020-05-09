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

// LIBRARY STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a library.
* It contains:
*      the room_id
*      short description
*      long description
*      a hashtable of items to be found there
*      a hashtable of paths accessible from the room. */
typedef struct library {
	/* hh is used for hashtable, as provided in uthash.h */
	char room_id[] = "library";
	char short_desc[] = "A libary room with skill-boosting resources";
	char long_desc[] = "A library with books, potions, and other skill-boosters";
	path_hash_t *paths;
	item_hash_t *items = { (book_t) b };
} library_t;

typedef struct dungeon {
	/* hh is used for hashtable, as provided in uthash.h */
	char room_id[] = "dungeon";
	char short_desc[] = "A dark dungeon with enemies";
	char long_desc[] = "A dank, dark dungeon with traps and enemies to battle";
	path_hash_t *paths;
	item_hash_t *items = { (apple_t) a };
} dungeon_t;

typedef struct open_field {
	/* hh is used for hashtable, as provided in uthash.h */
	char room_id[] = "field";
	char short_desc[] = "An open field";
	char long_desc[] = "An open field with grass and a clear view";
	path_hash_t *paths;
	item_hash_t *items = { (cow_t) c };
} open_field_t;

typedef union room_type {
	library l;
	dungeon d;
	open_field f;
}room_type_t;

enum room_tag { LIBRARY, DUNGEON, OPEN_FIELD };

typedef struct room {
	/* hh is used for hashtable, as provided in uthash.h */
	UT_hash_handle hh;
	enum room_tag room_tag;
	room_type_t room_type;
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
*  short string description
*  long string description
*  linked list of items in room
*  linked list of exits accessible from room
*
* Returns:
*  a pointer to new room
*/
room_t *room_new(char *room_id, char *short_desc, char *long_desc);

/* room_init() initializes a room struct with given values
Parameters:
a memory allocated new room pointer
a unique room id
a short description of the room
a long description of the room

Returns:
FAILURE for failure, SUCCESS for success
*/

int room_init(room_t *new_room, char *room_id, char *short_desc,
	char *long_desc);

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

/* Retrieves the pointer to an item contained within a room
* Parameters:
*   pointer to room
*   string of item's id
*
* Returns:
*   pointer to item, NULL if not foun
*/
item_t* get_item_in_room(room_t* room, char* item_id);

/*
* Function to get a linked list (utlist) of all the items in the room
*
* Parameters:
*  room
*
* Returns:
*  linked list of pointers to items (the head element)
*/
item_list_t *get_all_items_in_room(room_t *room);

#endif
