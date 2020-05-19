/* 
 * Basic functions for control blocks to be used in custom-actions implementation. 
 * 
 * Please see "control_block_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/struct.h"
#include "game-state/item.h"
#include "custom-actions/control_block_functions.h"

/* See control_block_functions.h */
control_block_t* control_block_new(enum control_type control_type, AST_block *next)
{
    control_block_t *control;
    int new_control;

    control = malloc(sizeof(control_block_t));

    if (control == NULL) 
    {
        error("Could not allocate memory");
        return NULL;
    }

    new_control = control_block_init(control, control_type, next);
    if (new_control != SUCCESS)
    {
        error("Could not intialize control_block_t");
        return NULL;
    }

    return control;  
}

/* See control_block_functions.h */
int control_block_init(control_block_t *control, enum control_type control_type,
AST_block *next)
{
    assert(control != NULL);
    assert(control_type != NULL);
    assert(next != NULL);

    control->control_type = control_type;
    control->next = next;

    return SUCCESS; 
}

/* See control_block_functions.h */
int control_block_free(control_block_t *control)
{
    assert(control != NULL);

    free(control);

    return SUCCESS; 
} 
