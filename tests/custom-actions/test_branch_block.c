#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "branch_block.h"
#include "game-state/item.h"
#include "ast_block.h"

/* Checks that a new branch block with conditional type EQ is created 
without interruption */
Test(branch_block_t, new_EQ)
{
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
                                                    conditional_type,num_controls, &controls);

    cr_assert_not_null(new_branch, "branch_block_new() failed");

    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}

/* Checks that a new branch block with conditional type LTGT is created 
without interruption */
Test(branch_block_t, new_LTGT)
{   
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTGT;
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
    
    cr_assert_not_null(new_branch, "branch_block_new() failed");
    
    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}

/* Checks that a new branch block with conditional type LTEGTE is created 
without interruption */
Test(branch_block_t, new_LTEGTE)
{   
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTEGTE;
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
    
    cr_assert_not_null(new_branch, "branch_block_new() failed");
    
    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}

/* Checks that a new branch block with conditional type IN is created 
without interruption */
Test(branch_block_t, new_IN)
{   
    int num_conditionals = 1;
    conditional_type_t conditional_type = IN;
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
    
    cr_assert_not_null(new_branch, "branch_block_new() failed");
    
    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}


/* Checks that a new AST branch block with conditional type EQ is created 
without interruption */
Test(branch_block_t, new_AST_EQ)
{
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
    block_type_t block_type = BRANCH;
    
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals, 
                                    conditional_type, num_controls, &controls);
    
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                    conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block, new_branch, "AST_branch_block_new() didn't set "
                "ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    branch_block_free(new_branch);
    AST_block_free(ast);
}

/* Checks that a new AST branch block with conditional type LTGT is created 
without interruption */
Test(branch_block_t, new_AST_LTGT)
{
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTGT;
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
    block_type_t block_type = BRANCH;
    
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals, 
                                    conditional_type, num_controls, &controls);
    
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                    conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block, new_branch, "AST_branch_block_new() didn't set "
                "ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    branch_block_free(new_branch);
    AST_block_free(ast);
}

/* Checks that a new AST branch block with conditional type LTEGTE is created 
without interruption */
Test(branch_block_t, new_AST_LTEGTE)
{
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTEGTE;
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
    block_type_t block_type = BRANCH;
    
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals, 
                                    conditional_type, num_controls, &controls);
    
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                    conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block, new_branch, "AST_branch_block_new() didn't set "
                "ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    branch_block_free(new_branch);
    AST_block_free(ast);
}

/* Checks that a new AST branch block with conditional type IN is created 
without interruption */
Test(branch_block_t, new_AST_IN)
{
    int num_conditionals = 1;
    conditional_type_t conditional_type = IN;
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
    block_type_t block_type = BRANCH;
    
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals, 
                                    conditional_type, num_controls, &controls);
    
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                    conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block, new_branch, "AST_branch_block_new() didn't set "
                "ast->block");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    branch_block_free(new_branch);
    AST_block_free(ast);
}

/* Checks that a new branch block with conditional type EQ is initialized without 
interruption */
Test(branch_block_t, init_EQ)
{
    branch_block_t branch;
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

    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                            num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, controls, "branch_block_init() didn't set "
                "branch.controls"); 
}

/* Checks that a new branch block with conditional type LTGT is initialized without 
interruption */
Test(branch_block_t, init_LTGT)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTGT;
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

    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                            num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, controls, "branch_block_init() didn't set "
                "branch.controls");
}

/* Checks that a new branch block with conditional type LTEGTE is initialized without 
interruption */
Test(branch_block_t, init_LTEGTE)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTEGTE;
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

    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                            num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, controls, "branch_block_init() didn't set "
                "branch.controls");
}

/* Checks that a new branch block with conditional type IN is initialized without 
interruption */
Test(branch_block_t, init_IN)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = IN;
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

    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                            num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, controls, "branch_block_init() didn't set "
                "branch.controls");
}

/* Checks that a new branch block with conditional type EQ is freed without 
interruption */
Test(branch_block_t, free_EQ)
{
    branch_block_t* branch;
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
    
    branch = branch_block_new(num_conditionals, &conditionals, conditional_type,  
                                num_controls, &controls);

    cr_assert_not_null(branch, "branch_block_new() failed");
    
    rc = branch_block_free(branch);

    cr_assert_eq(rc, SUCCESS, "branch_block_free() failed");
}

/* Checks that a new branch block with conditional type LTGT is freed without 
interruption */
Test(branch_block_t, free_LTGT)
{
    branch_block_t* branch;
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTGT;
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

    branch = branch_block_new(num_conditionals, &conditionals, conditional_type,
                                num_controls, &controls);

    cr_assert_not_null(branch, "branch_block_new() failed");

    rc = branch_block_free(branch);

    cr_assert_eq(rc, SUCCESS, "branch_block_free() failed");
}
     
/* Checks that a new branch block with conditional type LTEGTE is freed without 
interruption */
Test(branch_block_t, free_LTEGTE)
{
    branch_block_t* branch;
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = LTEGTE;
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

    branch = branch_block_new(num_conditionals, &conditionals, conditional_type,
                                num_controls, &controls);

    cr_assert_not_null(branch, "branch_block_new() failed");

    rc = branch_block_free(branch);

    cr_assert_eq(rc, SUCCESS, "branch_block_free() failed");
}
     
/* Checks that a new branch block with conditional type IN is freed without 
interruption */
Test(branch_block_t, free_IN)
{
    branch_block_t* branch;
    int rc;
    int num_conditionals = 1;
    conditional_type_t conditional_type = IN;
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

    branch = branch_block_new(num_conditionals, &conditionals, conditional_type,
                                num_controls, &controls);

    cr_assert_not_null(branch, "branch_block_new() failed");

    rc = branch_block_free(branch);

    cr_assert_eq(rc, SUCCESS, "branch_block_free() failed");
}
      
