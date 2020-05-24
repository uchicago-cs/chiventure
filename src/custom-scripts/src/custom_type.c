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
        // return using lua script
    } else {
        return ot.data.b;
    }
}


// see custom_types.h
char char_t_get(obj_t ot) {
    assert(ot.type == TYPE_CHAR);
    if (ot.is_lua) {
        // return using lua script
    } else {
        return ot.data.c;
    }
}

// see custom_types.h
int int_t_get(obj_t ot) {
    assert(ot.type == TYPE_INT);
    if (ot.is_lua) {
        // return using lua script
    } else {
        return ot.data.i;
    }
}

// see custom_types.h
char* str_t_get(obj_t ot) {
    assert(ot.type == TYPE_STR);
    if (ot.is_lua) {
        // return using lua script
    } else {
        return ot.data.s;
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