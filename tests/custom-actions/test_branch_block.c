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
    
    // allocates a new control block to nest within a branch block
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

    // allocates a new control block to nest within a branch block
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

    // allocates a new control block to nest within a branch block
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
 
    // allocates a new control block to nest within a branch block
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
