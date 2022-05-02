#include "custom-scripts/obj_custom_type.h"
#include "arg_custom_types.c"

// see obj_custom_type.h
object_t *obj_t_new()
{
    object_t *ot = (object_t*)malloc(sizeof(object_t));
    ot->type = NONE_TYPE;
    ot->is_lua = false;
    ot->args = NULL;
    return ot;
}

// see obj_custom_type.h
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

// see obj_custom_type.h
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

// see obj_custom_type.h
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

// see obj_custom_type.h
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

// see obj_custom_type.h
object_t *obj_add_arg_bool(object_t *ot, bool b) {
    arg_t *add = arg_t_bool(b);
    ot->args = arg_t_add(ot->args, add);
    return ot;
}

// see obj_custom_type.h
object_t *obj_add_arg_char(object_t *ot, char c) {
    arg_t *add = arg_t_char(c);
    ot->args = arg_t_add(ot->args, add);
    return ot;
}

// see obj_custom_type.h
object_t *obj_add_arg_int(object_t *ot, int i) {
    arg_t *add = arg_t_int(i);
    ot->args = arg_t_add(ot->args, add);
    return ot;
}

// see obj_custom_type.h
object_t *obj_add_arg_str(object_t *ot, char *s) {
    arg_t *add = arg_t_str(s);
    ot->args = arg_t_add(ot->args, add);
    return ot;
}