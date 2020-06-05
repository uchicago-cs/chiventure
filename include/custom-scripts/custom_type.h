#ifndef _CUSTOM_TYPE_H_
#define _CUSTOM_TYPE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

/* File consisting of the custom pseudo-type created by Custom Scripts (inspired by libobj)
   =========================================================================== */

typedef enum data_type
{
    NONE_TYPE = 0,
    BOOL_TYPE = 1,
    CHAR_TYPE = 2,
    INT_TYPE = 3,
    STR_TYPE = 4,
} data_type_t;

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
} object_t;


/**
 * obj_t_new() creates an empty object_t struct
 * Returns:
 * - pointer to an empty object struct
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
object_t *obj_t_new();

/**
 * obj_t_bool() creates an object_t struct containing a boolean
 * Parameters:
 * - bool value to be stored
 * - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the bool
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
object_t *obj_t_bool(bool b, char *lua);

/**
 * obj_t_char() creates an object_t struct containing a char
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the char
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
object_t *obj_t_char(char c, char *lua);

/**
 * obj_t_int() creates an object_t struct containing a int
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the int
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
object_t *obj_t_int(int i, char *lua);

/**
 * obj_t_str() creates an object_t struct containing a string
 * Parameters:
 * - char value to be stored
 *  - Lua script (NULL if no script to be specified)
 * Returns:
 * - pointer to an object struct containing the str
 * 
 * Chose not to use pointer return type because data type is small,
 * so copying is not costly
 */
object_t *obj_t_str(char *s, char *lua);

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

/**
 * string_is_lua() determines whether a string is a Lua directory string
 * A lua directory string must start with LUA
 * Parameters:
 * - s: string to be investigated
 * Returns:
 * - boolean value (true = lua directory)
 */
bool string_is_lua(char* s);

/**
 * extra_lua(), given input is a Lua directory, extracts the Lua directory
 * Parameters:
 * - s: Lua directory string (includes "LUA " prefix)
 * Returns:
 * - String that is just the Lua directory
 */
char* extract_lua(char* s);

#endif
