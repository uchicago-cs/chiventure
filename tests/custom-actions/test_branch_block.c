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
    int num_controls = 1;
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
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest within a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // allocates the new branch block
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
                                                  conditional_type, num_controls, &controls);

    cr_assert_not_null(new_branch, "branch_block_new() failed");

    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, &conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, &controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}

/* Checks that a new branch block with conditional type LTGT is created 
without interruption */
Test(branch_block_t, new_LTGT)
{   
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = LTGT;
    
    // allocates a new conditional block to nest within a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest within a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // allocates the new branch block
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
                                                  conditional_type, num_controls, &controls);
    
    cr_assert_not_null(new_branch, "branch_block_new() failed");
    
    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, &conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, &controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}

/* Checks that a new branch block with conditional type LTEGTE is created 
without interruption */
Test(branch_block_t, new_LTEGTE)
{   
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = LTEGTE;
    
    // allocates a new conditional block to nest within a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest within a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // allocates the new branch block
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
                                                  conditional_type, num_controls, &controls);
    
    cr_assert_not_null(new_branch, "branch_block_new() failed");
    
    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, &conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, &controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}

/* Checks that a new branch block with conditional type IN is created 
without interruption */
Test(branch_block_t, new_IN)
{   
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = IN;
    
    // allocates a new conditional block to nest within a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest within a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // allocates the new branch block
    branch_block_t* new_branch = branch_block_new(num_conditionals, &conditionals,
                                                  conditional_type, num_controls, &controls);
    
    cr_assert_not_null(new_branch, "branch_block_new() failed");
    
    cr_assert_eq(new_branch->num_conditionals, num_conditionals, "branch_block_new() "
                "didn't set new_branch->num_conditionals");
    cr_assert_eq(new_branch->conditional_type, conditional_type, "branch_block_new() "
                "didn't set new_branch->conditional_type");
    cr_assert_eq(new_branch->conditionals, &conditionals, "branch_block_new() didn't "
                "set new_branch->conditionals");
    cr_assert_eq(new_branch->num_controls, num_controls, "branch_block_new() didn't "
                "set new_branch->num_controls");
    cr_assert_eq(new_branch->controls, &controls, "branch_block_new() didn't set "
                "new_branch->controls");
    
    branch_block_free(new_branch);
}


/* Checks that a new AST branch block with conditional type EQ is created 
without interruption */
Test(branch_block_t, new_AST_EQ)
{
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = EQ;
    
    // allocates a new conditional block to be nested in the branch and AST blocks
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested in the branch and AST blocks
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    block_type_t block_type = BRANCH;
    
    // allocates a new AST (type branch) block
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block->branch_block->num_conditionals, num_conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditionals, &conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditional_type, conditional_type, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditional_type");
    cr_assert_eq(new_ast->block->branch_block->num_controls, num_controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_controls");
    cr_assert_eq(new_ast->block->branch_block->controls, &controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->controls");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST branch block with conditional type LTGT is created 
without interruption */
Test(branch_block_t, new_AST_LTGT)
{
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = LTGT;
    
    // allocates a new conditional block to be nested in the branch and AST blocks
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested in the branch and AST blocks
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    block_type_t block_type = BRANCH;
    
    // allocates a new AST (type branch) block
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block->branch_block->num_conditionals, num_conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditionals, &conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditional_type, conditional_type, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditional_type");
    cr_assert_eq(new_ast->block->branch_block->num_controls, num_controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_controls");
    cr_assert_eq(new_ast->block->branch_block->controls, &controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->controls");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST branch block with conditional type LTEGTE is created 
without interruption */
Test(branch_block_t, new_AST_LTEGTE)
{
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = LTEGTE;
    
    // allocates a new conditional block to be nested in the branch and AST blocks
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested in the branch and AST blocks
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    block_type_t block_type = BRANCH;
    
    // allocates a new AST (type branch) block
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block->branch_block->num_conditionals, num_conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditionals, &conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditional_type, conditional_type, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditional_type");
    cr_assert_eq(new_ast->block->branch_block->num_controls, num_controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_controls");
    cr_assert_eq(new_ast->block->branch_block->controls, &controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->controls");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    AST_block_free(new_ast);
}

/* Checks that a new AST branch block with conditional type IN is created 
without interruption */
Test(branch_block_t, new_AST_IN)
{
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = IN;
    
    // allocates a new conditional block to be nested in the branch and AST blocks
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested in the branch and AST blocks
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    block_type_t block_type = BRANCH;
    
    // allocates a new AST (type branch) block
    AST_block_t* new_ast = AST_branch_block_new(num_conditionals, &conditionals, 
                                                conditional_type, num_controls, &controls);

    cr_assert_not_null(new_ast, "AST_branch_block_new() failed");

    cr_assert_eq(new_ast->block->branch_block->num_conditionals, num_conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditionals, &conditionals, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditionals");
    cr_assert_eq(new_ast->block->branch_block->conditional_type, conditional_type, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->conditional_type");
    cr_assert_eq(new_ast->block->branch_block->num_controls, num_controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->num_controls");
    cr_assert_eq(new_ast->block->branch_block->controls, &controls, "AST_branch_block_new() didn't set "
                "ast->block->branch_block->controls");
    cr_assert_eq(new_ast->block_type, block_type, "AST_branch_block_new() didn't set "
                "ast->block_type");
    
    AST_block_free(new_ast);
}

/* Checks that a new branch block with conditional type EQ is initialized without 
interruption */
Test(branch_block_t, init_EQ)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = EQ;
    
    // allocates a new conditional block to nest inside the branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest inside the branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // initializes a new branch block
    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                           num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, &conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, &controls, "branch_block_init() didn't set "
                "branch.controls"); 
}

/* Checks that a new branch block with conditional type LTGT is initialized without 
interruption */
Test(branch_block_t, init_LTGT)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = LTGT;
    
    // allocates a new conditional block to nest inside the branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest inside the branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // initializes a new branch block
    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                           num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, &conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, &controls, "branch_block_init() didn't set "
                "branch.controls");
}

/* Checks that a new branch block with conditional type LTEGTE is initialized without 
interruption */
Test(branch_block_t, init_LTEGTE)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = LTEGTE;
    
    // allocates a new conditional block to nest inside the branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest inside the branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // initializes a new branch block
    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                           num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, &conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, &controls, "branch_block_init() didn't set "
                "branch.controls");
}

/* Checks that a new branch block with conditional type IN is initialized without 
interruption */
Test(branch_block_t, init_IN)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = IN;
    
    // allocates a new conditional block to nest inside the branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to nest inside the branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);

    // initializes a new branch block
    rc = branch_block_init(&branch, num_conditionals, &conditionals, conditional_type, 
                           num_controls, &controls);

    cr_assert_eq(rc, SUCCESS, "branch_block_init() failed");
    cr_assert_eq(branch.num_conditionals, num_conditionals, "branch_block_init() "
                "didn't set new_branch.num_conditionals");
    cr_assert_eq(branch.conditional_type, conditional_type, "branch_block_init() "
                "didn't set branch.conditional_type");
    cr_assert_eq(branch.conditionals, &conditionals, "branch_block_init() didn't "
                "set branch.conditionals");
    cr_assert_eq(branch.num_controls, num_controls, "branch_block_init() didn't "
                "set branch.num_controls");
    cr_assert_eq(branch.controls, &controls, "branch_block_init() didn't set "
                "branch.controls");
}

/* Checks that a new branch block with conditional type EQ is freed without 
interruption */
Test(branch_block_t, free_EQ)
{
    branch_block_t* branch;
    int rc;
    int num_conditionals = 1;
    int num_controls = 1;
    conditional_type_t conditional_type = EQ;
    
    // allocates a new conditional block to nest inside a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested inside a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    
    // allocates a new branch block to be freed
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
    int num_controls = 1;
    conditional_type_t conditional_type = LTGT;
    
    // allocates a new conditional block to nest inside a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested inside a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    
    // allocates a new branch block to be freed
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
    int num_controls = 1;
    conditional_type_t conditional_type = LTEGTE;
    
    // allocates a new conditional block to nest inside a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested inside a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    
    // allocates a new branch block to be freed
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
    int num_controls = 1;
    conditional_type_t conditional_type = IN;
    
    // allocates a new conditional block to nest inside a branch block
    char *attr_name1 = "attribute1";
    char *attr_name2 = "attribute2";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *left = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    left->hh = hh;
    left->attribute_key = attr_name1;
    left->attribute_tag = attribute_tag;
    left->attribute_value = attribute_value;
    attribute_t *right = malloc(sizeof(attribute_t));
    right->hh = hh;
    right->attribute_key = attr_name2;
    right->attribute_tag = attribute_tag ;
    right->attribute_value = attribute_value;
    conditional_block_t* conditionals = conditional_block_new(conditional_type, left, right);
    
    // allocates a new control block to be nested inside a branch block
    control_type_t control_type = IFELSE;
    control_block_t* controls = control_block_new(control_type);
    
    // allocates a new branch block to be freed
    branch = branch_block_new(num_conditionals, &conditionals, conditional_type,  
                              num_controls, &controls);

    cr_assert_not_null(branch, "branch_block_new() failed");

    rc = branch_block_free(branch);

    cr_assert_eq(rc, SUCCESS, "branch_block_free() failed");
}
