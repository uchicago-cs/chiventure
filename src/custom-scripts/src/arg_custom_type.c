#include "custom-scripts/arg_custom_type.h"

// see arg_custom_type.h
arg_t *arg_t_new() {
    arg_t *arg = (arg_t*)malloc(sizeof(arg_t));
    arg->type = NONE_TYPE;
    arg->prev = NULL;
    arg->next = NULL;
    return arg;
}

// see arg_custom_type.h
arg_t *arg_t_init(data_t d, data_type_t t) {
    arg_t *arg = arg_t_new();
    arg->type = t;

    switch (t) {
    case BOOL_TYPE:
        arg->data.b = d.b;
        break;
    case CHAR_TYPE:
        arg->data.c = d.c;
        break;
    case INT_TYPE:
        arg->data.i = d.i;
        break;
    case STR_TYPE:
        arg->data.s = d.s;
        break;
    default:  
        break;
    }
    return arg;
}

// see arg_custom_type.h
arg_t *arg_t_add(arg_t *head, arg_t *add) {
    DL_APPEND(head, add);
    return head;
}