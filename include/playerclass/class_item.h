#ifndef _CLASS_ITEM_H
#define _CLASS_ITEM_H

/*
 * Module for class-item interactions. Provides functionality for:
 * - Adding "multipliers" as fields of an item that control 
 *   how well certain player classes can the item
 * - Checking and removing class multipliers
 * - Restricting a class from using a specific item and checking
 *   whether or not a class is restricted from item usage
 * - Removing class restrictions
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game-state/item.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"


/* Given an item and a class, adds an attribute of the class to the item representing a multiplier.
 * 
 * Utilizes the class multiplier field of an item to set this information.  If the multiplier
 * already exists, it is overwritten.
 *
 * Parameters:
 * - item_t* item: item to which class attribute is being added
 * - class_t* class: class which is restricted from using item
 * - multiplier: the multiplier applied when the item is used, 0 represents a 
 *               restriction
 * 
 * Returns:
 * - int: 
 *   - SUCCESS if successful (includes overwriting a prexisting attribute)
 *   - FAILURE if not
 */
int add_item_multiplier(item_t* item, class_t* class, double multiplier);


/* Given an item and a class, returns the proficiency multiplier that class has when using the item.
 *
 * Utilizes the class multiplier field of an item to retrieve this information.  
 *
 * Parameters:
 * - item_t* item: item being checked for class multiplier
 * - class_t* class: class being checked
 * 
 * Return:
 * - double: 
 *   - 0.0 if the item is restricted
 *   - 1.0 if no multiplier has been set
 *   - The multiplier in all other cases
*/
double get_class_item_multiplier(item_t* item, class_t* class);


/* Given an item and a class, removes the class multiplier on the item.
 * 
 * Utilizes the class multipliers field of an item to change this information. 
 *
 * Parameters:
 * - item_t* item: item to which class attribute is being removed
 * - class_t* class: class which has proficiency multiplier using the item
 * 
 * Returns:
 * - int: 
 *   - SUCCESS if successful (includes case where the attribute does not exist)
 *   - FAILURE if not
 */
int remove_item_multiplier(item_t* item, class_t* class);


/* Given an item and a class, adds an attribute of the class to the item representing a restriction.
 * 
 * Utilizes the class restrictions field of an item to set this information.
 *
 * Parameters:
 * - item_t* item: item to which class attribute is being added
 * - class_t* class: class which is restricted from using item
 * 
 * Returns:
 * - int: 
 *   - SUCCESS if successful
 *   - FAILURE if not
 */
int add_item_restriction(item_t* item, class_t* class);


/* Given an item and a class, returns whether or not that class is restricted from using the item.
 *
 * Utilizes the class multiplier field of an item to retrieve this information.
 *
 * Parameters:
 * - item_t* item: item being checked for class restrictions
 * - class_t* class: class being checked
 * 
 * Return:
 * - bool: 
 *    - true if restricted
 *    - false if not
*/
bool is_restricted(item_t* item, class_t* class);


/* Given an item and a class, removes the class restriction on the item.
 * 
 * Utilizes the class multipliers field of an item to change this information.
 *
 * Parameters:
 * - item_t* item: item to which class attribute is being removed
 * - class_t* class: class which is restricted from using item
 * 
 * Returns:
 * - int: 
 *   - SUCCESS if successful
 *   - FAILURE if not
 */
int remove_item_restriction(item_t* item, class_t* class);


#endif /* CLASS_ITEM_H */
