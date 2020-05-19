/*
 * Basic functions for attributes to be used in custom-actions implementation. 
 * 
 * Please see "attribute_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/struct.h"
#include "game-state/item.h" 
#include "custom-actions/attribute_functions.h"

/* See attribute_functions.h */
attribute_t* attribute_new(attribute_value_t value, enum attribute_type 
attribute_type, char *name)
{
    return NULL;
}

/* See attribute_functions.h */
int attribute_init(attribute_t *attribute, attribute_value_t value, enum                  
attribute_type attribute_type, char *name)
{
    return 0;
}
