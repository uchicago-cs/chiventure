#ifndef _CUSTOM_TYPE_H_
#define _CUSTOM_TYPE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

/* File consisting of the custom pseudo-type created by Custom Scripts (inspired by libobj)
   =========================================================================== */

typedef enum datatype
{
    TYPE_NONE = 0,
    TYPE_BOOL = 1,
    TYPE_CHAR = 2,
    TYPE_INT = 3,
    TYPE_STR = 4,
} datatype_t;

typedef struct obj
{
    // Type of underlying data
    datatype_t type;

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
} obj_t;


/**
 * obj_t_new() creates an empty obj_t struct
 * Returns:
 * - obj_t empty object struct
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
obj_t obj_t_new();

/**
 * obj_t_bool() creates an obj_t struct containing a boolean
 * Parameters:
 * - bool value to be stored
 * - Lua script (NULL if no script to be specified)
 * Returns:
 * - obj_t object struct containing the bool
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
obj_t obj_t_bool(bool b, char *lua);

/**
 * obj_t_char() creates an obj_t struct containing a char
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - obj_t object struct containing the char
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
obj_t obj_t_char(char c, char *lua);

/**
 * obj_t_int() creates an obj_t struct containing a int
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - obj_t object struct containing the int
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
obj_t obj_t_int(int i, char *lua);

/**
 * obj_t_str() creates an obj_t struct containing a string
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - obj_t object struct containing the str
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
obj_t obj_t_str(char *s, char *lua);

/**
 * bool_t_get() returns a bool from an obj_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - bool from ot
 */
bool bool_t_get(obj_t ot);

/**
 * char_t_get() returns a char from an obj_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - char from ot
 */
char char_t_get(obj_t ot);

/**
 * int_t_get() returns an int from an obj_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - integer from ot
 */
int int_t_get(obj_t ot);

/**
 * string_t_get() returns a string from an obj_t struct
 * Parameters:
 * - ot: an obj_t
 * Returns:
 * - string from ot
 */
const char* string_t_get(obj_t ot);



#endif
