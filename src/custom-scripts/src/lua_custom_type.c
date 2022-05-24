#include "custom-scripts/lua_custom_type.h"

// see lua_custom_type.h
int push_args(lua_State *L, object_t* ot) {
    int count = 0; // number of arguments in linked list
    arg_t *head = ot->args;
    arg_t *to_push;
    // push arguments one-by-one
    DL_FOREACH(head, to_push) {
        count++;
        // identify type of argument
        data_type_t type = to_push->type;
        // push argument to virtual stack
        switch(type) {
            case BOOL_TYPE:
            {
                int b = to_push->data.b; // pushboolean requires int
                lua_pushboolean(L, b);
                break;
            }
            case CHAR_TYPE:
            {
                char c = to_push->data.c;
                lua_pushlstring(L, &c, 1);
                break;
            }
            case INT_TYPE:
            {
                int i = to_push->data.i;
                lua_pushnumber(L, i);
                break;
            }
            case STR_TYPE:
            {
                char *s = to_push->data.s;
                lua_pushstring(L, s);
                break;
            }
            default: // NONE_TYPE
                break;
        }
    }

    return count;
}

// see lua_custom_type.h
lua_State *callLua(object_t *ot, char *lua_path) {
    lua_State *L = luaL_newstate();

    // opens all standard Lua libraries into the given state
    luaL_openlibs(L);

    // loads the given file
    luaL_dofile(L, lua_path);

    // sets virtual stack top to index 0
    lua_settop(L, 0);

    // push functions and arguments and call function
    lua_getglobal(L, "foo");
    int num_args = push_args(L, ot);
    lua_pcall(L, num_args, 1, 0);

    return L;
}