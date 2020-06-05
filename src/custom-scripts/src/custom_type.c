#include "custom-scripts/custom_type.h"

// see custom_type.h
object_t *obj_t_new()
{
    object_t *ot = (object_t*)malloc(sizeof(object_t));
    ot->type = NONE_TYPE;
    ot->is_lua = false;
    return ot;
}

// see custom_type.h
object_t *obj_t_bool(bool b, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = BOOL_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data.b = b;
    }
    return ot;
}

// see custom_type.h
object_t *obj_t_char(char c, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = CHAR_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data.c = c;
    }
    return ot;
}

// see custom_type.h
object_t *obj_t_int(int i, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = INT_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data.i = i;
    }
    return ot;
}

// see custom_type.h
object_t *obj_t_str(char *s, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = STR_TYPE;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data.s = s;
    }
    return ot;
}

/**
 * Helper function for the getter functions below
 * Calls the Lua function in the directory specified, stores the data
 * in the Lua virtual stack for the getter functions to extract and return
 */
lua_State *callLua(char *lua_path) {
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dofile(L, lua_path);
        lua_settop(L, 0);
        lua_getglobal(L, "foo");
        lua_pcall(L, 0, 1, 0);
        return L;
}

// see custom_types.h
bool bool_t_get(object_t *ot) {
    assert(ot->type == BOOL_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(lua_path);
        int result = (int)lua_toboolean(L, -1);
        lua_pop(L, 1);
        if (result)
            return true;
        else
            return false;
    } 
    else {
        return ot->data.b;
    }
}

// see custom_types.h
char char_t_get(object_t *ot) {
    assert(ot->type == CHAR_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(lua_path);
        const char *result = lua_tostring(L, -1);
        lua_pop(L, 1);
        char *result1 = strdup(result);
        return *result1;
    } else {
        return ot->data.c;
    }
}

// see custom_types.h
int int_t_get(object_t *ot) {
    assert(ot->type == INT_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(lua_path);
        int result = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        return result;
    } else {
        return ot->data.i;
    }
}

// see custom_types.h
char* str_t_get(object_t *ot) {
    assert(ot->type == STR_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(lua_path);
        const char *result = lua_tostring(L, -1);
        lua_pop(L, 1);
        char *result1 = strdup(result);
        return result1;
    } else {
        return ot->data.s;
    }
}

// see custom_types.h
bool string_is_lua(char* s) {
    if (!(s)) { // string is NULL
        return false;
    }
    if (s[0] == 'L' && s[1] == 'U' && s[2] == 'A' && s[3] == ' ') {
        return true;
    } else {
        return false;
    }
}

// see custom_types.h
char* extract_lua(char* s) {
    return s + 4; // remove the first 4 characters of the string
}
