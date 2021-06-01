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
AST_block_t* AST_block_new(block_t *block, block_type_t block_type)
{
    AST_block_t *ast = malloc(sizeof(AST_block_t));
    int new_ast;

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
int AST_block_init(AST_block_t *ast, block_t *block, block_type_t block_type)
{
    assert(ast != NULL); 
    assert(block != NULL);
 
    ast->block = block;
    ast->block_type = block_type;
    ast->next = NULL;

    return SUCCESS; 
}

/* See ast_block.h */
int AST_free(AST_block_t* ast)
{
    assert(ast != NULL);

    if (ast->block != NULL)
    {
        switch(ast->block_type) 
        {
            case CONTROL: 
                if (ast->block->control_block != NULL) 
                {
                    control_block_free(ast->block->control_block);
                    ast->block->control_block == NULL;
                }
                free(ast->block);
                ast->block == NULL;
                break;
            case ACTION:
                if (ast->block->action_block != NULL)
                {
                    action_block_free(ast->block->action_block);
                    ast->block->action_block == NULL;
                }
                free(ast->block);
                ast->block == NULL;
                break;
            case CONDITIONAL:
                if (ast->block->conditional_block != NULL)
                {
                    conditional_block_free(ast->block->conditional_block);
                }
                free(ast->block);
                ast->block == NULL;
                break; 
            case BRANCH:
                if (ast->block->branch_block != NULL)
                {
                    branch_block_free(ast->block->branch_block);
                }
                free(ast->block);
                ast->block == NULL;
        }
    }

    free(ast);

    return SUCCESS;
}

/* See ast_block.h */
int AST_block_free(AST_block_t *ast)
{
    assert(ast != NULL);

    AST_block_t *elt, *tmp;
    LL_FOREACH_SAFE(ast, elt, tmp)
    {
        LL_DELETE(ast, elt);
	    AST_free(elt);
    }

    return SUCCESS;  
}

//---------------To add List Functionality for AST_blocks----------------------

/* See ast_block.h */
int list_how_many_AST_block(AST_block_t* head)
{
    assert(head != NULL);

    int count;
    AST_block_t* elt = malloc(sizeof(AST_block_t));
    LL_COUNT(head, elt, ret_val);
    free(elt);
    return count;
}

/* See ast_block.h */
int append_list_AST_block(AST_block_t* head, AST_block_t* add)
{
    assert(head != NULL);
    LL_APPEND(head, add);
    return SUCCESS;
}

/* See ast_block.h */
int prepend_list_AST_block(AST_block_t* head, AST_block_t* add)
{
    assert(head != NULL);
    LL_PREPEND(head, add);
    return SUCCESS;
}

/* See ast_block.h */
int list_remove_AST_block(AST_block_t* head, AST_block_t* del)
{
    assert(head != NULL);
    assert(del != NULL);
    
    LL_DELETE(head, del);

    /* Set 'next' pointer to NULL do avoid recursive freeing from AST_block_free */
    del->next = NULL;
    AST_block_free(del);
    
    return SUCCESS;
}
