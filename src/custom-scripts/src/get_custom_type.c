#include "custom-scripts/get_custom_type.h"

// see get_custom_types.h
data_t arg_t_get(object_t *ot) {
    data_t d;
    lua_State *L;
    char *lua_path;

    if (ot->is_lua) {
        char *lua_path = ot->data.lua;
        lua_State *L = callLua(ot, lua_path);
    } else {
        return ot->data;
    }

    switch (ot->type) {
        case BOOL_TYPE:
            assert(ot->type == BOOL_TYPE);
            int result = (int)lua_toboolean(L, -1);
            lua_pop(L, 1);
            d.b = (result ? true : false);
            return d;
            break;
        case CHAR_TYPE:
            assert(ot->type == CHAR_TYPE);
            const char *result2 = lua_tostring(L, -1);
            lua_pop(L, 1);
            char *result3 = strdup(result2);
            d.c = *result3;
            return d;
            break;
        case INT_TYPE:
            assert(ot->type == INT_TYPE);
            int result4 = (int)lua_tointeger(L, -1);
            lua_pop(L, 1);
            d.i = result4;
            return d;
            break;
        case STR_TYPE:
            assert(ot->type == STR_TYPE);
            const char *result5 = lua_tostring(L, -1);
            lua_pop(L, 1);
            char *result6 = strdup(result5);
            d.s = result6;
            return d;
            break;
        default:
            return ot->data;
            break;
    }
}