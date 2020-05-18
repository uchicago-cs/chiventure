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
#define NULL_BLOCK 2
#define INVALID_ARGS 3
#define INVALID_ATTRIBUTES 4
#define OPERATION_ATTRIBUTE_MISTMATCH 5
#define CONTROL_MISSING_END 6

#endif