/* 
 * Basic functions for conditional blocks to be used in custom-actions implementation. 
 * 
 * Please see "conditional_block_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/struct.h"
#include "game-state/item.h" 
#include "custom-actions/conditional_block_functions.h"

/* See conditional_block_functions.h */
conditional_block_t* conditional_block_new(enum conditional_type conditional_type, 
attribute_t* left, attribute_t* right)
{
    return NULL;
}

/* See conditional_block_functions.h */
int conditional_block_init(conditional_block_t *conditional, enum conditional_type 
conditional_type, attribute_t* left, attribute_t* right)
{
    return 0;
}

/* See conditional_block_functions.h */
int conditional_block_free(conditional_block_t *conditional)
{
    return 0;
}

