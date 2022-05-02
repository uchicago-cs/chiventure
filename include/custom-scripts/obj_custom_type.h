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
    union
    {
        bool b;
        char c;
        int  i;
        char *s;
        char *lua;
    } data;

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
object_t *obj_t_bool(bool b, char *lua);

/**
 * obj_t_char() creates an object_t struct containing a char
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the char
 */
object_t *obj_t_char(char c, char *lua);

/**
 * obj_t_int() creates an object_t struct containing a int
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the int
 */
object_t *obj_t_int(int i, char *lua);

/**
 * obj_t_str() creates an object_t struct containing a string
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the str
 */
object_t *obj_t_str(char *s, char *lua);

// ============================================================================

/**
 * obj_add_arg_bool adds a bool to the argument linked list of the object_t
 * Parameters:
 * - the object whose argument list is to be added to
 * - the boolean to be added
 * Returns:
 * - the updated object
 */
object_t *obj_add_arg_bool(object_t *obj, bool b);

/**
 * obj_add_arg_char adds a char to the argument linked list of the object_t
 * Parameters:
 * - the object whose argument list is to be added to
 * - the char to be added
 * Returns:
 * - the updated object
 */
object_t *obj_add_arg_char(object_t *obj, char c);

/**
 * obj_add_arg_int adds a int to the argument linked list of the object_t
 * Parameters:
 * - the object whose argument list is to be added to
 * - the int to be added
 * Returns:
 * - the updated object
 */
object_t *obj_add_arg_int(object_t *obj, int i);

/**
 * obj_add_arg_str adds a string to the argument linked list of the object_t
 * Parameters:
 * - the object whose argument list is to be added to
 * - the string to be added
 * Returns:
 * - the updated object
 */
object_t *obj_add_arg_str(object_t *obj, char *s);

#endif