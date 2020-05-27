#ifndef CUSTOM_ACTIONS_COMMON_H
#define CUSTOM_ACTIONS_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include "game-state/item.h"

#define TRUE 0
#define FALSE 1
#define SUCCEEDS 2
#define FAILS 3

/* attribute_new - allocates new attribute structure
 * 
 * Note: this is just a helper to allocate attribute structures with the
 *  necessary information testing because there is no attribute_new function
 *  provided in game-state/item.h
 *
 * Arguments:
 *  - tag: type of attribute value
 *  - value: attribute value
 *
 * Returns:
 *  - pointer to attribute
 */
attribute_t *attribute_new(enum attribute_tag tag, attribute_value_t value); 

#endif /* CUSTOM_ACTIONS_COMMON_H */
