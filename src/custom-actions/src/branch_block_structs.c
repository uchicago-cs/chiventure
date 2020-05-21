/* 
 * Branch block structs to be used in custom-actions implementation
 *
 * Please see "branch_block_structs.h" for struct documentation
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom-actions/branch_block_structs.h"
#include "custom-actions/conditional_block_structs.h"
#include "custom-actions/control_block_structs.h"

/* A block that holds pointers to both a control and a conditional block */
typedef struct branch_block {
    int num_conditionals;
    conditional_block_t** conditionals;
    enum conditional_type conditional_type;
    int num_controls;
    control_block_t** controls;
} branch_block_t;


