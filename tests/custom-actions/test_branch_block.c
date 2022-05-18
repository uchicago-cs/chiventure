#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "branch_block.h"
#include "game-state/item.h"
#include "ast_block.h"


/* Checks that a new branch block with conditional type EQ is created 
without interruption */
Test(branch_block_t, new)
{
    int num_conditionals = 1;
    int num_actions = 1;
    conditional_type_t conditional_type = EQ;
    
    // allocates a new conditional block to nest within a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = strdup(attr_name1);
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = strdup(attr_name2);
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new action block to nest within a branch block
    control_type_t control_type = IFELSE;
    action_enum_t action_type = SET;
    AST_block_t* actions  = AST_action_block_new(action_type, num_actions, &left);
    cr_assert_not_null(actions, "action_block_new failed");
    
    // allocates the new branch block
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
                                                  control_type, num_actions, &actions);

    cr_assert_not_null(new_branch, "branch_block_new() failed");

    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->control_type, control_type, "branch_block_new() "
                "didn't set new_branch->control_type");
    cr_assert_eq(new_branch->conditionals, &conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_actions, num_actions, "branch_block_new() didn't "
                "set new_branch->num_actions");
    cr_assert_eq(new_branch->actions, &actions, "branch_block_new() didn't set "
                "new_branch->actions");
    
    branch_block_free(new_branch);
    attribute_free(left);
    attribute_free(right);
}


/* Checks that a new AST branch block with conditional type EQ is created 
without interruption */
Test(branch_block_t, new_AST)
{
    int num_conditionals = 1;
    int num_actions = 1;
    block_type_t block_type = BRANCH;
    // allocates a new conditional block to nest within a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = strdup(attr_name1);
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = strdup(attr_name2);
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_type_t conditional_type = EQ;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);

    // allocates a new action block to nest within a branch block
    control_type_t control_type = IFELSE;
    action_enum_t action_type = SET;
    AST_block_t* actions  = AST_action_block_new(action_type, num_actions, &left);
    cr_assert_not_null(actions, "action_block_new failed");

    // allocates the new branch block
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals,
						control_type, num_actions, &actions);
  
    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block->branch_block->num_conditionals, num_conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditionals, &conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditionals");
    cr_assert_eq(new_ast->block->branch_block->control_type, control_type, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->control_type");
    cr_assert_eq(new_ast->block->branch_block->num_actions, num_actions, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_actions");
    cr_assert_eq(new_ast->block->branch_block->actions, &actions, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->actions");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    AST_block_free(new_ast);
    attribute_free(left);
    attribute_free(right);
}


/* Checks that a new branch block with conditional type EQ is initialized without 
interruption */
Test(branch_block_t, init)
{
    int rc;
    branch_block_t *branch = malloc(sizeof(branch_block_t));
    int num_conditionals = 1;
    int num_actions = 1;
    // allocates a new conditional block to nest within a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = strdup(attr_name1);
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = strdup(attr_name2);
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_type_t conditional_type = EQ;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);

    // allocates a new action block to nest within a branch block
    control_type_t control_type = IFELSE;
    action_enum_t action_type = SET;
    AST_block_t* actions  = AST_action_block_new(action_type, num_actions, &left);
    cr_assert_not_null(actions, "action_block_new failed");

    // initializes a new branch block
    rc = branch_block_init(branch, num_conditionals, &conditionals, conditional_type, 
                           num_actions, &actions);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch->num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch->control_type, control_type, "branch_block_init() "
                "didn't set branch.control_type");
    cr_assert_eq(branch->conditionals, &conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch->num_actions, num_actions, "branch_block_init() didn't "
                "set branch.num_actions");
    cr_assert_eq(branch->actions, &actions, "branch_block_init() didn't set "
                "branch.actions");
    branch_block_free(branch);
    attribute_free(left);
    attribute_free(right);
}

/* Checks that a new branch block with conditional type EQ is freed without 
interruption */
Test(branch_block_t, free)
{
    int rc;
    int num_conditionals = 1;
    int num_actions = 1;
    // allocates a new conditional block to nest within a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = strdup(attr_name1);
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = strdup(attr_name2);
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_type_t conditional_type = EQ;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
 
    // allocates a new action block to nest within a branch block
    control_type_t control_type = IFELSE;
    action_enum_t action_type = SET;
    AST_block_t* actions  = AST_action_block_new(action_type, num_actions, &left);
    cr_assert_not_null(actions, "action_block_new failed");

    // allocates the new branch block
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
						control_type, num_actions, &actions);
    cr_assert_not_null(new_branch, "branch_block_new() failed");
    
    rc = branch_block_free(new_branch);

    cr_assert_eq(rc, SUCCESS, "branch_block_free() failed");
    attribute_free(left);
    attribute_free(right);
}

/* Checks that a new branch block runs as an IFELSE 
- If is true */
Test(branch_block_t, IFELSE_success)
{
  int rc;
  int num_conditionals = 1;
  int num_actions = 1;
  // allocates a new conditional block to nest within a branch block
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t av1, av2;
  av1.int_val = 1;
  av2.int_val = 2;
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = av1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag ;
  right->attribute_value = av2;
  conditional_type_t conditional_type = LTB;
  conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);

  // allocates a new action block to nest within a branch block
  control_type_t control_type = IFELSE;
  action_enum_t action_type = SET;

  attribute_t **args = malloc(sizeof(attribute_t*) * 2);
  action_param_t *action_params = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params->args = args; 
  args[0] = left;
  args[1] = right;

  int num_attributes = 2;
  AST_block_t* actions  = AST_action_block_new(action_type, num_attributes, action_params);
  cr_assert_not_null(actions, "action_block_new failed");

  
  // allocates the new branch block
  branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
						control_type, num_actions, &actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, SUCCESS, "do_branch_block failed");
  cr_assert_eq(right->attribute_value.int_val, left->attribute_value.int_val, "do_branch_block failed to set value");

  
  branch_block_free(new_branch);
  attribute_free(left);
  attribute_free(right);
}

/* Checks that a branch block runs an IFELSE properly
 - If isn't true */
Test(branch_block_t, IFELSE_failure)
{
  int rc;
  int num_conditionals = 1;
  int num_actions = 1;
  // allocates a new conditional block to nest within a branch block
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t av1, av2;
  av1.int_val = 1;
  av2.int_val = 2;
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = av1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag ;
  right->attribute_value = av2;
  conditional_type_t conditional_type = GTB;
  conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);

  // allocates a new action block to nest within a branch block
  control_type_t control_type = IFELSE;
  action_enum_t action_type = SET;

  attribute_t **args = malloc(sizeof(attribute_t*) * 2);
  args[0] = left;
  args[1] = right;

  int num_attributes = 2;
  AST_block_t* actions  = AST_action_block_new(action_type, num_attributes, args);
  cr_assert_not_null(actions, "action_block_new failed");


  // allocates the new branch block
  branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
						control_type, num_actions, &actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, SUCCESS, "do_branch_block failed");
  cr_assert_neq(right->attribute_value.int_val, left->attribute_value.int_val, "do_branch_block set value incorrectly");


  branch_block_free(new_branch);
  attribute_free(left);
  attribute_free(right);
}

/* Checks that a branch block runs an IFELSE properly
   - Multiple conditions */
Test(branch_block_t, multiple_conditions)
{
  int rc;
  int num_conditionals = 2;
  int num_actions = 2;
  // allocates a new array of conditional blocks to nest within a branch block
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  char *attr_name3 = "attribute3";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t av1, av2, av3;
  av1.int_val = 1;
  av2.int_val = 2;
  av3.int_val = 3;
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = av1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = av2;
  attribute_t *a3 = malloc(sizeof(attribute_t));
  a3->hh = hh;
  a3->attribute_key = strdup(attr_name3);
  a3->attribute_tag = attribute_tag;
  a3->attribute_value = av3;
  conditional_type_t conditional_type = GTB;
  conditional_block_t** conditionals = malloc(sizeof(conditional_block_t*) * 2);
  conditionals[0] = conditional_block_new(conditional_type, left, right);
  conditionals[1] = conditional_block_new(conditional_type, right, left);
  
  // allocates a new array of action blocks to nest within a branch block
  control_type_t control_type = IFELSE;
  action_enum_t action_type = SET;

  attribute_t **args1 = malloc(sizeof(attribute_t*) * 2);
  action_param_t *action_params1 = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params1->args = args1; 
  args1[0] = left;
  args1[1] = right;

  attribute_t **args2 = malloc(sizeof(attribute_t*) * 2);
  action_param_t *action_params2 = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params2->args = args2; 
  args2[0] = right;
  args2[1] = a3;
  
  int num_attributes = 2;
  AST_block_t** actions  = malloc(sizeof(AST_block_t*) * 2);
  actions[0] = AST_action_block_new(action_type, num_attributes, action_params1);
  actions[1] = AST_action_block_new(action_type, num_attributes, action_params2);

  // allocates the new branch block
  branch_block_t* new_branch = branch_block_new(num_conditionals, conditionals,
						control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);
    
  cr_assert_eq(rc, SUCCESS, "do_branch_block failed");
  cr_assert_neq(right->attribute_value.int_val, left->attribute_value.int_val, "do_branch_block set value incorrectly");
  cr_assert_eq(right->attribute_value.int_val, a3->attribute_value.int_val, "do_branch_block failed to set value");

  branch_block_free(new_branch);
  attribute_free(left);
  attribute_free(right);
  attribute_free(a3);
}

/* Checks that a branch block runs an IFELSE properly
   - Tests default case */
Test(branch_block_t, default_if)
{
  int rc;
  int num_conditionals = 1;
  int num_actions = 2;
  // allocates a new array of conditional blocks to nest within a branch block
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  char *attr_name3 = "attribute3";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t av1, av2, av3;
  av1.int_val = 1;
  av2.int_val = 2;
  av3.int_val = 3;
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = av1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = av2;
  attribute_t *a3 = malloc(sizeof(attribute_t));
  a3->hh = hh;
  a3->attribute_key = strdup(attr_name3);
  a3->attribute_tag = attribute_tag;
  a3->attribute_value = av3;
  conditional_type_t conditional_type = GTB;
  conditional_block_t** conditionals = malloc(sizeof(conditional_block_t*));
  conditionals[0] = conditional_block_new(conditional_type, left, right);

  // allocates a new array of action blocks to nest within a branch block
  control_type_t control_type = IFELSE;
  action_enum_t action_type = SET;

  attribute_t **args = malloc(sizeof(attribute_t*) * 2);
  action_param_t *action_params = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params->args = args; 
  args[0] = left;
  args[1] = right;

  attribute_t **args2 = malloc(sizeof(attribute_t*) * 2);
  action_param_t *action_params2 = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params2->args = args2; 
  args2[0] = right;
  args2[1] = a3;

  int num_attributes = 2;
  AST_block_t** actions  = malloc(sizeof(AST_block_t*) * 2);
  actions[0] = AST_action_block_new(action_type, num_attributes, action_params);
  actions[1] = AST_action_block_new(action_type, num_attributes, action_params2);

  // allocates the new branch block
  branch_block_t* new_branch = branch_block_new(num_conditionals, conditionals,
						control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, SUCCESS, "do_branch_block failed");
  cr_assert_neq(right->attribute_value.int_val, left->attribute_value.int_val, "do_branch_block set value incorrectly");
  cr_assert_eq(right->attribute_value.int_val, a3->attribute_value.int_val, "do_branch_block failed to set value");

  branch_block_free(new_branch);
  attribute_free(left);
  attribute_free(right);
  attribute_free(a3);
}

/* Checks that a branch block runs a WHILEENDWHILE properly
   - Normal While */
Test(branch_block_t, while_sucess)
{
  int rc;
  int num_conditionals = 1;
  int num_actions = 1;
  // allocates a new array of conditional blocks to nest within a branch block
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  char *attr_name3 = "attribute3";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t av1, av2, av3;
  av1.int_val = 1;
  av2.int_val = 1;
  av3.int_val = 5;
  
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = av1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = av2;
  attribute_t *a3 = malloc(sizeof(attribute_t));
  a3->hh = hh;
  a3->attribute_key = strdup(attr_name3);
  a3->attribute_tag = attribute_tag;
  a3->attribute_value = av3;
  conditional_type_t conditional_type = LTB;
  conditional_block_t** conditionals = malloc(sizeof(conditional_block_t*));
  conditionals[0] = conditional_block_new(conditional_type, right, a3);
  
  // allocates a new array of action blocks to nest within a branch block
  control_type_t control_type = WHILEENDWHILE;
  action_enum_t action_type = ADDITION;

  attribute_t **args = malloc(sizeof(attribute_t*) * 2);
  action_param_t *action_params = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params->args = args; 
  args[0] = left;
  args[1] = right;
  args[2] = right;

  int num_attributes = 3;
  AST_block_t** actions  = malloc(sizeof(AST_block_t*));
  actions[0] = AST_action_block_new(action_type, num_attributes, action_params);
  
  // allocates the new branch block
  branch_block_t* new_branch = branch_block_new(num_conditionals, conditionals,
						control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, SUCCESS, "do_branch_block failed");
  cr_assert_neq(right->attribute_value.int_val, left->attribute_value.int_val, "do_branch_block failed to add");
  cr_assert_eq(right->attribute_value.int_val, a3->attribute_value.int_val, "do_branch_block failed to set value");

  branch_block_free(new_branch);
  attribute_free(left);
  attribute_free(right);
  attribute_free(a3);
}

/* Checks that a branch block runs a WHILEENDWHILE properly
   - Multiple conditions */
Test(branch_block_t, end_while)
{
  int rc;
  int num_conditionals = 2;
  int num_actions = 1;
  // allocates a new array of conditional blocks to nest within a branch block
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  char *attr_name3 = "attribute3";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t av1, av2, av3;
  av1.int_val = 2;
  av2.int_val = 1;
  av3.int_val = 7;

  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = av1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = av2;
  attribute_t *a3 = malloc(sizeof(attribute_t));
  a3->hh = hh;
  a3->attribute_key = strdup(attr_name3);
  a3->attribute_tag = attribute_tag;
  a3->attribute_value = av3;
  conditional_type_t conditional_type = LTB;
  conditional_block_t** conditionals = malloc(sizeof(conditional_block_t*) * 2);
  conditionals[0] = conditional_block_new(conditional_type, right, left);
  conditionals[1] = conditional_block_new(conditional_type, right, a3);
  
  // allocates a new array of action blocks to nest within a branch block
  control_type_t control_type = WHILEENDWHILE;
  action_enum_t action_type = ADDITION;

  attribute_t **args = malloc(sizeof(attribute_t*) * 2);
  action_param_t *action_params = (action_param_t*)malloc(sizeof(action_param_t)); 
  action_params->args = args; 
  args[0] = left;
  args[1] = right;
  args[2] = right;

  int num_attributes = 3;
  AST_block_t** actions  = malloc(sizeof(AST_block_t*));
  actions[0] = AST_action_block_new(action_type, num_attributes, action_params);

  // allocates the new branch block
  branch_block_t* new_branch = branch_block_new(num_conditionals, conditionals,
						control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, SUCCESS, "do_branch_block failed");
  cr_assert_neq(right->attribute_value.int_val, 1, "do_branch_block failed to add");
  cr_assert_neq(right->attribute_value.int_val, 4, "do_branch_block ended while at the start condition");
  cr_assert_eq(right->attribute_value.int_val, a3->attribute_value.int_val, "do_branch_block failed to set value");

  branch_block_free(new_branch);
  attribute_free(left);
  attribute_free(right);
  attribute_free(a3);
}

/* Checks the failure conditions of do_branch_blocks */
Test(branch_block_t, failure_conditions)
{
  int rc;
  int num_conditionals = 1;
  int num_actions = 1;

  // allocates a new array of conditional blocks to nest within a branch block
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  char *attr_name3 = "attribute3";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t av1, av2, av3;
  av1.int_val = 1;
  av2.int_val = 1;
  av3.int_val = 5;

  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = av1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = av2;
  attribute_t *a3 = malloc(sizeof(attribute_t));
  a3->hh = hh;
  a3->attribute_key = strdup(attr_name3);
  a3->attribute_tag = attribute_tag;
  a3->attribute_value = av3;
  conditional_type_t conditional_type = LTB;
  conditional_block_t** conditionals = malloc(sizeof(conditional_block_t*));
  conditionals[0] = conditional_block_new(conditional_type, right, a3);

  // allocates a new array of action blocks to nest within a branch block
  control_type_t control_type = WHILEENDWHILE;
  action_enum_t action_type = ADDITION;

  attribute_t **args = malloc(sizeof(attribute_t*) * 2);
  args[0] = left;
  args[1] = right;
  args[2] = right;

  int num_attributes = 3;
  AST_block_t** actions  = malloc(sizeof(AST_block_t*));
  actions[0] = AST_action_block_new(action_type, num_attributes, args);
  branch_block_t *new_branch;

  //No Conditionals
  new_branch = branch_block_new(num_conditionals, conditionals, control_type, num_actions, actions);
  new_branch->num_conditionals = 0;
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, FAILURE, "do_branch_block didn't fail with no conditions");
  free(new_branch);
  
  //No actions
  new_branch = branch_block_new(num_conditionals, conditionals, control_type, num_actions, actions);
  new_branch->num_actions = 0;
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, FAILURE, "do_branch_block didn't fail with no actions");
  free(new_branch);

  //Too many actions for a while loop
  num_actions = 2;
  new_branch = branch_block_new(num_conditionals, conditionals, control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, FAILURE, "While didn't fail with 2 actions");
  free(new_branch);

  //Too many conditionals for a while loop
  num_actions = 1;
  num_conditionals = 11;
  new_branch = branch_block_new(num_conditionals, conditionals, control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, FAILURE, "do_branch_block didn't fail with too many conditionals in an if");
  free(new_branch);

  //More conditionals than actions in an IF
  control_type = IFELSE;
  new_branch = branch_block_new(num_conditionals, conditionals, control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, FAILURE, "do_branch_block didn't fail with no conditionals");
  free(new_branch);

  //Too many actions in an IF
  num_actions = 22;
  new_branch = branch_block_new(num_conditionals, conditionals, control_type, num_actions, actions);
  cr_assert_not_null(new_branch, "branch_block_new() failed");

  rc = do_branch_block(new_branch);

  cr_assert_eq(rc, FAILURE, "do_branch_block didn't fail with too many actions");
  new_branch->num_actions = 1;
  new_branch->num_conditionals = 1;
  branch_block_free(new_branch);

  attribute_free(left);
  attribute_free(right);
  attribute_free(a3);
}
