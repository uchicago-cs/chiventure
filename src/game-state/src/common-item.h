#ifndef _COMMON_ITEM_H
#define _COMMON_ITEM_H

#include "item.h"
#include "game_action.h"

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


/* this has to be in the interface as room and player modules use this */
/* delete_all_items() deletes and frees all items in a hash table
 * Parameters:
 *  hash table of items
 * Returns:
 *  SUCCESS if successful
 */
int delete_all_items(item_hash_t items);

/* add_attribute_to_hash() adds an attribute to the item hash table
  Parameters:
    an item
    the attribute value to add

  Returns:
    FAILURE for failure, SUCCESS for success
*/
int add_attribute_to_hash(item_t* item, attribute_t* new_attribute);

/* get_attribute() returns a pointer to an attribute if it exists
  Parameters:
    an item
    the attribute name

  Returns:
    NULL if the attribute does not exist, pointer to attribute if it does
*/
attribute_t *get_attribute(item_t *item, char *attr_name);


/* delete_all_attributes() deletes all attributes in a hashtable of attributes
  Parameters:
    a hash table of attributes

  Returns:
    Always returns SUCCESS
*/
int delete_all_attributes(attribute_hash_t attributes);

/* action_new() allocates a space for an action struct in memory and
* assigns given values to struct fields
*  Parameters:
*    action name and an action type struct
*  Returns:
*    A pointer to a new action struct.
*/
game_action_t *game_action_new(char *act_name, char* success_str, char* fail_str);

/* action_init() initializes an action struct with given values
   arguments are taken from action management
 Parameters:
    a memory allocated new action pointer
    an action name
    an action type struct
 Returns:
    FAILURE for failure, SUCCESS for success
*/
int game_action_init(game_action_t *new_action, char *act_name, char* success_str, char* fail_str);
#endif
