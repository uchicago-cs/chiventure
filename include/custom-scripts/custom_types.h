#ifndef _CUSTOM_TYPES_H_
#define _CUSTOM_TYPES_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

// /* File consisting of all custom pseudo-types created by Custom Scripts
//    =========================================================================== */

// /**
//  * A pseudo-int type: underlying type is either an int or a Lua script directory
//  */
// typedef union pseudoInt {
//     int i;
//     char *luaDirectory;
// } pseudoInt;


// /**
//  * A type struct that contains the following:
//  * - isInt: whether the underlying is an int (1 = int, 0 = Lua Directory)
//  * - p: contains the underlying data type
//  */
// typedef struct int_t {
//     bool isInt; 
//     pseudoInt p;
// } int_t;


// /**
//  * int_t_new() creates an int_t struct
//  * Parameters:
//  * - i: underlying integer if applicable
//  * - luaDirectory: either defined or NULL string
//  * Returns:
//  * - int_t struct with contained data
//  * 
//  * Chose not to use pointer return type because data type is small,
//  * so copying is not costly
//  */
// int_t int_t_new(int i, char *luaDirectory);


// /**
//  * int_t_init() initializes a int_t struct
//  * Parameters:
//  * - it: a declared int_t type
//  * - i: underlying integer if applicable
//  * - luaDirectory: either defined or NULL string
//  * Returns:
//  * - int_t struct with contained data
//  * 
//  * Chose not to use pointer return type because data type is small,
//  * so copying is not costly
//  */
// int_t int_t_init(int_t it, int i, char *luaDirectory);


// /**
//  * int_t_get() returns an int from a int_t struct
//  * Parameters:
//  * - it: an int_t
//  * Returns:
//  * - integer from it
//  */
// int int_t_get(int_t it);


// /**
//  * A pseudo-bool type: underlying type is either a bool or a Lua script directory
//  */
// typedef union pseudoBool {
//     bool b;
//     char *luaDirectory;
// } pseudoBool;


// /**
//  * A type struct that contains the following:
//  * - isBool: whether the underlying is a bool (1 = bool, 0 = Lua Directory)
//  * - p: contains the underlying data type
//  */
// typedef struct {
//     bool isBool; 
//     pseudoBool p;
// } bool_t;


// /**
//  * bool_t_new() creates a bool_t struct
//  * Parameters:
//  * - s: underlying string if applicable
//  * - luaDirectory: either defined or NULL string
//  * Returns:
//  * - bool_t struct with contained data
//  * 
//  * Chose not to use pointer return type because data type is small,
//  * so copying is not costly
//  */
// bool_t bool_t_new(bool b, char *luaDirectory);


// /**
//  * bool_t_init() initializes a bool_t struct
//  * Parameters:
//  * - bt: a declared bool_t type
//  * - b: underlying bool if applicable
//  * - luaDirectory: either defined or NULL string
//  * Returns:
//  * - bool_t struct with contained data
//  * 
//  * Chose not to use pointer return type because data type is small,
//  * so copying is not costly
//  */
// bool_t bool_t_init(bool_t bt, bool b, char *luaDirectory);


// /**
//  * bool_t_get() returns a bool from a bool_t struct
//  * Parameters:
//  * - bt: a bool_t
//  * Returns:
//  * - bool from bt
//  */
// bool bool_t_get(bool_t bt);


// /**
//  * A pseudo-string type: underlying type is either a string or a Lua script directory
//  */
// typedef union pseudoString {
//     char *s;
//     char *luaDirectory;
// } pseudoString;


// /**
//  * A type struct that contains the following:
//  * - isString: whether the underlying is a string (1 = string, 0 = Lua Directory)
//  * - p: contains the underlying data type
//  */
// typedef struct {
//     bool isString; 
//     pseudoString p;
// } string_t;


// /**
//  * string_t_new() creates a string_t struct
//  * Parameters:
//  * - s: underlying string if applicable
//  * - luaDirectory: either defined or NULL string
//  * Returns:
//  * - string_t struct with contained data
//  * 
//  * Chose not to use pointer return type because data type is small,
//  * so copying is not costly
//  */
// string_t string_t_new(char *s, char *luaDirectory);


// /**
//  * string_t_init() initializes a string_t struct
//  * Parameters:
//  * - st: a declared string_t type
//  * - s: underlying string if applicable
//  * - luaDirectory: either defined or NULL string
//  * Returns:
//  * - string_t struct with contained data
//  * 
//  * Chose not to use pointer return type because data type is small,
//  * so copying is not costly
//  */
// string_t string_t_init(string_t it, char *s, char *luaDirectory);


// /**
//  * string_t_get() returns a string from a string_t struct
//  * Parameters:
//  * - st: a string_t
//  * Returns:
//  * - string from st
//  */
// const char* string_t_get(string_t st);


// /**
//  * string_is_lua() determines whether a string is a Lua directory string
//  * A lua directory string must start with LUA
//  * Parameters:
//  * - s: string to be investigated
//  * Returns:
//  * - boolean value (true = lua directory)
//  */
// bool string_is_lua(char* s);

// /**
//  * extra_lua(), given input is a Lua directory, extracts the Lua directory
//  * Parameters:
//  * - s: Lua directory string (includes "LUA " prefix)
//  * Returns:
//  * - String that is just the Lua directory
//  */
// char* extract_lua(char* s);


#endif
