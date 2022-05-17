#ifndef _OBJ_CUSTOM_TYPE_H_
#define _OBJ_CUSTOM_TYPE_H_

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
 * obj_t_bool() creates an object_t struct containing a boolean
 * Parameters:
 * - bool value to be stored
 * - Lua script (NULL if no script to be specified)
 * - argument linked list to be passed to Lua if applicable
 * Returns:
 * - pointer to an object struct containing the bool
 */
object_t *obj_t_init(data_t d, data_type_t t, char *lua);

// ============================================================================

/**
 * obj_add_arg_bool adds a bool to the argument linked list of the object_t
 * Parameters:
 * - the object whose argument list is to be added to
 * - the boolean to be added
 * Returns:
 * - the updated object
 */
object_t *obj_add_arg(object_t *obj, data_t d, data_type_t t);

#endif