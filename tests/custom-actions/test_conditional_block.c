#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "conditional_block.h"

/* Checks that a new conditional block with type EQ is created without interruption */
Test(conditional_block_t, new_EQ)
{
    enum conditional_type conditional_type = EQ;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    conditional_block_t* new_conditional = conditional_block_new(conditional_type, 
                                                                left, right);

    cr_assert_not_null(new_conditional, "conditional_block_new() failed");

    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");

    conditional_block_free(new_conditional);
}


/* Checks that a new conditional block with type LTGT is created without interruption */
Test(conditional_block_t, new_LTGT)
{   
    enum conditional_type conditional_type = LTGT;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);
    
    conditional_block_t* new_conditional = conditional_block_new(conditional_type,
                                                                left, right);
    
    cr_assert_not_null(new_conditional, "conditional_block_new() failed");
    
    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");
    
    conditional_block_free(new_conditional);
}


/* Checks that a new conditional block with type LTEGTE is created without interruption */
Test(conditional_block_t, new_LTEGTE)
{   
    enum conditional_type conditional_type = LTEGTE;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);
    
    conditional_block_t* new_conditional = conditional_block_new(conditional_type,
                                                                left, right);
    
    cr_assert_not_null(new_conditional, "conditional_block_new() failed");
    
    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");
    
    conditional_block_free(new_conditional);
}


/* Checks that a new conditional block with type IN is created without interruption */
Test(conditional_block_t, new_IN)
{   
    enum conditional_type conditional_type = IN;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);
    
    conditional_block_t* new_conditional = conditional_block_new(conditional_type,
                                                                left, right);
    
    cr_assert_not_null(new_conditional, "conditional_block_new() failed");
    
    cr_assert_eq(new_conditional->conditional_type, conditional_type, "conditional_block_new() "
                "didn't set new_conditional->conditional_type");
    cr_assert_eq(new_conditional->left, left, "conditional_block_new() didn't set "
                "new_conditional->left");
    cr_assert_eq(new_conditional->right, right, "conditional_block_new() didn't set "
                "new_conditional->right");
    
    conditional_block_free(new_conditional);
}

/* Checks that a new conditional block with type EQ is initialized without interruption */
Test(conditional_block_t, init_EQ)
{
    conditional_block_t conditional;
    int rc;
    enum conditional_type conditional_type = EQ;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type LTGT is initialized without interruption */
Test(conditional_block_t, init_LTGT)
{
    conditional_block_t conditional;
    int rc;
    enum conditional_type conditional_type = LTGT;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type LTEGTE is initialized without interruption */
Test(conditional_block_t, init_LTEGTE)
{
    conditional_block_t conditional;
    int rc;
    enum conditional_type conditional_type = LTEGTE;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type IN is initialized without interruption */
Test(conditional_block_t, init_IN)
{
    conditional_block_t conditional;
    int rc;
    enum conditional_type conditional_type = IN;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                "conditional.right");
}

/* Checks that a new conditional block with type EQ is freed without interruption */
Test(conditional_block_t, free_EQ)
{
    conditional_block_t* conditional;
    int rc;
    enum conditional_type conditional_type = EQ;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}

/* Checks that a new conditional block with type LTGT is freed without interruption */
Test(conditional_block_t, free_LTGT)
{
    conditional_block_t* conditional;
    int rc;
    enum conditional_type conditional_type = LTGT;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}
   
/* Checks that a new conditional block with type LTEGTE is freed without interruption */
Test(conditional_block_t, free_LTEGTE)
{
    conditional_block_t* conditional;
    int rc;
    enum conditional_type conditional_type = LTEGTE;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}
   
/* Checks that a new conditional block with type IN is freed without interruption */
Test(conditional_block_t, free_IN)
{
    conditional_block_t* conditional;
    int rc;
    enum conditional_type conditional_type = IN;
    attribute_t* left = attribute_new(00, "attribute1", INTEGER, 1);
    attribute_t* right = attribute_new(01, "attribute2", INTEGER, 2);

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}
   
