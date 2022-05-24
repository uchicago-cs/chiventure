#include "custom-scripts/get_custom_type.h"

// see get_custom_types.h
data_t arg_t_get(object_t *ot) {
    data_t d;

    switch (ot->type) {
        case BOOL_TYPE:
            assert(ot->type == BOOL_TYPE);
            if (ot->is_lua) {
                char *lua_path = ot->data.lua;
                lua_State *L = callLua(ot, lua_path); 
                int result = (int)lua_toboolean(L, -1);
                lua_pop(L, 1);
                d.b = (result ? true : false);
                return d;
            } else {
                return ot->data;
            }
            break;
        case CHAR_TYPE:
            assert(ot->type == CHAR_TYPE);
            if (ot->is_lua) {
                char *lua_path = ot->data.lua;
                lua_State *L = callLua(ot, lua_path);
                const char *result = lua_tostring(L, -1);
                lua_pop(L, 1);
                char *result1 = strdup(result);
                d.c = *result1;
                return d;
            } else {
                return ot->data;
            }
            break;
        case INT_TYPE:
            assert(ot->type == INT_TYPE);
            if (ot->is_lua) {
                char *lua_path = ot->data.lua;
                lua_State *L = callLua(ot, lua_path);
                int result = (int)lua_tointeger(L, -1);
                lua_pop(L, 1);
                d.i = result;
                return d;
            } else {
                return ot->data;
            }
            break;
        case STR_TYPE:
            assert(ot->type == STR_TYPE);
            if (ot->is_lua) {
                char *lua_path = ot->data.lua;
                lua_State *L = callLua(ot, lua_path);
                const char *result = lua_tostring(L, -1);
                lua_pop(L, 1);
                char *result1 = strdup(result);
                d.s = result1;
                return d;
            } else {
                return ot->data;
            }
            break;
        default:
            return ot->data;
            break;
        }
    } 