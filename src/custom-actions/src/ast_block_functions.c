/* 
 * Basic functions for ast blocks to be used in custom-actions implementation. 
 * 
 * Please see "ast_block_functions.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "custom-actions/struct.h"
#include "game-state/item.h" 
#include "custom-actions/ast_block_functions.h"

/* See ast_block_functions.h */
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

/* See ast_block_functions.h */
int AST_block_init(AST_block_t *ast, block_t block, enum block_type block_type)
{
    assert(ast != NULL);
    assert(block != NULL);
    assert(block_type != NULL);

    ast->block = block;
    ast->block_type = block_type;

    return SUCCESS; 
}

/* See ast_block_functions.h */
int AST_block_free(AST_block_t *ast)
{
    assert(ast != NULL);

    free(ast);

    return SUCCESS;  
}

