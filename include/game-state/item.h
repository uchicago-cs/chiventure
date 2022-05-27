#ifndef _ITEM_H
#define _ITEM_H

#include "game_state_common.h"
#include "action_management/action_structs.h"
#include "game-state/stats.h"

#define ITER_ALL_ITEMS_IN_ROOM(room, curr_item) item_list_t *ITTMP_ITEMRM; \
LL_FOREACH_SAFE(get_all_items_in_hash(&((room)->items)), (curr_item), ITTMP_ITEMRM)
#define ITER_ALL_ITEMS_IN_INVENTORY(player, curr_item) item_list_t *ITTMP_ITEMINV; \
LL_FOREACH_SAFE(get_all_items_in_hash(&((player)->inventory)), (curr_item), ITTMP_ITEMINV)
#define ITER_ALL_ATTRIBUTES(item, curr_attr) attribute_t *ITTMP_ATTR; \
HASH_ITER(hh, (item)->attributes, (curr_attr), ITTMP_ATTR)

/* Forward declaration. Full typedef can be found in player.h */
typedef struct player player_t;
/* Forward declaration. Full typedef can be found in condition.h */
typedef struct condition condition_list_t;

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

// ITEM STRUCTURE DEFINITION + BASIC FUNCTIONS --------------------------------

/* This typedef is to distinguish between attribute_t pointers which are
* used to point to the attribute_t structs in the traditional sense,
* and those which are used to hash attribute_t structs with the
* UTHASH macros as specified in src/common/include */
typedef struct attribute attribute_hash_t;

/* Forward declarations. Full typedef can be found in actionmanagement.h */
typedef struct game_action game_action_hash_t;
typedef struct game_action game_action_t;

typedef struct item {
    UT_hash_handle hh; // makes this struct hashable for the room struct (objects in rooms) and player struct (inventory)
    UT_hash_handle hh_all_items; // This second hash handle makes it possible
                                 // for an item to belong to two hash tables.
                                 // For example, game->all_items and player->
                                 // inventory. This hash handle is reserved for
                                 // the game->all_items hash table.
    char *item_id;
    char *short_desc;
    char *long_desc;
    game_action_hash_t *actions;
    attribute_list_t *class_multipliers; // a linked list of all player class multipliers
    attribute_hash_t *attributes; // a hashtable for all attributes
    effects_hash_t *stat_effects; // hashtable of effects item can have (set to NULL if no effects)
    struct item *next; // points to item w/ identical id, if it exists
    char *item_image; // a file path to an image of an item
    unsigned int inventory_x_pos; // a x-coordinate for an item's position in an inventory
    unsigned int inventory_y_pos; // a y-coordinate for an item's position in an inventory
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

/* Function to get an item from an item hashtable
 *
 * Parameters:
 *  pointer to hashtable of items
 *  id of the item
 *
 * Returns:
 *  pointer to the item, or NULL if it does not exist
 */ 
item_t *get_item_in_hash(item_hash_t *ht, char *id);

/* Removes an item from a hashtable of items
 * Note that the memory associated with this item is not freed
 * 
 * Parameters:
 *  pointer to hashtable of items (pointer necessary for uthash to work)
 *  item to remove from hashtable
 * 
 * Return:
 *  SUCCESS if successful, FAILURE if failed
 */ 
int remove_item_from_hash(item_hash_t **ht, item_t *old_item);

/* Adds an item to a hashtable using the hash handle hh_all_items.
 * NOTE: This function should only be used to populate game->all_items!
 * 
 * Parameters:
 *  pointer to a hashtable of items (specifically, game->all_items)
 *  item to add to the hashtable
 *
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 */
int add_item_to_all_items_hash(item_hash_t **all_items, item_t *item);

/* Removes an item from a hashtable via the hash handle hh_all_items.
 * NOTE: This function should only be used to unload game->all_items!
 * 
 * Parameters:
 *  pointer to a hashtable of items (specifically, game->all_items)
 *  item to remove from the hashtable
 *
 * Returns: 
 *  SUCCESS if successful, FAILURE if failed
 */
int remove_item_from_all_items_hash(item_hash_t **all_items, item_t *item);

/* Adds a stat effect to an item
 * 
 * Parameters:
 *  pointer to an item
 *  effect to add to item
 * 
 * Return:
 *  SUCCESS if successful, FAILURE if failed
 */ 
int add_effect_to_item(item_t *item, stat_effect_t *effect);


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

/* str_attr_new() creates a new string-specific attribute
 * Parameters:
 *  Name of the attribute (char*)
 *  The value to add to the attribute
 * Returns:
 *  Pointer to the new attribute, NULL if memory was unable to be allocated
 */
attribute_t* str_attr_new(char* attr_name, char* value);

/* int_attr_new() creates a new integer-specific attribute
 * Parameters:
 *  Name of the attribute (char*)
 *  The value to add to the attribute
 * Returns:
 *  Pointer to the new attribute, NULL if memory was unable to be allocated
 */
attribute_t* int_attr_new(char* attr_name, int value);

/* double_attr_new() creates a new double-specific attribute
 * Parameters:
 *  Name of the attribute (char*)
 *  The value to add to the attribute
 * Returns:
 *  Pointer to the new attribute, NULL if memory was unable to be allocated
 */
attribute_t* double_attr_new(char* attr_name, double value);

/* char_attr_new() creates a new char-specific attribute
 * Parameters:
 *  Name of the attribute (char*)
 *  The value to add to the attribute
 * Returns:
 *  Pointer to the new attribute, NULL if memory was unable to be allocated
 */
attribute_t* char_attr_new(char* attr_name, char value);

/* bool_attr_new() creates a new bool-specific attribute
 * Parameters:
 *  Name of the attribute (char*)
 *  The value to add to the attribute
 * Returns:
 *  Pointer to the new attribute, NULL if memory was unable to be allocated
 */
attribute_t* bool_attr_new(char* attr_name, bool value);

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

/* create_list_attribute: creates an empty attribute_list_t 
 * 
 * Returns: A pointer to the created attribute_list_t
 */
attribute_list_t* create_list_attribute();

/*
 * Function to check if a linked list (utlist) contains a specific attribute
 * 
 * Parameters:
 *  linked list of pointers to attributes
 *  name of a specific attribute
 *
 * Returns:
 *  false for does not contain, true for contains
 */
bool list_contains_attribute(attribute_list_t *head, char *attr_name);

/*
 * Function to add an attribute to a linked listed (utlist) of attributes
 *
 * Paramaters:
 *  Linked list of pointers to attributes
 *  An attribute to add to the list
 * 
 * Returns:
 *  FAILURE if it failed to add the attribute, SUCCESS if it adds/the list contains the attribute
 */
int add_attribute_to_list(attribute_list_t *head, attribute_t *attr);

/*
 * Function to remove an attribute from a linked listed (utlist) of attributes
 *
 * Parameters:
 *  Linked list of pointers to attributes
 *  (char*) The attribute key of the attribute to be removed
 * 
 * Returns:
 *  FAILURE it failed to remove the element from the list
 *  SUCCESS if the element was removed from the list
 */
int remove_attribute_from_list(attribute_list_t *head, char *attr_name);

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
/* delete_all_items() deletes all items in a hash table
 * NOTE: This function does not free the individual item structs, nor deal
 *       the linked lists. The freeing of the structs is done by
 *       delete_all_items_from_game() (in game.c)
 *
 * Parameters:
 *  Pointer to hash table of items
 *
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


/* list_get_attribute() returns a pointer to an attribute if it exists
 * Parameters:
 *  a pointer to a attribute_list
 *  attribute name
 * Returns:
 *  NULL if attribute does not exist, pointer to attribute if it does
 */
attribute_t *list_get_attribute(attribute_list_t *head, char* attr_name);


/* list_get_str_attr() returns the string value of an attribute of an item
 * Parameters:
 *  a pointer to the attribute_list
 *  the attribute name
 * Returns:
 *  the string value associated with the attribute
 */
char* list_get_str_attr(attribute_list_t *head, char* attr_name);


/* list_get_int_attr() returns the int value of an attribute of an item
 * Parameters:
 *  a pointer to the attribute_list
 *  the attribute name
 * Returns:
 *  the int value associated with the attribute
 */
int list_get_int_attr(attribute_list_t *head, char* attr_name);


/* list_get_double_attr() returns the double value of an attribute of an item
 * Parameters:
 *  a pointer to the attribute_list
 *  the attribute name
 * Returns:
 *  the double value associated with the attribute
 */
double list_get_double_attr(attribute_list_t *head, char* attr_name);


/* list_get_char_attr() returns the char value of an attribute of an item
 * Parameters:
 *  a pointer to the attribute_list
 *  the attribute name
 * Returns:
 *  the char value associated with the attribute
 */
char list_get_char_attr(attribute_list_t *head, char* attr_name);


/* list_get_bool_attr() returns the bool value of an attribute of an item
 * Parameters:
 *  a pointer to the attribute_list
 *  the attribute name
 * Returns:
 *  the bool value associated with the attribute
 */
bool list_get_bool_attr(attribute_list_t *head, char* attr_name);

#endif
