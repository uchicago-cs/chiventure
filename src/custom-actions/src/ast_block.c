/* 
 * Basic functions and structs for ast blocks to be used 
 * in custom-actions implementation. 
 * 
 * Please see "ast_block.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h" 
#include "../include/ast_block.h"
#include "../include/action_block.h"
#include "../include/branch_block.h"
#include "../include/conditional_block.h"
#include "../include/control_block.h"

/* See ast_block.h */
typedef union block {
    control_block_t *control_block;
    branch_block_t *branch_block;
    action_block_t *action_block;
    conditional_block_t *conditional_block;
} block_t;

/* See ast_block.h */
typedef struct AST_block {
    block_t block;
    enum block_type block_type;
} AST_block_t;

/* See ast_block.h */
AST_block_t* AST_block_new(block_t block, enum block_type block_type)
{
    AST_block_t *ast;
    int new_ast;

    ast = malloc(sizeof(AST_block_t));

    if (ast == NULL) 
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    new_ast = AST_block_init(ast, block, block_type);
    if (new_ast != SUCCESS)
    {
        fprintf(stderr, "Could not initialize AST_block_t");
        return NULL;
    }

    return ast; 
}

/* See ast_block.h */
int AST_block_init(AST_block_t *ast, block_t block, enum block_type block_type)
{
    assert(ast != NULL);
//    assert(block != NULL);
//    assert(block_type != NULL);

    ast->block = block;
    ast->block_type = block_type;

    return SUCCESS; 
}

/* See ast_block.h */
int AST_block_free(AST_block_t *ast)
{
    assert(ast != NULL);

    free(ast);

    return SUCCESS;  
}

