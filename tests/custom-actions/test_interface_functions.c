#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_action.h"
#include "ast_block.h"
#include "control_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "branch_block.h"
#include "game-state/item.h"
#include "interface.h"

/* Checks that an empty custom_action fails */
Test(Interface,null_custom_action) {
    custom_action_t* ca = (custom_action_t*)malloc(sizeof(custom_action_t));
    char* string = "test";
    ca->action_name=string;
    ca->context=string;
    ca->item=string;
    ca->type=string;
    UT_hash_handle hh = hh;
    ca->hh=hh;
    ca->head = NULL;
    cr_assert_eq(do_custom_action(NULL),FAILURE, "do_custom_action didn't check for NULL input");
    cr_assert_eq(do_custom_action(ca),SUCCESS, "do_custom_action incorrectly checked for a NULL head");
}
