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
AST_block_t* AST_block_new(block_t *block, block_type_t block_type, int num_AST, 
                           AST_block_t **next)
{
    AST_block_t *ast = malloc(sizeof(AST_block_t));
    int new_ast;

    if (ast == NULL) 
    {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    new_ast = AST_block_init(ast, block, block_type, num_AST, *next);
    if (new_ast != SUCCESS)
    {
        fprintf(stderr, "Could not initialize AST_block_t");
        return NULL;
    }

    return ast; 
}

/* See ast_block.h */
int AST_block_init(AST_block_t *ast, block_t *block, block_type_t block_type,
                   int num_AST, AST_block_t **next)
{
    assert(ast != NULL); 
    assert(block != NULL);
    assert(num_AST > 0);
 
    ast->block = block;
    ast->block_type = block_type;
    ast->num_AST = num_AST;
    ast->next = *next;

    return SUCCESS; 
}

/* See ast_block.h */
int AST_block_free(AST_block_t *ast)
{
    assert(ast != NULL);
    switch(ast->block_type) 
    {
        case CONTROL: 
            if (ast->block->control_block != NULL) 
            {
                control_block_free(ast->block->control_block);
            }
            break;
        case ACTION:
            if (ast->block->action_block != NULL)
            {
                action_block_free(ast->block->action_block);
            }
            break;
        case CONDITIONAL:
            if (ast->block->conditional_block != NULL)
            {
                conditional_block_free(ast->block->conditional_block);
            }
            break; 
        case BRANCH:
            if (ast->block->branch_block != NULL)
            {
                branch_block_free(ast->block->branch_block);
            }
    }
    if (ast->num_AST > 1) {
        for (int n = 0; n < ast->num_AST - 1; n++) {
            AST_block_free(ast->next[n]);
        }
    }
    free(ast);

    return SUCCESS;  
}
