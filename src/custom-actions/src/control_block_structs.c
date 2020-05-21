/* 
 * Control block structs to be used in custom-actions implementation
 *
 * Please see "control_block_structs.h" for struct documentation
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/ast_block_structs.h"
#include "custom-actions/control_block_structs.h"

/* An enumeration type for a control block */
typedef enum control_type {
    IFELSE,
    WHILEENDWHILE,
    FORENDFOR
} control_type;

/* Struct to contain a control block, which introduces an action */
typedef struct control_block {
    enum control_type control_type;
    AST_block_t* next;
} control_block_t;

