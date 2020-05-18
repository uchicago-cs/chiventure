#ifndef _CUSTOM_ACTIONS_COMMON_H
#define _CUSTOM_ACTIONS_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "common/uthash.h"
#include "common/utlist.h"
#include "common/common.h"

//Error codes for action block failure
// The block that was passed in is NULL
#define NULL_BLOCK 2
// An invalid number of attributes were passed in for the action type
#define INVALID_ARGS 3
// Something is wrong with at least one of the attribute pointers
// associated with the block
#define INVALID_ATTRIBUTES 4
// The operation the block has cannot be applied to the selected attributes 
// (e.g. greater than comparisons on strings)
#define OPERATION_ATTRIBUTE_MISTMATCH 5
// A control block with a paired end (WHILE/ENDWHILE, IF/ENDIF) 
// cannot find the respective end block in the path it goes down
#define CONTROL_MISSING_END 6
// The block passed in does not have its block_type set correctly
#define NO_TYPE 7

#endif