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

  append_list_AST_block(first_ast, second_ast);
  append_list_AST_block(first_ast, third_ast);
    
  /* Create another AST_block that will be places as the last place in linked list */
  block_t *cond = malloc(sizeof(block_t));
  block_type_t new_end_block_type = CONDITIONAL;

  AST_block_t* new_end_ast = AST_block_new(cond, new_end_block_type);
  cr_assert_not_null(new_end_ast, "AST_block_new failed to create the to-be new_end_AST_block");
  
  ret_val = append_list_AST_block(first_ast, new_end_ast);
  cr_assert_eq(ret_val, SUCCESS, "list_add_AST_block returned FAILURE upon trying to add in last place");

  cr_assert_eq(new_end_ast, third_ast->next, "Append did not properly place new_end_ast at the end of the list");
  
  if (first_ast->next != second_ast)
  {
    cr_assert_fail("list_add_AST_block unintentionally messed with pointers that shouldn't have been");
  }
  if (second_ast->next != third_ast)
  {
    cr_assert_fail("list_add_AST_block unintentionally messed with pointer that shouldn't have been");
  }
  if (third_ast->next != new_end_ast)
  {
    cr_assert_fail("list_add_AST_block did not set the pointer to the new last AST_block in list");
  }
  
  AST_block_free(first_ast);
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

    append_list_AST_block(new_ast, second_ast);
    append_list_AST_block(new_ast, third_ast);

    /* Check to see how many AST_block_t are linked together */
    ret_val = list_how_many_AST_block(new_ast);
    cr_assert_eq(ret_val, 3, "list_how_many_AST_block did not return correct value of only 3 AST blocks linked");

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

    append_list_AST_block(first_ast, second_ast);
    append_list_AST_block(first_ast, third_ast);
    
    /* Create another AST_block that will be places as the first place in linked list */
    block_t *cond = malloc(sizeof(block_t));
    block_type_t new_first_block_type = CONDITIONAL;
      
    AST_block_t* new_first_ast = AST_block_new(cond, new_first_block_type);
    cr_assert_not_null(new_first_ast, "AST_block_new failed to create the to-be new_first_AST_block");
    
    ret_val = prepend_list_AST_block(first_ast, new_first_ast);
    cr_assert_eq(ret_val, SUCCESS, "list_add_AST_block returned FAILURE upon trying to add in first place");

    cr_assert_eq(new_first_ast->next, first_ast , "The new first ast block was not properly added to the start of the list");

    if (new_first_ast->next != first_ast)
        cr_assert_fail("new_first_ast second element failed to be set to first_ast");
    if (first_ast->next != second_ast)
        cr_assert_fail("list_add_AST_block unintentionally messed with pointers that shouldn't have been");
    if (second_ast->next != third_ast)
        cr_assert_fail("list_add_AST_block unintentionally messed with pointer that shouldn't have been");

    AST_block_free(new_first_ast);
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

    append_list_AST_block(new_ast, second_ast);
    append_list_AST_block(new_ast, third_ast);
    
    /* Delete second item from linked list */
    ret_val = list_remove_AST_block(new_ast, second_ast);
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

    append_list_AST_block(new_ast, second_ast);
    append_list_AST_block(new_ast, third_ast);
    
    block_t* fail = malloc(sizeof(action_block_t));
    block_type_t fail_block_type = CONDITIONAL;

    AST_block_t* fail_ast = AST_block_new(fail, fail_block_type);
    /* Delete second item from linked list */
    ret_val = list_remove_AST_block(new_ast, fail_ast);
    cr_assert_eq(ret_val, SUCCESS, "list_remove_AST_block failed");

    if (new_ast->next == third_ast)
        cr_assert_fail("list_remove_AST_block deleted second AST_block when it shouldn't have");

    AST_block_free(new_ast);
}

/* Checks that only a singular AST block is freed when calling AST_free */
Test(AST_block_t, AST_free)
{
    int ret_val;

    ret_val = sizeof(AST_block_t);

    /* Create 2 AST_blocks and link them together according to name (manual) */
    block_t *block = malloc(sizeof(control_block_t));
    block_type_t block_type = CONTROL;
    
    AST_block_t* new_ast = AST_block_new(block, block_type);
    cr_assert_not_null(new_ast, "AST_block_new failed to create a AST_block");

    block_t *brnc = malloc(sizeof(branch_block_t));
    brnc->control_block = control_block_new(IFELSE);
    block_type_t second_block_type = CONTROL;

    AST_block_t* second_ast = AST_block_new(brnc, second_block_type);
    cr_assert_not_null(second_ast, "AST_block_new failed to create the second AST_block");

    append_list_AST_block(new_ast, second_ast);

    /* Free new_ast */
    ret_val = AST_free(new_ast);
    cr_assert_eq(ret_val, SUCCESS, "AST_free failed to run without interruptions");
    cr_assert_not_null(second_ast, "AST_free freed the entire list of AST blocks");

    ret_val = AST_free(second_ast);
    cr_assert_eq(ret_val, SUCCESS, "AST_Free failed to free second_ast, prior error must exist");
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
  action_param_t *action_params = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params->args = args; 
  args[0] = attr1;
  args[1] = attr2;

  
  AST_block_t* new_ast = AST_action_block_new(SET, 2, action_params);

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

/* Checks that run_ast_block correctly runs multiple blocks */
Test(AST_block_t, run_multiple_actions)
{
  attribute_t *attr1, *attr2, *attr3;
  attribute_value_t val1, val2, val3;
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
  
  attr3 = malloc(sizeof(attribute_t));
  attr3->attribute_key = strdup(attr_name);
  attr3->attribute_tag = INTEGER;
  val3.int_val = 15;
  attr3->attribute_value = val3;
  
  attribute_t **args = (attribute_t**) malloc(sizeof(attribute_t*) * 3);
  action_param_t *action_params = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params->args = args; 
  args[0] = attr1;
  args[1] = attr2;
  args[2] = attr3;

  
  AST_block_t* new_ast = AST_action_block_new(ADDITION, 3, action_params);
  AST_block_t* next = AST_action_block_new(MULTIPLY, 3, action_params);
  
  cr_assert_not_null(new_ast, "AST_block_new failed for new_ast");
  cr_assert_not_null(next, "AST_block_new failed for next");

  new_ast->next = next;

  int rc = run_ast_block(new_ast);

  cr_assert_eq(rc, SUCCESS, "run_ast_block failed");

  cr_assert_eq(attr3->attribute_value.int_val, 50, "The final evaluate made was not the multiply action block");

  attribute_free(attr1);
  attribute_free(attr2);
  attribute_free(attr3);
  AST_block_free(new_ast);
}
