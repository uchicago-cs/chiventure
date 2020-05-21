/* 
 * Action block structs to be used in custom-actions implementation 
 */

#ifndef INCLUDE_ACTION_BLOCK_STRUCTS_H_
#define INCLUDE_ACTION_BLOCK_STRUCTS_H_

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/ast_block_structs.h"

/* An enumeration type for an action block */
typedef enum action_type;

/* A block that holds an action, as well as corresponding attributes and actions */
typedef struct action_block;

#endif /* INCLUDE_ACTION_BLOCK_STRUCTS_H_ */
