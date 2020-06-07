#ifndef _CLASS_ITEM_RESTRICTION_H
#define _CLASS_ITEM_RESTRICTION_H
/*
 * Module for class-item restrictions. Provides functionality for
 * restricting a class from using a specific item and checking
 * whether or not a class is restricted from item usage. 
*/
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game-state/item.h"
#include "playerclass/class.h"
#include "playerclass/class_structs.h"

/*Given an item and a class, adds an attribute of the class to the item and sets to True
 * Parameters:
 * - item_t* item: item to which class attribute is being added
 * - class_t* class: class which is restricted from using item
 * Return:
 *- int: 
 *   - SUCCESS if successful
 *   - FAILURE if not
 */
int set_item_restriction(item_t* item, class_t* class);

/*Given an item and a class, returns whether or not that class is restricted from using item
* Parameters:
* - item_t* item: item being checked for class restrictions
* - class_t* class: class being checked
*
* Return:
* - bool: 
*    - true if restricted
*    - false if not
*/
bool get_class_restriction(item_t* item, class_t* class);

#endif /* CLASS_ITEM_RESTRICTION_H */