#ifndef _ITEM_H
#define _ITEM_H

#include "../game-state/game_state_common.h"
#include "../action_management/action_structs.h"

#define ITER_ALL_ITEMS_IN_ROOM(room, curr_item) item_t *ITTMP_ITEMRM; 
HASH_ITER(hh, (room)->items, (curr_item), ITTMP_ITEMRM)
#define ITER_ALL_ITEMS_IN_INVENTORY(player, curr_item) item_t *ITTMP_ITEMINV; \
HASH_ITER(hh, (player)->inventory, (curr_item), ITTMP_ITEMINV)
#define ITER_ALL_ATTRIBUTES(item, curr_attr) attribute_t *ITTMP_ATTR; \
HASH_ITER(hh, (item)->attributes, (curr_attr), ITTMP_ATTR)

// ITEM STRUCTURE DEFINITION + BASIC FUNCTIONS --------------------------------

/* This typedef is to distinguish between attribute_t pointers which are
* used to point to the attribute_t structs in the traditional sense,
* and those which are used to hash attribute_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct attribute attribute_hash_t;

typedef struct game_action game_action_hash_t;

typedef struct apple {
	UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
	char item_id[] = "apple";
	char short_desc[] = "A red apple";
	char long_desc[] = "A juicy Red Delicious apple";
	game_action_hash_t *actions;
	attribute_hash_t *attributes; // a hashtable for all attributes
} apple_t;

typedef struct book {
	UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
	char item_id = "book";
	char short_desc = "A big book";
	char long_desc = "A simulation survival encyclopedia";
	game_action_hash_t *actions;
	attribute_hash_t *attributes; // a hashtable for all attributes
} book_t;

typedef struct cow {
	UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
	char item_id[] = "cow";
	char short_desc[] = "A black and white cow";
	char long_desc[] = "A black and white cow named Mavis";
	game_action_hash_t *actions;
	attribute_hash_t *attributes; // a hashtable for all attributes
} cow_t;

typedef struct door {
	UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
	char item_id[] = "door";
	char short_desc[] = "A normal door";
	char long_desc[] = "A wooden door with a worn doorknob";
	game_action_hash_t *actions;
	attribute_hash_t *attributes; // a hashtable for all attributes
} door_t;

typedef struct window {
	UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
	char item_id[] = "window";
	char short_desc[] = "A normal window";
	char long_desc[] = "A clean window with an operating handle";
	game_action_hash_t *actions;
	attribute_hash_t *attributes; // a hashtable for all attributes
} window_t;

typedef union item_type {
	apple_t a;
	book_t b;
	cow_t c;
	door_t d;
	window_t w;
}item_type_t;

enum item_tag { APPLE, BOOK, COW, DOOR, WINDOW };

typedef struct item {
	UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
	enum item_tag item_tag;
	item_type_t item_type;
	game_action_hash_t *actions;
	attribute_hash_t *attributes; // a hashtable for all attributes
} item_t;

/* This typedef is to distinguish between item_t pointers which are
* used to point to the item_t structs in the traditional sense,
* and those which are used to hash item_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct item item_hash_t;

typedef struct item_wrapped_for_llist {
	struct item_wrapped_for_llist *next;
	item_t *item;
} item_list_t;

/* item_new() allocates a space for an item struct in memory
*  Parameters:
*    a unique item id
*  Returns:
*    A pointer to a new item struct.
*/
item_t *item_new(char *item_id);

/* item_init() initializes an item struct with given values
arguments are taken from WDL
Parameters:
a memory allocated new item pointer
a unique item id
Returns:
FAILURE for failure, SUCCESS for success
*/
int item_init(item_t *new_item, char *item_id);

/* Get short description of item
*
* Parameters:
*  pointer to item
*
* Returns:
*  short description string
*  NULL if item is NULL
*/
char *get_sdesc_item(item_t *item);

/* Get long description of item
*
* Parameters:
*  pointer to item
*
* Returns:
*  long description string
*  NULL if item is NULL
*/
char *get_ldesc_item(item_t *item);

/* item_free() frees allocated space for an item struct in memory
*  Parameters:
*    a pointer to the item
*  Returns:
*    SUCCESS if successful, FAILURE if not
*/
int item_free(item_t *item_tofree);



#endif
