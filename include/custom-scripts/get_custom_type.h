#ifndef _GET_CUSTOM_TYPE_H_
#define _GET_CUSTOM_TYPE_H_

#include "lua_custom_type.h"

/**
 * bool_t_get() returns a bool from an object_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - bool from ot
 */
bool bool_t_get(object_t *ot);

/**
 * char_t_get() returns a char from an object_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - char from ot
 */
char char_t_get(object_t *ot);

/**
 * int_t_get() returns an int from an object_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - integer from ot
 */
int int_t_get(object_t *ot);

/**
 * string_t_get() returns a string from an object_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - string from ot
 */
char* str_t_get(object_t *ot);

#endif