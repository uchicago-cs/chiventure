#include "custom-scripts/custom_types.h"

// Basic new and initialization functions

// see custom_types.h
int_t int_t_new(int i, char* luaDirectory) {
    int_t it;
    return int_t_init(it, i, luaDirectory);
}

// see custom_types.h
int_t int_t_init(int_t it, int i, char* luaDirectory) {
    if (luaDirectory == NULL) { // if lua is not specified
        it.isInt = 1;
        it.p.i = i;
    } else {
        it.isInt = 0;
        it.p.luaDirectory = luaDirectory;
    }
    return it;
}

// see custom_types.h
int int_t_get(int_t it) {
    if (it.isInt) {
        return it.p.i;
    } else {
        char *lua_path = it.p.luaDirectory;
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
    }
}

// see custom_types.h
bool_t bool_t_new(bool b, char *luaDirectory) {
     bool_t bt;
    return bool_t_init(bt, b, luaDirectory);
}

// see custom_types.h
bool_t bool_t_init(bool_t bt, bool b, char *luaDirectory) {
    if (luaDirectory == NULL) { // if lua is not specified
        bt.isBool = 1;
        bt.p.b = b;
    } else {
        bt.isBool = 0;
        bt.p.luaDirectory = luaDirectory;
    }
    return bt;
}

// see custom_types.h
bool bool_t_get(bool_t bt) {
    if (bt.isBool) {
        return bt.p.b;
    } else {
        char *lua_path = bt.p.luaDirectory;
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
}

// see custom_types.h
string_t string_t_new(char *s, char *luaDirectory) {
    string_t st;
    return string_t_init(st, s, luaDirectory);
}

// see custom_types.h
string_t string_t_init(string_t st, char *s, char *luaDirectory) {
    if (luaDirectory == NULL) { // if lua is not specified
        st.isString = 1;
        st.p.s = s;
    } else {
        st.isString = 0;
        st.p.luaDirectory = luaDirectory;
    }
    return st;
}

// see custom_types.h
const char* string_t_get(string_t st) {
    if (st.isString) {
        return st.p.s;
    } else {
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
    }
    // temporary
    return st.p.s;
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