/* 
 * Basic functions and structs for ast blocks to be used 
 * in custom-actions implementation. 
 * 
 * Please see "ast_block.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h" 
#include "ast_block.h"

/* See ast_block.h */
AST_block_t* AST_block_new(block_type_t block_type, AST_block_t *next)
{
    AST_block_t *ast;
    int new_ast;

    ast = malloc(sizeof(AST_block_t));

    if (ast == NULL) 
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    new_ast = AST_block_init(ast, block_type, next);
    if (new_ast != SUCCESS)
    {
        fprintf(stderr, "Could not initialize AST_block_t");
        return NULL;
    }

    return ast; 
}

/* See ast_block.h */
int AST_block_init(AST_block_t *ast, block_type_t block_type, AST_block_t *next)
{
    assert(ast != NULL); 

    ast->block_type = block_type;
    switch(ast->block_type)
    {
        case control_block: control_block_new(
    return SUCCESS; 
}

/* See ast_block.h */
int AST_block_free(AST_block_t *ast)
{
    assert(ast != NULL);

    free(ast);

    return SUCCESS;  
}

