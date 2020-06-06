#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast_block.h"
#include "control_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "branch_block.h"

/* Checks that a new AST block with control type is created without interruption */
Test(AST_block_t, new_CONTROL)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONTROL;
    int num_AST = 1;
    AST_block_t** next;
    
    AST_block_t* new_ast = AST_block_new(block, block_type, num_AST, next);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");
    cr_assert_eq(new_ast->num_AST, num_AST, "AST_block_new() didn't set new_ast->num_AST");
    cr_assert_eq(new_ast->next, next, "AST_block_new() didn't set new_ast->next");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST block with branch type is created without interruption */
Test(AST_block_t, new_BRANCH)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = BRANCH;
    block_type_t block_type2 = CONDITIONAL;
    int num_AST = 2;
    int num_AST2 = 1;
    AST_block_t** test;
    AST_block_t* next = AST_block_new(block, block_type2, num_AST2, test);
    
    AST_block_t* new_ast = AST_block_new(block, block_type, num_AST, &next);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");
    cr_assert_eq(new_ast->num_AST, num_AST, "AST_block_new() didn't set new_ast->num_AST");
    cr_assert_eq(*(new_ast->next), next, "AST_block_new() didn't set new_ast->next");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST block with action type is created without interruption */
Test(AST_block_t, new_ACTION)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = ACTION;
    block_type_t block_type2 = CONDITIONAL;
    int num_AST = 2;
    int num_AST2 = 1;
    AST_block_t** test;
    AST_block_t** next = AST_block_new(block, block_type2, num_AST2, test);
    
    AST_block_t* new_ast = AST_block_new(block, block_type, num_AST, &next);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");
    cr_assert_eq(new_ast->num_AST, num_AST, "AST_block_new() didn't set new_ast->num_AST");
    cr_assert_eq(*(new_ast->next), *next, "AST_block_new() didn't set new_ast->next");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST block with conditional type is created without interruption */
Test(AST_block_t, new_CONDITIONAL)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONDITIONAL;
    block_type_t block_type2 = CONDITIONAL;
    int num_AST = 2;
    int num_AST2 = 1;
    AST_block_t** test;
    AST_block_t** next = AST_block_new(block, block_type2, num_AST2, test);
    
    AST_block_t* new_ast = AST_block_new(block, block_type, num_AST, &next);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");
    cr_assert_eq(new_ast->num_AST, num_AST, "AST_block_new() didn't set new_ast->num_AST");
    cr_assert_eq(*(new_ast->next), *next, "AST_block_new() didn't set new_ast->next");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST block with control type is initialized without interruption */
Test(AST_block_t, init_CONTROL)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONTROL;
    int num_AST = 1;
    AST_block_t **next;

    rc = AST_block_init(&ast, block, block_type, num_AST, next);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with branch type is initialized without interruption */
Test(AST_block_t, init_BRANCH)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = BRANCH;
    int num_AST = 1;
    AST_block_t **next;

    rc = AST_block_init(&ast, block, block_type, num_AST, next);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with action type is initialized without interruption */
Test(AST_block_t, init_ACTION)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = ACTION;
    int num_AST = 1;
    AST_block_t **next;

    rc = AST_block_init(&ast, block, block_type, num_AST, next);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with conditional type is initialized without interruption */
Test(AST_block_t, init_CONDITIONAL)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONDITIONAL;
    int num_AST = 1;
    AST_block_t **next;

    rc = AST_block_init(&ast, block, block_type, num_AST, next);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with control type is freed without interruption */
Test(AST_block_t, free_CONTROL)
{
    AST_block_t* ast;
    int rc;
    block_type_t block_type = CONTROL;
    block_t *block = malloc(sizeof(block_t));
    int num_AST = 1;
    AST_block_t **next;
    
    ast = AST_block_new(block, block_type, num_AST, next);

    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with branch type is freed without interruption */
Test(AST_block_t, free_BRANCH)
{
    AST_block_t* ast;
    int rc;
    block_type_t block_type = BRANCH;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type2 = CONDITIONAL;
    int num_AST = 2;
    int num_AST2 = 1;
    AST_block_t* test;
    AST_block_t* next = AST_block_new(block, block_type2, num_AST2, &test);
    
    ast = AST_block_new(block, block_type, num_AST, &next);

    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with action type is freed without interruption */
Test(AST_block_t, free_ACTION)
{
    AST_block_t* ast;
    int rc;
    block_type_t block_type = ACTION;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type2 = CONDITIONAL;
    int num_AST = 2;
    int num_AST2 = 1;
    AST_block_t* test;
    AST_block_t* next = AST_block_new(block, block_type2, num_AST2, &test);
    
    ast = AST_block_new(block, block_type, num_AST, &next);

    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with conditional type is freed without interruption */
Test(AST_block_t, free_CONDITIONAL)
{
    AST_block_t* ast;
    int rc;
    block_type_t block_type = CONDITIONAL;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type2 = CONDITIONAL;
    int num_AST = 2;
    int num_AST2 = 1;
    AST_block_t* test;
    AST_block_t* next = AST_block_new(block, block_type2, num_AST2, &test);
    
    ast = AST_block_new(block, block_type, num_AST, &next);
    
    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}
