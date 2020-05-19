/* 
 * Functions to be used in attribute implementation
 */

#ifndef INCLUDE_ATTRIBUTE_FUNCTIONS_H
#define INCLUDE_ATTRIBUTE_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/struct.h"

/* 
 * Allocates an attribute in the heap. 
 * 
 * Parameters: 
 * - an attribute value 
 * - a string with the attribute name 
 * - enum representing the attribute type 
 * 
 * Returns: 
 * - An attribute. 
 */
attribute_t* attribute_new(attribute_value_t value, enum attribute_tag 
attribute_tag, char *name);

/* 
 * Initializes attribute. 
 * 
 * Parameters: 
 * - attribute. Must point to already allocated memory.  
 * - an attribute value 
 * - a string with the attribute name  
 * - enum representing the attribute type    
 * 
 * Returns: 
 * - SUCCESS if success, FAILURE if error occurs
 */
int attribute_init(attribute_t *attribute, attribute_value_t value, enum                  
attribute_tag attribute_tag, char *name);

#endif /* INCLUDE_ATTRIBUTE_FUNCTIONS_H */
