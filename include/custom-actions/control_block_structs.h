/* 
 * Control block structs to be used in custom-actions implementation
 */

#ifndef INCLUDE_CONTROL_BLOCK_STRUCTS_H_
#define INCLUDE_CONTROL_BLOCK_STRUCTS_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/ast_block_structs.h"

/* An enumeration type for a control block */
typedef enum control_type;

/* Struct to contain a control block, which introduces an action */
typedef struct control_block;

#endif /* INCLUDE_CONTROL_BLOCK_STRUCTS_H_ */
