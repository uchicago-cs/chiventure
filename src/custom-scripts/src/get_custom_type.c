#include "custom-scripts/get_custom_type.h"
#include "lua_custom_types.c"

// see get_custom_types.h
bool bool_t_get(object_t *ot) {
    assert(ot->type == BOOL_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        int result = (int)lua_toboolean(L, -1);
        lua_pop(L, 1);
        return (result ? true : false);
    } 
    else {
        return ot->data.b;
    }
}

// see get_custom_types.h
char char_t_get(object_t *ot) {
    assert(ot->type == CHAR_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        const char *result = lua_tostring(L, -1);
        lua_pop(L, 1);
        char *result1 = strdup(result);
        return *result1;
    } else {
        return ot->data.c;
    }
}

// see get_custom_types.h
int int_t_get(object_t *ot) {
    assert(ot->type == INT_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        int result = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        return result;
    } else {
        return ot->data.i;
    }
}

// see get_custom_types.h
char* str_t_get(object_t *ot) {
    assert(ot->type == STR_TYPE);
    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
        const char *result = lua_tostring(L, -1);
        lua_pop(L, 1);
        char *result1 = strdup(result);
        return result1;
    } else {
        return ot->data.s;
    }
}