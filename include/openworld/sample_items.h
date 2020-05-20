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

typedef enum item_tag { APPLE, BOOK, COW, DOOR, EAGLE, FRUIT, GOLD, 
						HAT, ICE, JUG, KETTLE, LADDER, MIRROR,
						NAIL, OLIVE, PENCIL, QUILL, RABBIT,
						SCISSORS, TRAY, UMBRELLA, VIDEO, WATERCOLORS,
						XYLOPHONE, YAM, ZEBRA} item_tag_t;

typedef struct item {
	UT_hash_handle hh;
	item_tag_t item_tag;
	char *item_id;
	char *short_desc;
	char *long_desc;
//	game_action_hash_t *actions;
	attribute_list_t *attributes; // a hashtable for all attribute

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
*    item_tag_t item_tag which specifies item type
*  Returns:
*    A pointer to a new item struct.
*/
item_t *item_new(item_tag_t item_tag);

/* item_init() initializes an item struct with given values
* arguments are taken from WDL
* Parameters:
* a memory allocated new item pointer
* item_tag_t item_tag that specifies the kind of item
* Returns:
* FAILURE for failure, SUCCESS for success
*/
int item_init(item_t *new_item, item_tag_t item_tag);

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

// ATTRIBUTE STUCTURE DEFINITION ----------------------------------------------
// values will be loaded from WDL/provided by action management
typedef union attribute_value {
	double double_val;
	char char_val;
	bool bool_val;
	char* str_val;
	int int_val;
} attribute_value_t;

enum attribute_tag { DOUBLE, BOOLE, CHARACTER, STRING, INTEGER } attribute_tag_t;

typedef struct attribute {
	UT_hash_handle hh;
	char* attribute_key; // attribute name
	enum attribute_tag attribute_tag;
	attribute_value_t attribute_value;
} attribute_t;

typedef struct attribute_wrapped_for_llist {
	struct attribute_wrapped_for_llist *next;
	attribute_t *attribute;
} attribute_list_t;

/* attribute_init() initializes an attribute struct with given values
* arguments are taken from WDL
* Parameters:
* a memory allocated new attribute pointer
* char* attr_name that names the attribute
* attribute_tag_t item_tag that specifies the kind of item
* Returns:
* FAILURE for failure, SUCCESS for success
*/
int attribute_init(attribute_t* new_attr, char* attr_name, attribute_tag_t* tag);

/* attribute_new() allocates a space for an item struct in memory
*  Parameters:
*    char* attr_name that names the attribute
*	 attribute_tag_t* tag that specifies the data type of attribute
*  Returns:
*    A pointer to a new attribute struct.
*/
attribute_t* attribute_new(char* attr_name, attribute_tag_t* tag)

/* add_attribute_to_hash adds new attribute to hash table for search purposes
* IDK WILL FLESH OUT THIS DESCRIPTION LATER ONCE I UNDERSTAND THE HASH SYSTEM
*/
int add_attribute_to_hash(item_t* item, attribute_t* new_attribute);

/* set_int_attr() sets the value of an attribute of an item to the given int
* Parameters:
*  a pointer to the item
*  the attribute with value to be changed
*  the int attribute value to be set
* Returns:
*  SUCCESS if successful, FAILURE if failed
*  returns SUCCESS if given value is already the attribute value
*/
int set_int_attr(item_t* item, char* attr_name, int value);

/* attribute_free() frees allocated space for an attribute struct in memory
*  Parameters:
*    a pointer to the attribute
*  Returns:
*    SUCCESS if successful, FAILURE if not
*/
int attribute_free(attribute_t* attr)


#endif /* _SAMPLE_ITEM_H */
