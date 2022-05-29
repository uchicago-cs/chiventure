#ifndef _OBJ_CUSTOM_TYPE_H_
#define _OBJ_CUSTOM_TYPE_H_

#include "arg_custom_type.h"

typedef struct obj_t
{
    // Type of underlying data
    data_type_t type;

    // Whether this data will be represented by a Lua script
    bool is_lua;

    // Data associated with the object
    data_t data;

    // Linked list of arguments
    arg_t *args;
} object_t;

/**
 * obj_t_new() creates an empty object_t struct
 * Returns:
 * - pointer to an empty object struct
 */
object_t *obj_t_new();

/**
 * obj_t_init() initializes an object_t struct
 * Parameters:
 * - data struct to be stored
 * - singular data_type_t enum held by data struct
 * - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the data struct
 */
object_t *obj_t_init(data_t d, data_type_t t, char *lua);

// ============================================================================

/**
 * obj_add_arg adds a data_t struct to the argument linked list of the object_t
 * Parameters:
 * - the object whose argument list is to be added to
 * - the data_t struct which will be added
 * - the data_type_t enum held by the data struct
 * Returns:
 * - the updated object
 */
object_t *obj_add_arg(object_t *obj, data_t d, data_type_t t);

#endif