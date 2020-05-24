//#include "custom-scripts/custom_type.h"
#include "custom-scripts/custom_type.h"

// see custom_type.h
obj_t obj_t_new()
{
    obj_t ot;
    ot.type = TYPE_NONE;
    ot.is_lua = false;
    return ot;
}

// see custom_type.h
obj_t obj_t_bool(bool b, char *lua)
{
    obj_t ot = obj_t_new();
    ot.type = TYPE_BOOL;
    if (lua) {
        ot.is_lua = true;
        ot.data.lua = lua;
    } else {
        ot.data.b = b;
    }
    return ot;
}

// see custom_type.h
obj_t obj_t_char(char c, char *lua)
{
    obj_t ot = obj_t_new();
    ot.type = TYPE_CHAR;
    if (lua) {
        ot.is_lua = true;
        ot.data.lua = lua;
    } else {
        ot.data.c = c;
    }
    return ot;
}

// see custom_type.h
obj_t obj_t_int(int i, char *lua)
{
    obj_t ot = obj_t_new();
    ot.type = TYPE_INT;
    if (lua) {
        ot.is_lua = true;
        ot.data.lua = lua;
    } else {
        ot.data.i = i;
    }
    return ot;
}

// see custom_type.h
obj_t obj_t_str(char *s, char *lua)
{
    obj_t ot = obj_t_new();
    ot.type = TYPE_STR;
    if (lua) {
        ot.is_lua = true;
        ot.data.lua = lua;
    } else {
        ot.data.s = s;
    }
    return ot;
}


// see custom_types.h
bool bool_t_get(obj_t ot) {
    assert(ot.type == TYPE_BOOL);
    if (ot.is_lua) {
        char *lua_path = ot.data.lua;
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dofile(L, lua_path);
        lua_settop(L, 0);
        lua_getglobal(L, "foo");
        lua_call(L, 0, 1);
        //lua_pcall(L, 0, 1, 0);
        int result = (int)lua_toboolean(L, -1);
        lua_pop(L, 1);
        if (result)
            return true;
        else
            return false;
    } 
    else {
        return ot.data.b;
    }
}


// see custom_types.h
char char_t_get(obj_t ot) {
    assert(ot.type == TYPE_CHAR);
    if (ot.is_lua) {
        char *lua_path = ot.data.lua;
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dofile(L, lua_path);
        lua_settop(L, 0);
        lua_getglobal(L, "foo");
        lua_call(L, 0, 1);
        //lua_pcall(L, 0, 1, 0);
        const char *result = lua_tostring(L, -1);
        //printf ("Lua string is %s\n", result);
        lua_pop(L, 1);
        return *result;
    } else {
        return ot.data.c;
    }
}

// see custom_types.h
int int_t_get(obj_t ot) {
    assert(ot.type == TYPE_INT);
    if (ot.is_lua) {
        char *lua_path = ot.data.lua;
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dofile(L, lua_path);
        lua_settop(L, 0);
        lua_getglobal(L, "foo");
        lua_call(L, 0, 1);
        //lua_pcall(L, 0, 1, 0);
        int result = (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        return result;
    } else {
        return ot.data.i;
    }
}

// see custom_types.h
char* str_t_get(obj_t ot) {
    assert(ot.type == TYPE_STR);
    if (ot.is_lua) {
        char *lua_path = st.p.luaDirectory;
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        luaL_dofile(L, lua_path);
        lua_settop(L, 0);
        lua_getglobal(L, "foo");
        lua_call(L, 0, 1);
        //lua_pcall(L, 0, 1, 0);
        const char *result = lua_tostring(L, -1);
        //printf ("Lua string is %s\n", result);
        lua_pop(L, 1);
        return result;
    } else {
        return ot.data.s;
    }
}
