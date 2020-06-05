#ifndef _ITEM_H
#define _ITEM_H

#include "game_state_common.h"
#include "action_management/action_structs.h"

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

typedef struct item {
    UT_hash_handle hh; //makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
    char *item_id;
    char *short_desc;
    char *long_desc;
    game_action_hash_t *actions;
    attribute_hash_t *attributes; // a hashtable for all attributes
    struct item *next; // points to item w/ identical id, if it exists
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
*    a unique item id, sdesc, ldesc
*  Returns:
*    A pointer to a new item struct.
*/
item_t *item_new(char *item_id, char *short_desc, char *long_desc);

/* item_init() initializes an item struct with given values
   arguments are taken from WDL
 Parameters:
    a memory allocated new item pointer
    a unique item id
    a short description of the item
    a long description of the item
 Returns:
    FAILURE for failure, SUCCESS for success
*/
int item_init(item_t *new_item, char *item_id, char *short_desc, char *long_desc);

/* item_free() frees allocated space for an item struct in memory
*  Parameters:
*    a pointer to the item
*  Returns:
*    SUCCESS if successful, FAILURE if not
*/
int item_free(item_t *item_tofree);

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

/* Adds an item to a hashtable of items,
 * as long as the new item does not have the same memory address
 * as another item in the hashtable
 * 
 * Parameters:
 *  pointer to hashtable of items (pointer necessary for uthash to work)
 *  item to add to hashtable
 * 
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 */ 
int add_item_to_hash(item_hash_t **ht, item_t *new_item);

/* Function to get a linked list (utlist) of all the items in a hashtable
 *
 * Parameters:
 *  pointer to hashtable of items (pointer necessary for uthash to work)
 *
 * Returns:
 *  linked list of pointers to items (the head element)
 */ 
item_list_t *get_all_items_in_hash(item_hash_t **ht);


/* Removes an item from a hashtable of items
 * Note that the memory associated with this item is not freed
 * 
 * Parameters:
 *  pointer to hashtable of items (pointer necessary for uthash to work)
 *  item to add to hashtable
 * 
 * Return:
 *  SUCCESS if successful, FAILURE if failed
 */ 
int remove_item_from_hash(item_hash_t **ht, item_t *old_item);

// ATTRIBUTE STUCTURE DEFINITION ----------------------------------------------
// values will be loaded from WDL/provided by action management
typedef union attribute_value {
    double double_val;
    char char_val;
    bool bool_val;
    char* str_val;
    int int_val;
} attribute_value_t;

enum attribute_tag {DOUBLE, BOOLE, CHARACTER, STRING, INTEGER};

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

// ACTION STRUCTURE DEFINITION + BASIC FUNCTIONS ------------------------------

typedef struct game_action_condition{
    item_t *item;
    attribute_t* attribute_to_check; //pointer to attribute
    attribute_value_t expected_value;
    struct game_action_condition *next;
} game_action_condition_t;

/* This typedef is to distinguish between game_action_condition_t
* pointers which are used to point to the game_action_condition_t structs
* in the traditional sense, and those which are used to enable UTLIST functionality
* on the game_action_condition_t structs as specified in src/common/include
*/
typedef struct game_action_condition action_condition_list_t;

typedef struct game_action_effect{
    item_t *item;
    attribute_t* attribute_to_modify;
    attribute_value_t new_value;
    struct game_action_effect *next; //mandatory for utlist macros
} game_action_effect_t;

/* This typedef is to distinguish between game_action_effect_t
* pointers which are used to point to the game_action_effect_t structs
* in the traditional sense, and those which are used to enable UTLIST functionality
* on the game_action_effect_t structs as specified in src/common/include
*/
typedef struct game_action_effect action_effect_list_t;


typedef struct game_action {
    UT_hash_handle hh;
    char* action_name;
    action_condition_list_t *conditions; //must be initialized to NULL
    action_effect_list_t *effects; //must be initialized to NULL
    char* success_str;
    char* fail_str;
} game_action_t;


// ATTRIBUTE FUNCTIONS (FOR ITEMS) --------------------------------------------

/* attribute_free() frees given attribute
 * Parameters:
 *  pointer to an attribute
 * Returns:
 *  SUCCESS if successful
 */
int attribute_free(attribute_t *attribute);

/* get_attribute() returns a pointer to an attribute if it exists
 * Parameters:
 *  a pointer to an item
 *  attribute name
 * Returns:
 *  NULL if attribute does not exist, pointer to attribute if does
 */
attribute_t *get_attribute(item_t *item, char *attr_name);

/* attributes_equal() checks if two items have the same specific attribute
 * note that it only checks ONE attribute of two items
 * Parameters:
 *  pointer to item1
 *  pointer to item2
 *  the attribute name
 * Returns:
 *  -1 if attribute are different types or does not exist in one or both items
 *  1 if equal, 0 if not equal
 */
int attributes_equal(item_t* item_1, item_t* item_2, char* attribute_name);


// ATTRIBUTE ADDITION & REPLACEMENT FUNCTIONS ---------------------------------
// the following functions allow their users to add attributes to the given
// item or replace (read: change) attributes associated

/* set_str_attr() sets the value of an attribute of an item to the given string
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the string attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_str_attr(item_t* item, char* attr_name, char* value);

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

/* set_double_attr() sets the value of an attribute of an item to
 * the given double
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the double attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_double_attr(item_t* item, char* attr_name, double value);

/* set_char_attr() sets the value of an attribute of an item to the given char
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the char attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_char_attr(item_t* item, char* attr_name, char value);

/* set_bool_attr() sets the value of an attribute of an item to the given boolean
 * Parameters:
 *  a pointer to the item
 *  the attribute with value to be changed
 *  the bool attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_bool_attr(item_t* item, char* attr_name, bool value);

/* set_act_attr() sets the value of an attribute of an item to the given action
 * Parameters:
 *  a pointer to the item
 *  the attribute name with value to be changed
 *  the action attribute value to be set
 * Returns:
 *  SUCCESS if successful, FAILURE if failed
 *  returns SUCCESS if given value is already the attribute value
 */
int set_act_attr(item_t* item, char* attr_name, action_type_t *value);

// ATTRIBUTE GET FUNCTIONS --------------------------------------------
// the following functions allow their users to get (read: retrieve)
// attributes associated with an item using the name of the attribute

/* get_str_attr() returns the string value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the string value associated with the attribute
 */
char* get_str_attr(item_t *item, char* attr_name);

/* get_int_attr() returns the int value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the int value associated with the attribute
 */
int get_int_attr(item_t *item, char* attr_name);

/* get_double_attr() returns the double value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the double value associated with the attribute
 */
double get_double_attr(item_t *item, char* attr_name);

/* get_char_attr() returns the character value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the char value associated with the attribute
 */
char get_char_attr(item_t *item, char* attr_name);

/* get_bool_attr() returns the bool value of an attribute of an item
 * Parameters:
 *  a pointer to the item
 *  the attribute name
 * Returns:
 *  the bool value associated with the attribute
 */
bool get_bool_attr(item_t *item, char* attr_name);

//ATTRIBUTE LIST FUNCTIONS
/*
 * Function to get a linked list (utlist) of all the attributes in the item
 *
 * Parameters:
 *  item
 *
 * Returns:
 *  linked list of pointers to attributes (the head element)
 */
attribute_list_t *get_all_attributes(item_t *item);

/*
 * Function to delete a linked list (utlist) retrieved from get_all_attributes()
 *
 * Parameters:
 *  linked list of pointers to attributes
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_attribute_llist(attribute_list_t *head);


/*
 * Function to delete a linked list (utlist) retrieved from get_all_items()
 *
 * Parameters:
 *  linked list of pointers to items
 *
 * Returns:
 *  SUCCESS on success, FAILURE if an error occurs.
 */
int delete_item_llist(item_list_t *head);

/* item_init() initializes an item struct with given values
    arguments are taken from WDL
  Parameters:
    a memory allocated new item pointer
    a unique item id
    a short description of the item
    a long description of the item
  Returns:
    FAILURE for failure, SUCCESS for success
*/
int item_init(item_t *new_item, char *item_id,
              char *short_desc, char *long_desc);

/* this has to be in the interface as room and player modules use this */
/* delete_all_items() deletes and frees all items in a hash table
 * Parameters:
 *  Pointer to hash table of items
 * Returns:
 *  SUCCESS if successful
 */
int delete_all_items(item_hash_t **items);

/* add_attribute_to_hash() adds an attribute to the item hash table
  Parameters:
    an item
    the attribute value to add

  Returns:
    FAILURE for failure, SUCCESS for success
*/
int add_attribute_to_hash(item_t* item, attribute_t* new_attribute);


/* delete_all_attributes() deletes all attributes in a hashtable of attributes
  Parameters:
    a hash table of attributes

  Returns:
    Always returns SUCCESS
*/
int delete_all_attributes(attribute_hash_t *attributes);


/* action_init() initializes an action struct with given values
   arguments are taken from action management
 Parameters:
    a memory allocated new action pointer
    an action name
    an action type struct
 Returns:
    FAILURE for failure, SUCCESS for success
*/
int game_action_init(game_action_t *new_action, char *act_name, 
             char* success_str, char* fail_str);

#endif
