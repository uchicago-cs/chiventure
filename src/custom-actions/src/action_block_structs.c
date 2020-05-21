/* 
 * Action block structs to be used in custom-actions implementation
 *
 * Please see "action_block_structs.h" for struct documentation
 */

#ifndef INCLUDE_STRUCT_H_
#define INCLUDE_STRUCT_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/attribute_structs.h"
#include "custom-actions/ast_block_structs.h"

/* An enumeration type for an action block */
typedef enum action_type {
    SET,
    SAY,
    MOVE, 
    ADDSUBMULTDIV, 
    GEN, 
    EXEC
} action_type;

/* A block that holds an action, as well as corresponding attributes and actions */
typedef struct action_block {
    enum action_type action_type;
    int num_args;
    attribute_t** args;
    AST_block_t* next;
} action_block_t;

#endif /* INCLUDE_STRUCT_H_ */
