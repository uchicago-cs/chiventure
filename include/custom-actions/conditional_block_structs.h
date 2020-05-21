/* 
 * Conditional block structs to be used in custom-actions implementation 
 */

#ifndef INCLUDE_CONDITIONAL_BLOCK_STRUCTS_H_
#define INCLUDE_CONDITIONAL_BLOCK_STRUCTS_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"

/* An enumeration type for a conditional block */
typedef enum conditional_type;

/* A block that returns true or false, and contains an operator and two attributes */
typedef struct conditional_block;

#endif /* INCLUDE_CONDITIONAL_BLOCK_STRUCTS_H_ */
