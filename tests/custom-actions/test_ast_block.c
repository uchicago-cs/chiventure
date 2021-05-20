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
    cr_assert_null(ast.prev, "AST_block_init() failed");
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
    cr_assert_null(ast.prev, "AST_block_init() failed");
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
    cr_assert_null(ast.prev, "AST_block_init() failed");
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
    cr_assert_null(ast.prev, "AST_block_init() failed");
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


/* Checks that run AST block functions correctly for action blocks */
Test(AST_block_t, run_block_action)
{
  attribute_t *attr1, *attr2;
  attribute_value_t val1, val2;
  char *attr_name = "attr";
  attr1 = malloc(sizeof(attribute_t));
  attr1->attribute_key = strdup(attr_name);
  attr1->attribute_tag = INTEGER;
  val1.int_val = 5;
  attr1->attribute_value = val1;

  attr2 = malloc(sizeof(attribute_t));
  attr2->attribute_key = strdup(attr_name);
  attr2->attribute_tag = INTEGER;
  val2.int_val = 10;
  attr2->attribute_value = val2;

  attribute_t **args = (attribute_t**) malloc(sizeof(attribute_t*) * 2);
  args[0] = attr1;
  args[1] = attr2;

  
  AST_block_t* new_ast = AST_action_block_new(SET, 2, args);

  cr_assert_not_null(new_ast, "AST_block_new failed");

  int rc = run_ast_block(new_ast);

  cr_assert_eq(rc, SUCCESS, "run_ast_block failed");

  cr_assert_eq(attr1->attribute_value.int_val, 10, "Run command failed to properly run an AST action block");

  attribute_free(attr1);
  attribute_free(attr2);
  AST_block_free(new_ast);
}


/* Checks running an AST conditional block */
Test(AST_block_t, run_block_conditional)
{
  attribute_t *attr1, *attr2;
  attribute_value_t val1, val2;
  char *attr_name = "attr";
  attr1 = malloc(sizeof(attribute_t));
  attr1->attribute_key = strdup(attr_name);
  attr1->attribute_tag = INTEGER;
  val1.int_val = 5;
  attr1->attribute_value = val1;

  attr2 = malloc(sizeof(attribute_t));
  attr2->attribute_key = strdup(attr_name);
  attr2->attribute_tag = INTEGER;
  val2.int_val = 10;
  attr2->attribute_value = val2;
  
  AST_block_t* new_ast = AST_conditional_block_new(EQ, attr1, attr2);
  cr_assert_not_null(new_ast, "AST_conditional_block_new failed");

  int rc = run_ast_block(new_ast);
  cr_assert_eq(rc, FAILURE, "Running did not properly fail when called on a conditional block");
  AST_block_free(new_ast);
  attribute_free(attr1);
  attribute_free(attr2);
}

/* Checks running an AST control block */
Test(AST_block_t, run_block_control)
{
  AST_block_t* new_ast = AST_control_block_new(IFELSE);
  cr_assert_not_null(new_ast, "AST_control_block_new failed");
  
  int rc = run_ast_block(new_ast);
  cr_assert_eq(rc, FAILURE, "Running did not properly fail when called on a control block");
  AST_block_free(new_ast);
 
}

/* Branch blocks are currently not implemented, so there is currently no test */
