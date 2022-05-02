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
arg_t *arg_t_bool(bool b) {
    arg_t *arg = arg_t_new();
    arg->type = BOOL_TYPE;
    arg->data.b = b;
    return arg;
}

// see arg_custom_type.h
arg_t *arg_t_char(char c) {
    arg_t *arg = arg_t_new();
    arg->type = CHAR_TYPE;
    arg->data.c = c;
    return arg;
}

// see arg_custom_type.h
arg_t *arg_t_int(int i) {
    arg_t *arg = arg_t_new();
    arg->type = INT_TYPE;
    arg->data.i = i;
    return arg;
}

// see arg_custom_type.h
arg_t *arg_t_str(char *s) {
    arg_t *arg = arg_t_new();
    arg->type = STR_TYPE;
    arg->data.s = s;
    return arg;
}

// see arg_custom_type.h
arg_t *arg_t_add(arg_t *head, arg_t *add) {
    if (add == NULL) {
        return head;
    } else if (head == NULL) {
        return add;
    } else {
        arg_t *temp = head;
        // iterating over linked list to last node
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = add;
        temp->next->prev = temp;
        return head;
    }
}