/* 
 * Control block structs to be used in custom-actions implementation
 *
 * Please see "control_block_structs.h" for struct documentation
 */

#ifndef INCLUDE_STRUCT_H_
#define INCLUDE_STRUCT_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/ast_block_structs.h"

/* An enumeration type for a control block */
typedef enum control_type {
    IFELSE,
    WHILEENDWHILE,
    FORENDFOR
} control_type;

/* An enumeration type for a control block */
typedef enum control_type {
    IFELSE,
    WHILEENDWHILE,
    FORENDFOR
} control_type;

#endif /* INCLUDE_STRUCT_H_ */
