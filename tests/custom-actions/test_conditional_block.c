#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "conditional_block.h"
#include "game-state/item.h"
#include "ast_block.h"

/* Checks that a new conditional block with type EQ is created without interruption */
Test(conditional_block_t, new_EQ)
{
    conditional_type_t conditional_type = EQ;
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

/* Checks that a new conditional block with type LTB is created without interruption */
Test(conditional_block_t, new_LTB)
{   
    conditional_type_t conditional_type = LTB;
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

/* Checks that a new conditional block with type LTEB is created without interruption */
Test(conditional_block_t, new_LTEB)
{   
    conditional_type_t conditional_type = LTEB;
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
    conditional_type_t conditional_type = IN;
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

/* Checks that a new AST conditional block with type EQ is created without interruption */
Test(conditional_block_t, new_AST_EQ)
{
    conditional_type_t conditional_type = EQ;
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
    block_type_t block_type = CONDITIONAL;
   
    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                     left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block->conditional_block->conditional_type, conditional_type, "AST_conditional_block_new() "
                 "didn't set new_ast->block->conditional_block->conditional_type");
    cr_assert_eq(new_ast->block->conditional_block->left, left, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->left");
    cr_assert_eq(new_ast->block->conditional_block->right, right, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->right");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                 "new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST conditional block with type IN is created without interruption */
Test(conditional_block_t, new_AST_IN)
{
    conditional_type_t conditional_type = IN;
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
    block_type_t block_type = CONDITIONAL;
    
    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                     left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block->conditional_block->conditional_type, conditional_type, "AST_conditional_block_new() "
                 "didn't set new_ast->block->conditional_block->conditional_type");
    cr_assert_eq(new_ast->block->conditional_block->left, left, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->left");
    cr_assert_eq(new_ast->block->conditional_block->right, right, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->right");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                 "new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST conditional block with type LTB is created without interruption */
Test(conditional_block_t, new_AST_LTB)
{
    conditional_type_t conditional_type = LTB;
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
    block_type_t block_type = CONDITIONAL;
    
    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                     left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block->conditional_block->conditional_type, conditional_type, "AST_conditional_block_new() "
                 "didn't set new_ast->block->conditional_block->conditional_type");
    cr_assert_eq(new_ast->block->conditional_block->left, left, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->left");
    cr_assert_eq(new_ast->block->conditional_block->right, right, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->right");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                 "new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new AST conditional block with type LTEB is created without interruption */
Test(conditional_block_t, new_AST_LTEB)
{
    conditional_type_t conditional_type = LTEB;
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
    block_type_t block_type = CONDITIONAL;
    
    AST_block_t* new_ast = AST_conditional_block_new(conditional_type, 
                                                     left, right);

    cr_assert_not_null(new_ast, "AST_conditional_block_new() failed");

    cr_assert_eq(new_ast->block->conditional_block->conditional_type, conditional_type, "AST_conditional_block_new() "
                 "didn't set new_ast->block->conditional_block->conditional_type");
    cr_assert_eq(new_ast->block->conditional_block->left, left, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->left");
    cr_assert_eq(new_ast->block->conditional_block->right, right, "AST_conditional_block_new() didn't set "
                 "new_ast->block->conditional_block->right");
    cr_assert_eq(new_ast->block_type, block_type, "AST_conditional_block_new() didn't set "
                 "new_ast->block_type");

    AST_block_free(new_ast);
}

/* Checks that a new conditional block with type EQ is initialized without interruption */
Test(conditional_block_t, init_EQ)
{
    conditional_block_t conditional;
    int rc;
    conditional_type_t conditional_type = EQ;
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

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                 "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                 "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                 "conditional.right");
}

/* Checks that a new conditional block with type LTB is initialized without interruption */
Test(conditional_block_t, init_LTB)
{
    conditional_block_t conditional;
    int rc;
    conditional_type_t conditional_type = LTB;
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

    rc = conditional_block_init(&conditional, conditional_type, left, right);

    cr_assert_eq(rc, SUCCESS, "conditional_block_init() failed");
    cr_assert_eq(conditional.conditional_type, conditional_type, "conditional_block_init() "
                 "didn't set conditional.conditional_type");
    cr_assert_eq(conditional.left, left, "conditional_block_init() didn't set "
                 "conditional.left");
    cr_assert_eq(conditional.right, right, "conditional_block_init() didn't set "
                 "conditional.right");
}

/* Checks that a new conditional block with type LTEB is initialized without interruption */
Test(conditional_block_t, init_LTEB)
{
    conditional_block_t conditional;
    int rc;
    conditional_type_t conditional_type = LTEB;
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
    conditional_type_t conditional_type = IN;
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
    conditional_type_t conditional_type = EQ;
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

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}

/* Checks that a new conditional block with type LTB is freed without interruption */
Test(conditional_block_t, free_LTB)
{
    conditional_block_t* conditional;
    int rc;
    conditional_type_t conditional_type = LTB;
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

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}
   
/* Checks that a new conditional block with type LTEB is freed without interruption */
Test(conditional_block_t, free_LTEB)
{
    conditional_block_t* conditional;
    int rc;
    conditional_type_t conditional_type = LTEB;
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
    conditional_type_t conditional_type = IN;
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

    conditional = conditional_block_new(conditional_type, left, right);

    cr_assert_not_null(conditional, "conditional_block_new() failed");

    rc = conditional_block_free(conditional);

    cr_assert_eq(rc, SUCCESS, "conditional_block_free() failed");
}

/* Checks the functionality of eval_conditional_block with equality */
Test(conditional_block_t, eval_cond_eq)
{
  conditional_block_t* conditional;
  int rc;
  conditional_type_t conditional_type = EQ;
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t attribute_value1;
  attribute_value_t attribute_value2;
  
  attribute_value1.int_val = 1;
  attribute_value2.int_val = 2;
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = attribute_value1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = attribute_value2;
  
  conditional = conditional_block_new(conditional_type, left, right);
  cr_assert_not_null(conditional, "conditional_block_new() failed");

  cr_assert_eq(eval_conditional_block(conditional), 0, "Incorrectly thought that 1 and 2 were equal");
  right->attribute_value = attribute_value1;
  cr_assert_eq(eval_conditional_block(conditional), 1, "Incorrectly thought that 1 and 1 were not equal");
  attribute_free(left);
  attribute_free(right);
  conditional_block_free(conditional);
}

/* Checks the functionality of eval_conditional_block with less than and greater than */
Test(conditional_block_t, eval_cond_LTGT)
{
  conditional_block_t* conditional;
  int rc;
  conditional_type_t conditional_type = LTB;
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t attribute_value1;
  attribute_value_t attribute_value2;

  attribute_value1.int_val = 1;
  attribute_value2.int_val = 2;
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = attribute_value1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = attribute_value2;

  conditional = conditional_block_new(conditional_type, left, right);
  cr_assert_not_null(conditional, "conditional_block_new() failed");

  cr_assert_eq(eval_conditional_block(conditional), 1, "Incorrectly thought that 1 was greater than or equal to 2");
  right->attribute_value = attribute_value1;
  cr_assert_eq(eval_conditional_block(conditional), 0, "Less than did not properly evaluate equality");
  conditional->conditional_type = GTB;
  cr_assert_eq(eval_conditional_block(conditional), 0, "Greater than did not properly evaluate equality");
  right->attribute_value = attribute_value2;
  cr_assert_eq(eval_conditional_block(conditional), 0, "Incorrectly thoguht that 1 was greater than 2");
  attribute_free(left);
  attribute_free(right);
  conditional_block_free(conditional);
}

/* Checks the functionality of eval_conditional_block with less than equal and greater than equal*/
Test(conditional_block_t, eval_cond_LTEGTE)
{
  conditional_block_t* conditional;
  int rc;
  conditional_type_t conditional_type = LTEB;
  char *attr_name1 = "attribute1";
  char *attr_name2 = "attribute2";
  enum attribute_tag attribute_tag = INTEGER;
  attribute_value_t attribute_value1;
  attribute_value_t attribute_value2;

  attribute_value1.int_val = 1;
  attribute_value2.int_val = 2;
  attribute_t *left = malloc(sizeof(attribute_t));
  UT_hash_handle hh = hh;
  left->hh = hh;
  left->attribute_key = strdup(attr_name1);
  left->attribute_tag = attribute_tag;
  left->attribute_value = attribute_value1;
  attribute_t *right = malloc(sizeof(attribute_t));
  right->hh = hh;
  right->attribute_key = strdup(attr_name2);
  right->attribute_tag = attribute_tag;
  right->attribute_value = attribute_value2;

  conditional = conditional_block_new(conditional_type, left, right);
  cr_assert_not_null(conditional, "conditional_block_new() failed");

  cr_assert_eq(eval_conditional_block(conditional), 1, "Incorrectly thought that 1 was greater than or equal to 2");
  right->attribute_value = attribute_value1;
  cr_assert_eq(eval_conditional_block(conditional), 1, "Less than equal did not properly evaluate equality");
  conditional->conditional_type = GTEB;
  cr_assert_eq(eval_conditional_block(conditional), 1, "Greater than equal did not properly evaluate equality");
  right->attribute_value = attribute_value2;
  cr_assert_eq(eval_conditional_block(conditional), 0, "Incorrectly thoguht that 1 was greater than 2");
  attribute_free(right);
  attribute_free(left);
  conditional_block_free(conditional);
}
