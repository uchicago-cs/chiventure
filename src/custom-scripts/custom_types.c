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