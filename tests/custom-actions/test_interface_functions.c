#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_block.h"
#include "ast_block.h"
#include "game-state/item.h"
#include "interface.h"

/* Checks that an empty custom_action fails */
Test(Interface,do_custom_action+bad_custom_action) {
    custom_action_t* ca = custom_action_new("test","test","test","test",NULL);  
    cr_assert_eq(do_custom_action(NULL),FAILURE, "do_custom_action didn't check for NULL input");
    cr_assert_eq(do_custom_action(ca),FAILURE, "do_custom_action didn't check for NULL head");
}
/* Checks that a custom_action with a bad branch block fails */
Test(Interface,do_custom_action+bad_branch) {
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
    branch_block_t* new_branch = branch_block_new(1, &conditionals, conditional_type, 2, &controls);
    custom_action_t* ca = custom_action_new("act_PUSH","item","obj_CHAIR","paladin");

    cr_assert_eq(do_custom_action(ca),FAILURE, "do_custom_action didn't recognize branch block had wrong arguments");
}
