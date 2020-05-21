#ifndef _SAMPLE_ROOM_H
#define _SAMPLE_ROOM_H

#include "../game-state/game_state_common.h"
#include "../game-state/room.h"
#include "sample_items.h"

#define ITER_ALL_PATHS(room, curr_path) path_t *ITTMP_PATH; \
HASH_ITER(hh, (room)->paths, (curr_path), ITTMP_PATH)

// FIXED ROOM STRUCT DEFINITION -----------------------------------------------------
/* This struct represents a 3 room themes: school, farmhouse, castle. Within these three
*  "buckets", we have several fixed room types assigned to each:
*	- school: classroom, closet, library, cafeteria, hallway
*	- farmhouse: barn, field, hallway, kitchen, living room
*	- castle: dungeon, hallway, library, throne room
* Each fixed room contains:
*      the room_tag (this is the enum type)
*      the room_id
*      short description
*      long description
*      a hashtable of items to be found there
*      a hashtable of paths accessible from the room. (see game-state/room.h)
*/

typedef enum fix_room_bucket { SCHOOL, FARMHOUSE, CASTLE } fix_room_bucket;

typedef enum fix_room_tag { BARN, CAFETERIA, CLASSROOM, CLOSET, DUNGEON, FIELD,
							HALLWAY, KITCHEN, LIBRARY, LIVING_ROOM, THRONE_ROOM} fix_room_tag_t;

typedef struct fix_room {
	fix_room_tag_t room_tag;
	room_t* room;
} fix_room_t;

/* This typedef is to distinguish between room_t pointers which are
* used to point to the room_t structs in the traditional sense,
* and those which are used to hash room_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct fix_room fixed_room_hash_t;

typedef struct fix_room_wrapped_for_llist {
	struct fix_room_wrapped_for_llist *next;
	fix_room_t *room;
} fix_room_list_t;

// ROOM FUNCTIONS -------------------------------------------------------------
/* Mallocs space for a new room
*
* Parameters:
*  room_tag_t room_tag that specifies what kind of room
*
* Returns:
*  a pointer to new room
*/
fix_room_t* fix_room_new(fix_room_tag_t room_tag, int items_wanted);

/* room_init() initializes a room struct with given values
* Parameters:
* a memory allocated new room pointer
* room_tag_t room_tag which specifies room type
* 
* Returns:
* FAILURE for failure, SUCCESS for success
*/

int fix_room_init(fix_room_t *new_room, fix_room_tag_t room_tag, int items_added);

/* Frees the space in memory taken by given room
*
* Parameters:
*  pointer to the room struct to be freed
*
* Returns:
*  Always returns SUCCESS
*/

int fix_room_free(fix_room_t *room);

/* Adds an item to the given room
*
* Parameters:
*  fix_room_t room of specific type needed by function,
*  int items wanted to specify how many times to iterate adding items
*  room tag is used to specify the appropriate subset of items that we
*		can choose from
*
* Returns:
*  SUCCESS if successful, FAILURE if failed
*/
int add_item_to_fix_room(fix_room_t *room, int items_wanted);

/* Get short description of room
*
* Parameters:
*  pointer to room
*
* Returns:
*  short description string
*/
char *get_sdesc_fix(fix_room_t *room);

/* Get long description of room
*
* Parameters:
*  pointer to room
*
* Returns:
*  long description string
*/
char *get_ldesc_fix(fix_room_t *room);

/* Get list (implemented with hashtable) of items in room
*
* Parameters:
*  pointer to room
*
* Returns:
*  hashtable of items in room
*/
item_hash_t* list_items(fix_room_t *room);	

/* Get list of paths from room
*
* Parameters:
*  pointer to room
*
* Returns:
*  pointer to hashtable of paths from room
*/
path_hash_t *list_fix_paths(fix_room_t *room);

/* Get a randomly generated room with no inital parameters
*  Will call on rand() function to randomly call on
* one of the hard-coded rooms
*
* Parameters: n\a
*
* Returns:
*  pointer to an initialized random room
*/
fix_room_t* generate_room();

#endif /* _SAMPLE_ROOM_H */
