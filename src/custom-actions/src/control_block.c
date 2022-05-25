/* 
 * Basic functions and structs for control blocks 
 * to be used in custom-actions implementation. 
 * 
 * Please see "control_block.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "ast_block.h"
#include "control_block.h"

/* See control_block.h */
control_block_t* control_block_new(control_type_t control_type)
{
    control_block_t *control;
    int new_control;
    block_type_t block_type = CONTROL;

    control = malloc(sizeof(control_block_t));

    if (control == NULL) 
    {
        fprintf(stderr,"Could not allocate memory");
        return NULL;
    }

    new_control = control_block_init(control, control_type);
    if (new_control != SUCCESS)
    {
        fprintf(stderr,"Could not intialize control_block_t");
        return NULL;
    }

    return control;
}

/* See control_block.h */
AST_block_t* AST_control_block_new(control_type_t control_type)
{
    AST_block_t *ast;
    control_block_t *control;
    int new_control;
    block_type_t block_type = CONTROL;
  
    control = malloc(sizeof(control_block_t));
    ast = malloc(sizeof(AST_block_t));

    if (control == NULL) 
    {
        fprintf(stderr,"Could not allocate memory");
        return NULL;
    }

    new_control = control_block_init(control, control_type);
    if (new_control != SUCCESS)
    {
        fprintf(stderr,"Could not intialize control_block_t");
        return NULL;
    }

    block_t *block = malloc(sizeof(block));
    block->control_block = control;
    ast = AST_block_new(block, block_type);
    return ast;
}

/* See control_block.h */
int control_block_init(control_block_t *control, control_type_t control_type)
{
    assert(control != NULL); 

    control->control_type = control_type;

    return SUCCESS; 
}

/* See control_block.h */
int control_block_free(control_block_t *control)
{
    assert(control != NULL);

    free(control);

    return SUCCESS; 
} 
