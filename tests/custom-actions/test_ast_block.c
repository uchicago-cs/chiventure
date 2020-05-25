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
    control_type_t control_type = IFELSE;
    block_t *block;
    block->control_block = control_block_new(control_type);
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
    int num_conditionals = 1;
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left;
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right;
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals, conditional_type, 
                                                    num_controls, &controls);

    block_t *block;
    block->branch_block = new_branch;
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
    action_enum_t action_type = SET;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    attribute_t *args = get_attribute(item_1, attr_name1);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    &args);

    block_t *block;
    block->action_block = new_action;
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
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);
    block_t *block;
    block->conditional_block = new_conditional;
    block_type_t block_type = CONDITIONAL;
    AST_block_t* new_ast = AST_block_new(block, block_type);

    cr_assert_not_null(new_ast, "AST_block_new failed");

    cr_assert_eq(new_ast->block, block, "AST_block_new() didn't set new_ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_block_new() didn't set " 
                "new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST block with control type is initialized without interruption */
Test(AST_block_t, init_CONTROL)
{
    AST_block_t ast;
    int rc;
    control_type_t control_type = IFELSE;
    control_block_t* new_control = control_block_new(control_type);
    block_t *block;
    block->control_block = new_control;
    block_type_t block_type = CONTROL;

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with branch type is initialized without interruption */
Test(AST_block_t, init_BRANCH)
{
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
                                                    conditional_type, num_controls, &controls);
    block_t *block;
    block_type_t block_type = BRANCH;
    block->branch_block = new_branch;
    AST_block_t ast;
    
    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with action type is initialized without interruption */
Test(AST_block_t, init_ACTION)
{
    int rc;
    action_enum_t action_type = SET;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    attribute_t *args = get_attribute(item_1, attr_name1);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    &args);
    block_t *block;
    block_type_t block_type = ACTION;
    block->action_block = new_action;
    AST_block_t ast; 

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with conditional type is initialized without interruption */
Test(AST_block_t, init_CONDITIONAL)
{
    int rc;
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);
    block_t *block;
    block_type_t block_type = CONDITIONAL;
    block->conditional_block = new_conditional;
    AST_block_t ast;

    rc = AST_block_init(&ast, block, block_type);

    cr_assert_eq(rc, SUCCESS, "AST_block_init() failed");
    cr_assert_eq(ast.block, block, "AST_block_init() didn't set ast->block");
    cr_assert_eq(ast.block_type, block_type, "AST_block_init() didn't set ast->block_type");
}

/* Checks that a new AST block with control type is freed without interruption */
Test(AST_block_t, free_CONTROL)
{
    AST_block_t* ast;
    int rc;
    control_type_t control_type = IFELSE;
    
    ast = AST_control_block_new(control_type);

    cr_assert_not_null(ast, "AST_control_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with branch type is freed without interruption */
Test(AST_block_t, free_BRANCH)
{
    AST_block_t* ast;
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                conditional_type, num_controls, &controls);

    cr_assert_not_null(ast, "AST_branch_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with action type is freed without interruption */
Test(AST_block_t, free_ACTION)
{
    AST_block_t* ast;
    int rc;
    action_enum_t action_type = SET;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    attribute_t *args = get_attribute(item_1, attr_name1);

    ast = AST_action_block_new(action_type, num_args, &args);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}

/* Checks that a new AST block with conditional type is freed without interruption */
Test(AST_block_t, free_CONDITIONAL)
{
    AST_block_t* ast;
    int rc;
    conditional_type_t conditional_type = EQ;
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    char *item_id1 = "01";
    char *short_desc1 = "01";
    char *long_desc1 = "0001";
    char *item_id2 = "02";
    char *short_desc2 = "02";
    char *long_desc2 = "0002";
    item_t *item_1 = item_new(item_id1, short_desc1, long_desc1);
    item_t *item_2 = item_new(item_id2, short_desc2, long_desc2);
    attribute_t* left = get_attribute(item_1, attr_name1);
    attribute_t* right = get_attribute(item_2, attr_name2);

    ast = AST_conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(ast, "AST_conditional_block_new() failed");

    rc = AST_block_free(ast);

    cr_assert_eq(rc, SUCCESS, "AST_block_free() failed");
}
