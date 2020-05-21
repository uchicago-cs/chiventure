/* 
 * AST block structs to be used in custom-actions implementation 
 */

#ifndef INCLUDE_AST_BLOCK_STRUCTS_H_
#define INCLUDE_AST_BLOCK_STRUCTS_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/control_block_structs.h"
#include "custom-actions/branch_block_structs.h"
#include "custom-actions/action_block_structs.h"
#include "custom-actions/conditional_block_structs.h"

/* An enumeration type for an AST block */
typedef enum block_type;

/* Struct to represent the type of a block */
typedef union block;

/* Struct to contain a block, as well as its type */
typedef struct AST_block;

#endif /* INCLUDE_AST_BLOCK_STRUCTS_H_ */
