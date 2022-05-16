#ifndef _GET_CUSTOM_TYPE_H_
#define _GET_CUSTOM_TYPE_H_

#include "lua_custom_type.h"

/**
 * bool_t_get() returns a bool from an object_t struct
 * Parameters:
 * - ot: an obj_t
 * - d: operating data type
 * Returns:
 * - bool from ot
 */
data_t arg_t_get(object_t *ot, data_t d);

#endif