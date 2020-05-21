/*
 * AST block structs to be used in custom-actions implementation
 *
 * Please see "ast_block_structs.h" for struct documentation
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/ast_block_structs.h"
#include "custom-actions/control_block_structs.h"
#include "custom-actions/conditional_block_structs.h"
#include "custom-actions/branch_block_structs.h"
#include "custom-actions/action_block_structs.h"

/* An enumeration type for an AST block */
typedef enum block_type {
    CONTROL, 
    BRANCH, 
    ACTION, 
    CONDITIONAL
} block_type;

/* Struct to represent the type of a block */
typedef union block {
    control_block_t control_block;
    branch_block_t branch_block;
    action_block_t action_block;
    conditional_block_t conditional_block;
} block_t;

/* Struct to contain a block, as well as its type */
typedef struct AST_block {
    block_t block;
    enum block_type block_type;
} AST_block_t;


