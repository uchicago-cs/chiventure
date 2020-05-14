/* 
 * Basic functions for structs to be used in custom-actions implementation. 
 * 
 * Please see "struct.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "item.h" 

/* See struct.h */
AST_block_t* AST_block_new(block_t block, enum block_type block_type)
{
    AST_block_t *ast;
    int new_ast;

    ast = malloc(sizeof(AST_block_t));

    if (ast == NULL) 
    {
        error("Could not allocate memory");
        return NULL;
    }

    new_ast = AST_block_init(ast, block, block_type);
    if (new_ast != SUCCESS)
    {
        error("Could not initialize AST_block_t");
        return NULL;
    }

    return ast; 
}

/* See struct.h */
int AST_block_init(AST_block_t *ast, block_t block, enum block_type block_type)
{
    assert(ast != NULL);
    assert(block != NULL);
    assert(block_type != NULL);

    ast->block = block;
    ast->block_type = block_type;

    return SUCCESS; 
}

/* See struct.h */
int AST_block_free(AST_block_t *ast)
{
    assert(ast != NULL);

    free(ast);

    return SUCCESS;  
}

/* See struct.h */
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

/* See struct.h */
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

/* See struct.h */
int control_block_free(control_block_t *control)
{
    assert(control != NULL);

    free(control);

    return SUCCESS; 
}

/* See struct.h */
branch_block_t* branch_block_new(int num_conditionals, conditional_block_t** 
conditionals, enum conditional_union_type conditional_union_type, int num_controls, 
control_block_t** controls)
{
    return NULL;
}

/* See struct.h */
int branch_block_init(branch_block_t *branch, int num_conditionals, conditional_block_t**
conditionals, enum conditional_union_type conditional_union_type, int num_controls,
control_block_t** controls)
{
    return 0;
}

/* See struct.h */
int branch_block_free(branch_block_t *branch)
{
    return 0;
}

/* See struct.h */
action_block_t* action_block_new(enum action_type action_type, int num_args, 
attribute_t** args, AST_block *next)
{
    return NULL;
}

/* See struct.h */
int action_block_init(action_block_t *action, enum action_type action_type, int num_args, 
attribute_t** args, AST_block *next)
{
    return 0;
}

/* See struct.h */
int action_block_free(action_block_t *branch)
{
    return 0;
}

/* See struct.h */
conditional_block_t* conditional_block_new(enum conditional_type conditional_type, 
attribute_t* left, attribute_t* right)
{
    return NULL;
}

/* See struct.h */
int conditional_block_init(conditional_block_t *conditional, enum conditional_type 
conditional_type, attribute_t* left, attribute_t* right)
{
    return 0;
}

/* See struct.h */
int conditional_block_free(conditional_block_t *conditional)
{
    return 0;
}

/* See struct.h */
attribute_t* attribute_new(attribute_value_t value, enum attribute_type 
attribute_type, char *name)
{
    return NULL;
}

/* See struct.h */
int attribute_init(attribute_t *attribute, attribute_value_t value, enum                  
attribute_type attribute_type, char *name)
{
    return 0;
}
 
