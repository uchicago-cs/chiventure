#ifndef _SAMPLE_ITEM_H
#define _SAMPLE_ITEM_H

#include "../game-state/game_state_common.h"
#include "sample_items.h"

#define ITER_ALL_ITEMS_IN_ROOM(room, curr_item) item_t *ITTMP_ITEMRM; \
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

typedef enum fix_item_tag { APPLE, BOOK, COW, DOOR, EAGLE, FRUIT, GOLD, 
						HAT, ICE, JUG, KETTLE, LADDER, MIRROR,
						NAIL, OLIVE, PENCIL, QUILL, RABBIT,
						SCISSORS, TRAY, UMBRELLA, VIDEO, WATERCOLORS,
						XYLOPHONE, YAM, ZEBRA} fix_item_tag_t;

typedef struct fix_item {
	UT_hash_handle hh;
	fix_item_tag_t item_tag;
	char *item_id;
	char *short_desc;
	char *long_desc;
//	game_action_hash_t *actions;
	attribute_list_t *attributes; // a hashtable for all attribute

} fix_item_t;

/* This typedef is to distinguish between item_t pointers which are
* used to point to the item_t structs in the traditional sense,
* and those which are used to hash item_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct fix_item fix_item_hash_t;

typedef struct fix_item_wrapped_for_llist {
	struct fix_item_wrapped_for_llist *next;
	fix_item_t *item;
} fix_item_list_t;

/* item_new() allocates a space for an item struct in memory
*  Parameters:
*    item_tag_t item_tag which specifies item type
*  Returns:
*    A pointer to a new item struct.
*/
fix_item_t *fix_item_new(fix_item_tag_t item_tag);

/* item_init() initializes an item struct with given values
* arguments are taken from WDL
* Parameters:
* a memory allocated new item pointer
* item_tag_t item_tag that specifies the kind of item
* Returns:
* FAILURE for failure, SUCCESS for success
*/
int fix_item_init(fix_item_t *new_item, fix_item_tag_t item_tag);

/* Get short description of item
*
* Parameters:
*  pointer to item
*
* Returns:
*  short description string
*  NULL if item is NULL
*/
char *get_sdesc_fix_item(fix_item_t *item);

/* Get long description of item
*
* Parameters:
*  pointer to item
*
* Returns:
*  long description string
*  NULL if item is NULL
*/
char *get_ldesc_fix_item(fix_item_t *item);

/* item_free() frees allocated space for an item struct in memory
*  Parameters:
*    a pointer to the item
*  Returns:
*    SUCCESS if successful, FAILURE if not
*/
int fix_item_free(fix_item_t *item_tofree);



#endif /* _SAMPLE_ITEM_H */
