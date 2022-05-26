#ifndef _LUA_CUSTOM_TYPE_H_
#define _LUA_CUSTOM_TYPE_H_

#include "obj_custom_type.h"

/**
 * Helper function used to push the arguments in the linked list
 * to the Lua vritual stack
 * Parameters:
 * - the Lua state created
 * - the object containing the argument linked list
 * Returns:
 * - the number of arguments in the linked list
 */
int push_args(lua_State *L, object_t* ot);

/**
 * Helper function for the getter functions below
 * Calls the Lua function in the directory specified, stores the data
 * in the Lua virtual stack for the getter functions to extract and return
 * Parameters:
 * - the object_t struct that contains the argument list to be passed to Lua
 * - the Lua script directory
 * Returns:
 * - the Lua state with the return value of the Lua script extracted and placed
 *   in the virtual stack
 */
lua_State *callLua(object_t *ot, char *lua_path);

#endif