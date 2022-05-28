#ifndef _GET_CUSTOM_TYPE_H_
#define _GET_CUSTOM_TYPE_H_

#include "lua_custom_type.h"

/**
 * arg_t_get() returns an data_t struct from an object_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - data from ot
 */
data_t arg_t_get(object_t *ot);

#endif