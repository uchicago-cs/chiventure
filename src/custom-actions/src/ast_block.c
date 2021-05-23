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
int AST_block_free(AST_block_t *ast)
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

    if (ast->next != NULL) 
    {
        AST_block_free(ast->next);
    }

    free(ast);

    return SUCCESS;  
}

//---------------To add List Functionality for AST_blocks----------------------

/* AST_cmp: Helper function that takes two AST_blocks and compares if they are 
 *          the same
 *
 * Parameters:
 *          - AST1: Pointer to one AST_block
 *          - AST2: Pointer to a seperate AST_block
 *
 * Returns:
 *          - 2 possible int value: 0 for when AST_blocks are the same
 *                                  1 otherwise
 * Note: The value for same MUST be 0 for this helper to be successfully used 
 *       in LL_<function>
 */
int AST_cmp(AST_block_t* AST1, AST_block_t* AST2)
{
    if (AST1 == AST2)
        return 0;
    else return 1;
}

/* See ast_block.h */
int list_how_many_AST_block(AST_block_t* head)
{
    assert(head != NULL);

    int ret_val = 1;
    AST_block_t* curr = head;

    while(curr->next != NULL)
    {
        ret_val += 1;
        curr = curr->next;
    }
    
    return ret_val;
}

/* See ast_block.h */
bool list_contains_AST_block(AST_block_t* head, AST_block_t* compare)
{
    if (head == NULL || compare == NULL)
    {
        return false;
    }

    AST_block_t* tmp;
    
    LL_SEARCH(head, tmp, compare, AST_cmp);

    if (tmp)
        return true;
    else return false;
}

/* See ast_block.h */
int list_add_AST_block(AST_block_t* head, AST_block_t* add, int num_to_place)
{
    if (head == NULL || add == NULL || num_to_place < 0)
        return FAILURE;

    if (list_contains_AST_block(head, add) == true)
        return FAILURE;
        
    /* Case where adding an AST_block_t as the new 'head'/beginning of the linked list */
    if (num_to_place == 0)
    {
        LL_PREPEND(head, add);
        return SUCCESS;
    }

    /* Case where adding an AST_block_t as the 'tail'/end of the linked list */
    if (num_to_place >= list_how_many_AST_block(head))
    {
        LL_APPEND(head, add);
        return SUCCESS;
    }

    /* General case where adding an AST_block_t somewhere within linked list */
    AST_block_t* curr = head;
    AST_block_t* prev;

    /* Get to the place in linked list specified by num_to_place */
    for (int i = 0; i < num_to_place; i++)
    {
        prev = curr;
        curr = curr->next;
    }

    /* Move Pointers around to accomodate new AST_block */
    add->next = curr;

    prev->next = add;

    return SUCCESS;
}

/* See ast_block.h */
int append_list_AST_block(AST_block_t* head, AST_block_t* add)
{
  return list_add_AST_block(head, add, list_how_many_AST_block(head));
}

/* See ast_block.h */
int prepend_list_AST_block(AST_block_t* head, AST_block_t* add)
{
  return list_add_AST_block(head, add, 0);
}

/* See ast_block.h */
int list_remove_AST_block(AST_block_t* head, AST_block_t* del)
{
    assert(head != NULL);
    assert(del != NULL);

    if (list_contains_AST_block(head, del) == false)
        return FAILURE;

    AST_block_t *elt, *tmp;
    LL_FOREACH_SAFE(head, elt, tmp)
    {
        if (AST_cmp(elt, del) == 0)
        {
            LL_DELETE(head, elt);
            
            /* Set 'next' pointer to NULL do avoid recursive freeing from AST_block_free */
            elt->next = NULL;
            AST_block_free(elt);
        }
    }

    return SUCCESS;
}
