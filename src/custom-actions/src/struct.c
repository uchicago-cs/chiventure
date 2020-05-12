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
    return NULL;
}

/* See struct.h */
int AST_block_init(AST_block_t *ast, block_t block, enum block_type block_type)
{
    return 0;
}

/* See struct.h */
int AST_block_free(AST_block_t *ast)
{
    return 0;
}

/* See struct.h */
control_block_t* control_block_new(enum control_type control_type, AST_block *next)
{
    return NULL;
}

/* See struct.h */
int control_block_init(control_block_t *control, enum control_type control_type,
AST_block *next)
{
    return 0;
}

/* See struct.h */
int control_block_free(control_block_t *control)
{
    return 0;
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
 
