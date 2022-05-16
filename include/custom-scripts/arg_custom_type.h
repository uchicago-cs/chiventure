#ifndef _ARG_CUSTOM_TYPE_H_
#define _ARG_CUSTOM_TYPE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
#include "utlist/src/utlist.h"

/* File consisting of the custom pseudo-type created by Custom Scripts (inspired by libobj)
   =========================================================================== */

typedef enum data_type
{
    NONE_TYPE = 0,
    BOOL_TYPE = 1,
    CHAR_TYPE = 2,
    INT_TYPE = 3,
    STR_TYPE = 4,
} data_type_t;

union {
    bool b;
    char c;
    int  i;
    char *s;
} data_t;

typedef struct arg_t
{
    // Type of underlying data
    data_type_t type;

    // Data associated with the argument
    data_t data;

    // Pointer to the previous and next arguments
    struct arg_t *prev, *next;
} arg_t;

/**
 * Creates an empty argument structure
 * Helper function for adding arguments to an object
 */
arg_t *arg_t_new();

/**
 * Creates an argument structure with the specified boolean
 * Helper function for obj_add_arg_bool
 */
arg_t *arg_t_init(data_t d, data_type_t t);

/**
 * Adds an argument structure to the end of the argument linked list
 * Helper function for all obj_add_arg_<type> functions
 */
arg_t *arg_t_add(arg_t *head, arg_t *add);

#endif