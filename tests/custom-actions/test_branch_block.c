#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "branch_block.h"

/* Checks that a new branch block with conditional type EQ is created 
without interruption */
Test(branch_block_t, new_EQ)
{
    int num_conditionals = 1;
    enum conditional_type conditional_type = EQ;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    branch_block_t* new_branch = branch_block_new(num_conditionals, conditional_type, 
                                                    conditionals, num_controls, controls);

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
    enum conditional_type conditional_type = LTGT;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);
    
    branch_block_t* new_branch = branch_block_new(num_conditionals, conditional_type,
                                                    conditionals, num_controls, controls);
    
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
    enum conditional_type conditional_type = LTEGTE;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);
    
    branch_block_t* new_branch = branch_block_new(num_conditionals, conditional_type,
                                                    conditionals, num_controls, controls);
    
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
    enum conditional_type conditional_type = IN;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);
    
    branch_block_t* new_branch = branch_block_new(num_conditionals, conditional_type,
                                                    conditionals, num_controls, controls);
    
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

/* Checks that a new branch block with conditional type EQ is initialized without 
interruption */
Test(branch_block_t, init_EQ)
{
    branch_block_t branch;
    int rc;
    int num_conditionals = 1;
    enum conditional_type conditional_type = EQ;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    rc = branch_block_init(&branch, num_conditionals, conditional_type, 
                            *conditionals, num_controls, *controls);

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
    enum conditional_type conditional_type = LTGT;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    rc = branch_block_init(&branch, num_conditionals, conditional_type,
                            *conditionals, num_controls, *controls);

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
    enum conditional_type conditional_type = LTEGTE;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    rc = branch_block_init(&branch, num_conditionals, conditional_type,
                            *conditionals, num_controls, *controls);

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
    enum conditional_type conditional_type = IN;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    rc = branch_block_init(&branch, num_conditionals, conditional_type,
                            *conditionals, num_controls, *controls);

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
    enum conditional_type conditional_type = EQ;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);
    
    branch = branch_block_new(num_conditionals, conditional_type, *conditionals, 
                                num_controls, controls);

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
    enum conditional_type conditional_type = LTGT;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    branch = branch_block_new(num_conditionals, conditional_type, *conditionals,
                                num_controls, controls);

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
    enum conditional_type conditional_type = LTEGTE;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    branch = branch_block_new(num_conditionals, conditional_type, *conditionals,
                                num_controls, controls);

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
    enum conditional_type conditional_type = IN;
    attribute_t* left = attribute_new(00, "attribute", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute", INTEGER, 2);
    conditional_block_t** conditionals = conditional_block_new(conditional_type, left, right);
    int num_controls = 1;
    AST_block_t* next = AST_block_new(control_block, CONTROL);
    control_block_t** controls = control_block_new(IFELSE, next);

    branch = branch_block_new(num_conditionals, conditional_type, *conditionals,
                                num_controls, controls);

    cr_assert_not_null(branch, "branch_block_new() failed");

    rc = branch_block_free(branch);

    cr_assert_eq(rc, SUCCESS, "branch_block_free() failed");
}
      
