#include "custom-scripts/obj_custom_type.h"

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
object_t *obj_t_init(data_t d, data_type_t t, char *lua)
{
    object_t *ot = obj_t_new();
    ot->type = t;
    if (lua) {
        ot->is_lua = true;
        ot->data.lua = lua;
    } else {
        ot->data = d;
    }
    return ot;
}

// see obj_custom_type.h
object_t *obj_add_arg(object_t *ot, data_t d, data_type_t t) {
    arg_t *add = arg_t_init(d, t);
    ot->args = arg_t_add(ot->args, add);
    return ot;
}