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
    
    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST block with branch type is created without interruption */
Test(AST_block_t, new_BRANCH)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = BRANCH;
    
    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST block with action type is created without interruption */
Test(AST_block_t, new_ACTION)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = ACTION;
     
    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with conditional type is created without interruption */
Test(AST_block_t, new_CONDITIONAL)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONDITIONAL;
      
    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with control type is initialized without interruption */
Test(AST_block_t, init_CONTROL)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONTROL;

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
    cr_assert_null(ast.next, "AST_block_init() failed");
}

/* Checks that a new AST block with branch type is initialized without interruption */
Test(AST_block_t, init_BRANCH)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = BRANCH;
   
    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
    cr_assert_null(ast.next, "AST_block_init() failed");
}

/* Checks that a new AST block with action type is initialized without interruption */
Test(AST_block_t, init_ACTION)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = ACTION;
    
    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
    cr_assert_null(ast.next, "AST_block_init() failed");
}

/* Checks that a new AST block with conditional type is initialized without interruption */
Test(AST_block_t, init_CONDITIONAL)
{
    AST_block_t ast;
    int rc;
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONDITIONAL;
    
    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
    cr_assert_null(ast.next, "AST_block_init() failed");
}

/* Tests that the correct number of AST_block_t was returned in linked list */
Test(AST_block_t, list_how_many_AST_block)
{
    int ret_val;

    /* Create 3 AST_blocks and link them together according to name (manual) */
    block_t *block = malloc(sizeof(control_block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* new_ast = AST_block_new(block, block_type);
    cr_assert_not_null(new_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(branch_block_t));
    block_type_t second_block_type = BRANCH;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    block_t *act = malloc(sizeof(action_block_t));
    block_type_t third_block_type = ACTION;
     
    AST_block_t* third_ast = AST_block_new(act, third_block_type);
    cr_assert_not_null(third_ast, "AST_block_new failed to create the third AST_block");

    new_ast->next = second_ast;
    second_ast->next = third_ast;
    third_ast->next = NULL;

    /* Check to see how many AST_block_t are linked together */
    ret_val = list_how_many_AST_block(new_ast);
    cr_assert_eq(ret_val, 3, "list_how_many_AST_block did not return correct value of only 3 AST blocks linked");

    AST_block_free(new_ast);
}

/* Tests that a specific type of block_type was found in linked list */
Test(AST_block_t, list_contains_AST_block)
{
    bool ret_val;

    /* Create two seperate AST_blocks and link them together */

    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* new_ast = AST_block_new(block, block_type);
    cr_assert_not_null(new_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(block_t));
    block_type_t second_block_type = BRANCH;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    new_ast->next = second_ast;

    /* Check whether or not CONTROL is found in linked list*/
    ret_val = list_contains_AST_block(new_ast, block_type);
    cr_assert_eq(ret_val, true, "list_contains_AST_block failed to find CONTROL block type");

    /* Check whether or not BRANCH is found in linked list */
    ret_val = list_contains_AST_block(new_ast, second_block_type);
    cr_assert_eq(ret_val, true, "list_contains_AST_block failed to find BRANCH block type");

    AST_block_free(new_ast);  
}

/* Check that we can successfully add an AST_block_t in specified location */
Test(AST_block_t, list_add_AST_block)
{
    int ret_val;
    bool ret_bool;

    /* Create 3 AST_blocks and link them together according to name (manual) */
    block_t *block = malloc(sizeof(control_block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* new_ast = AST_block_new(block, block_type);
    cr_assert_not_null(new_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(branch_block_t));
    block_type_t second_block_type = BRANCH;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    block_t *act = malloc(sizeof(action_block_t));
    block_type_t third_block_type = ACTION;
     
    AST_block_t* third_ast = AST_block_new(act, third_block_type);
    cr_assert_not_null(third_ast, "AST_block_new failed to create the third AST_block");

    new_ast->next = second_ast;
    second_ast->next = third_ast;
    third_ast->next = NULL;

    /* Create another AST_block that will be places as the second place in linked list */
    block_t *cond = malloc(sizeof(block_t));
    block_type_t new_second_block_type = CONDITIONAL;
      
    AST_block_t* new_second_ast = AST_block_new(cond, new_second_block_type);
    cr_assert_not_null(new_second_ast, "AST_block_new failed to create the to-be new_second_AST_block");
    
    ret_bool = list_contains_AST_block(new_ast, new_second_block_type);
    cr_assert_eq(ret_bool, false, "list_contains_AST_block found CONDITIONAL before being added");

    ret_val = list_add_AST_block(new_ast, new_second_ast, 1);
    cr_assert_eq(ret_val, SUCCESS, "list_add_AST_block returned FAILURE upon trying to add in second place");

    ret_bool = list_contains_AST_block(new_ast, new_second_block_type);
    cr_assert_eq(ret_bool, true, "list_contains_AST_block could not find CONDITIONAL after being added");

    if (new_ast->next != new_second_ast)
        cr_assert_fail("new_ast second element failed to be set to new_second_ast");
    if (new_second_ast->next != second_ast)
        cr_assert_fail("list_add_AST_block failed to set 'next' pointer of added element");
    if (second_ast->next != third_ast)
        cr_assert_fail("list_add_AST_block unintentionally messed with pointer that shouldn't have been");

    AST_block_free(new_ast);
}

/* Check that we can successfully add an AST_block_t as the start location */
Test(AST_block_t, prepend_list_ast)
{
    int ret_val;
    bool ret_bool;

    /* Create 3 AST_blocks and link them together according to name (manual) */
    block_t *block = malloc(sizeof(control_block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* first_ast = AST_block_new(block, block_type);
    cr_assert_not_null(first_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(branch_block_t));
    block_type_t second_block_type = BRANCH;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    block_t *act = malloc(sizeof(action_block_t));
    block_type_t third_block_type = ACTION;
     
    AST_block_t* third_ast = AST_block_new(act, third_block_type);
    cr_assert_not_null(third_ast, "AST_block_new failed to create the third AST_block");

    first_ast->next = second_ast;
    second_ast->next = third_ast;
    third_ast->next = NULL;

    /* Create another AST_block that will be places as the first place in linked list */
    block_t *cond = malloc(sizeof(block_t));
    block_type_t new_first_block_type = CONDITIONAL;
      
    AST_block_t* new_first_ast = AST_block_new(cond, new_first_block_type);
    cr_assert_not_null(new_first_ast, "AST_block_new failed to create the to-be new_first_AST_block");
    
    ret_bool = list_contains_AST_block(first_ast, new_first_block_type);
    cr_assert_eq(ret_bool, false, "list_contains_AST_block found CONDITIONAL before being added");

    ret_val = prepend_list_AST_block(first_ast, new_first_ast);
    cr_assert_eq(ret_val, SUCCESS, "list_add_AST_block returned FAILURE upon trying to add in first place");

    ret_bool = list_contains_AST_block(new_first_ast, new_first_block_type);
    cr_assert_eq(ret_bool, true, "list_contains_AST_block could not find CONDITIONAL after being added");

    if (new_first_ast->next != first_ast)
        cr_assert_fail("new_first_ast second element failed to be set to first_ast");
    if (first_ast->next != second_ast)
        cr_assert_fail("list_add_AST_block unintentionally messed with pointers that shouldn't have been");
    if (second_ast->next != third_ast)
        cr_assert_fail("list_add_AST_block unintentionally messed with pointer that shouldn't have been");

    AST_block_free(new_first_ast);
}

/* Check that we can successfully append an AST_block_t to a list of AST_block_t */
Test(AST_block_t, append_list_ast_block)
{
  int ret_val;
  bool ret_bool;

  /* Create 3 AST_blocks and link them together according to name (manual) */
  block_t *block = malloc(sizeof(control_block_t));
  block_type_t block_type = CONTROL;

  AST_block_t* first_ast = AST_block_new(block, block_type);
  cr_assert_not_null(first_ast, "AST_block_new failed to create a AST_block");

  block_t *brnc = malloc(sizeof(branch_block_t));
  block_type_t second_block_type = BRANCH;

  AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
  cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

  block_t *act = malloc(sizeof(action_block_t));
  block_type_t third_block_type = ACTION;

  AST_block_t* third_ast = AST_block_new(act, third_block_type);
  cr_assert_not_null(third_ast, "AST_block_new failed to create the third AST_block");

  first_ast->next = second_ast;
  second_ast->next = third_ast;
  third_ast->next = NULL;

  /* Create another AST_block that will be places as the last place in linked list */
  block_t *cond = malloc(sizeof(block_t));
  block_type_t new_end_block_type = CONDITIONAL;

  AST_block_t* new_end_ast = AST_block_new(cond, new_end_block_type);
  cr_assert_not_null(new_end_ast, "AST_block_new failed to create the to-be new_end_AST_block");

  ret_bool = list_contains_AST_block(first_ast, new_end_block_type);
  cr_assert_eq(ret_bool, false, "list_contains_AST_block found CONDITIONAL before being added");

  ret_val = append_list_AST_block(first_ast, new_end_ast);
  cr_assert_eq(ret_val, SUCCESS, "list_add_AST_block returned FAILURE upon trying to add in last place");

  ret_bool = list_contains_AST_block(first_ast, new_end_block_type);
  cr_assert_eq(ret_bool, true, "list_contains_AST_block could not find CONDITIONAL after being added");

  if (first_ast->next != second_ast)
    cr_assert_fail("list_add_AST_block unintentionally messed with pointers that shouldn't have been");
  if (second_ast->next != third_ast)
    cr_assert_fail("list_add_AST_block unintentionally messed with pointer that shouldn't have been");
  if (third_ast->next != new_end_ast)
    cr_assert_fail("list_add_AST_block did not set the pointer to the new last AST_block in list");

  AST_block_free(first_ast);
}

/* Check that we can successfully add an AST_block_t as 'tail'/end location */
Test(AST_block_t, list_add_AST_block_to_end)
{
    int ret_val;
    bool ret_bool;

    /* Create 3 AST_blocks and link them together according to name (manual) */
    block_t *block = malloc(sizeof(control_block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* first_ast = AST_block_new(block, block_type);
    cr_assert_not_null(first_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(branch_block_t));
    block_type_t second_block_type = BRANCH;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    block_t *act = malloc(sizeof(action_block_t));
    block_type_t third_block_type = ACTION;
     
    AST_block_t* third_ast = AST_block_new(act, third_block_type);
    cr_assert_not_null(third_ast, "AST_block_new failed to create the third AST_block");

    first_ast->next = second_ast;
    second_ast->next = third_ast;
    third_ast->next = NULL;

    /* Create another AST_block that will be places as the last place in linked list */
    block_t *cond = malloc(sizeof(block_t));
    block_type_t new_end_block_type = CONDITIONAL;
      
    AST_block_t* new_end_ast = AST_block_new(cond, new_end_block_type);
    cr_assert_not_null(new_end_ast, "AST_block_new failed to create the to-be new_end_AST_block");
    
    ret_bool = list_contains_AST_block(first_ast, new_end_block_type);
    cr_assert_eq(ret_bool, false, "list_contains_AST_block found CONDITIONAL before being added");

    ret_val = list_add_AST_block(first_ast, new_end_ast, 50);
    cr_assert_eq(ret_val, SUCCESS, "list_add_AST_block returned FAILURE upon trying to add in last place");

    ret_bool = list_contains_AST_block(first_ast, new_end_block_type);
    cr_assert_eq(ret_bool, true, "list_contains_AST_block could not find CONDITIONAL after being added");

    if (first_ast->next != second_ast)
        cr_assert_fail("list_add_AST_block unintentionally messed with pointers that shouldn't have been");
    if (second_ast->next != third_ast)
        cr_assert_fail("list_add_AST_block unintentionally messed with pointer that shouldn't have been");
    if (third_ast->next != new_end_ast)
        cr_assert_fail("list_add_AST_block did not set the pointer to the new last AST_block in list");

    AST_block_free(first_ast);
}

/* Checks that we can successfuly delete an item in an AST_block_t linked list */
Test(AST_block_t, list_remove_AST_block)
{
    int ret_val;
    bool ret_bool;

    /* Create 3 AST_blocks and link them together according to name (manual) */
    block_t *block = malloc(sizeof(control_block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* new_ast = AST_block_new(block, block_type);
    cr_assert_not_null(new_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(branch_block_t));
    block_type_t second_block_type = BRANCH;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    block_t *act = malloc(sizeof(action_block_t));
    block_type_t third_block_type = ACTION;
     
    AST_block_t* third_ast = AST_block_new(act, third_block_type);
    cr_assert_not_null(third_ast, "AST_block_new failed to create the third AST_block");

    new_ast->next = second_ast;
    second_ast->next = third_ast;
    third_ast->next = NULL;

    /* Delete second item from linked list */
    ret_val = list_remove_AST_block(new_ast, second_block_type);
    cr_assert_eq(ret_val, SUCCESS, "list_remove_AST_block failed in deleting second item in linked list");

    if (new_ast->next != third_ast)
        cr_assert_fail("list_remove_AST_block did not set pointer from first item to third item");
    if (!second_ast)
        cr_assert_fail("list_remove_AST_block did not free the second item from linked list");

    AST_block_free(new_ast);
}

/* Checks fail condition when deleting an AST_block_t */
Test(AST_block_t, list_remove_AST_block_failure)
{
    int ret_val;
    bool ret_bool;

    /* Create 3 AST_blocks and link them together according to name (manual) */
    block_t *block = malloc(sizeof(control_block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* new_ast = AST_block_new(block, block_type);
    cr_assert_not_null(new_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(branch_block_t));
    block_type_t second_block_type = BRANCH;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    block_t *act = malloc(sizeof(action_block_t));
    block_type_t third_block_type = ACTION;
     
    AST_block_t* third_ast = AST_block_new(act, third_block_type);
    cr_assert_not_null(third_ast, "AST_block_new failed to create the third AST_block");

    new_ast->next = second_ast;
    second_ast->next = third_ast;
    third_ast->next = NULL;

    block_type_t fail_block_type = CONDITIONAL;
    /* Delete second item from linked list */
    ret_val = list_remove_AST_block(new_ast, fail_block_type);
    cr_assert_eq(ret_val, FAILURE, "list_remove_AST_block failed in deleting second item in linked list");

    if (new_ast->next == third_ast)
        cr_assert_fail("list_remove_AST_block deleted second AST_block when shouldn't");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with control type is freed without interruption */
Test(AST_block_t, free_CONTROL)
{
    AST_block_t* ast;
    int rc;
    block_type_t block_type = CONTROL;
    block_t *block = malloc(sizeof(block_t));
    
    ast = AST_block_new(block, block_type);

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
    
    ast = AST_block_new(block, block_type);

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
    
    ast = AST_block_new(block, block_type);

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
    
    ast = AST_block_new(block, block_type);
    
    cr_assert_not_null(ast, "AST_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}
