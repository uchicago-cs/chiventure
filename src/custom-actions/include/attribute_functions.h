/* 
 * Functions to be used in attribute implementation
 */

#ifndef INCLUDE_ATTRIBUTE_FUNCTIONS_H
#define INCLUDE_ATTRIBUTE_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
//#include "custom-actions/struct.h"

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
attribute_t* attribute_new(UT_hash_handle hh, char *attribute_key, enum attribute_tag 
attribute_tag, attribute_value_t attribute_value);

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
int attribute_init(attribute_t *attribute, UT_hash_handle hh, char *attribute_key, enum           attribute_tag attribute_tag, attribute_value_t attribute_value);

#endif /* INCLUDE_ATTRIBUTE_FUNCTIONS_H */
