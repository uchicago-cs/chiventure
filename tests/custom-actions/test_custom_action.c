#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_action.h"
#include "ast_block.h"
#include "control_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "branch_block.h"

/* Checks that a new custom action with a control type AST block is created without 
interruption */
Test(custom_action_t, new_CONTROL)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONTROL;

    AST_block_t *head = AST_block_new(block, block_type);
    
    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";

    custom_action_t *new_action = custom_action_new(action_name, context, item, 
                                                    type, head);

    cr_assert_not_null(new_action, "custom_action_new failed");

    cr_assert_eq(new_action->action_name, action_name, "custom_action_new() didn't "
                 "set new_action->action_name");
    cr_assert_eq(new_action->context, context, "custom_action_new() didn't set "
                 "new_action->context");
    cr_assert_eq(new_action->item, item, "custom_action_new() didn't set "
                 "new_action->item");
    cr_assert_eq(new_action->type, type, "custom_action_new() didn't set "
                 "new_action->type");
    cr_assert_eq(new_action->head, head, "custom_action_new() didn't set "
                 "new_action->head");

    custom_action_free(new_action);
}

/* Checks that a new custom action with a branch type AST block is created without 
interruption */
Test(custom_action_t, new_BRANCH)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = BRANCH;

    AST_block_t *head = AST_block_new(block, block_type);
    
    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";

    custom_action_t *new_action = custom_action_new(action_name, context, item, 
                                                    type, head);

    cr_assert_not_null(new_action, "custom_action_new failed");

    cr_assert_eq(new_action->action_name, action_name, "custom_action_new() didn't "
                 "set new_action->action_name");
    cr_assert_eq(new_action->context, context, "custom_action_new() didn't set "
                 "new_action->context");
    cr_assert_eq(new_action->item, item, "custom_action_new() didn't set "
                 "new_action->item");
    cr_assert_eq(new_action->type, type, "custom_action_new() didn't set "
                 "new_action->type");
    cr_assert_eq(new_action->head, head, "custom_action_new() didn't set "
                 "new_action->head");

    custom_action_free(new_action);
}

/* Checks that a new custom action with a conditional type AST block is created without 
interruption */
Test(custom_action_t, new_CONDITIONAL)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONDITIONAL;

    AST_block_t *head = AST_block_new(block, block_type);
    
    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";

    custom_action_t *new_action = custom_action_new(action_name, context, item, 
                                                    type, head);

    cr_assert_not_null(new_action, "custom_action_new failed");

    cr_assert_eq(new_action->action_name, action_name, "custom_action_new() didn't "
                 "set new_action->action_name");
    cr_assert_eq(new_action->context, context, "custom_action_new() didn't set "
                 "new_action->context");
    cr_assert_eq(new_action->item, item, "custom_action_new() didn't set "
                 "new_action->item");
    cr_assert_eq(new_action->type, type, "custom_action_new() didn't set "
                 "new_action->type");
    cr_assert_eq(new_action->head, head, "custom_action_new() didn't set "
                 "new_action->head");

    custom_action_free(new_action);
}

/* Checks that a new custom action with an action type AST block is created without 
interruption */
Test(custom_action_t, new_ACTION)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = ACTION;

    AST_block_t *head = AST_block_new(block, block_type);
    
    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";

    custom_action_t *new_action = custom_action_new(action_name, context, item, 
                                                    type, head);

    cr_assert_not_null(new_action, "custom_action_new failed");

    cr_assert_eq(new_action->action_name, action_name, "custom_action_new() didn't "
                 "set new_action->action_name");
    cr_assert_eq(new_action->context, context, "custom_action_new() didn't set "
                 "new_action->context");
    cr_assert_eq(new_action->item, item, "custom_action_new() didn't set "
                 "new_action->item");
    cr_assert_eq(new_action->type, type, "custom_action_new() didn't set "
                 "new_action->type");
    cr_assert_eq(new_action->head, head, "custom_action_new() didn't set "
                 "new_action->head");

    custom_action_free(new_action);
}

/* Checks that a new custom action with a control type AST block is initialized 
without interruption */
Test(custom_action_t, init_CONTROL)
{ 
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONTROL;

    AST_block_t *head = AST_block_new(block, block_type);

    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;
    custom_action_t action;

    rc = custom_action_init(&action, action_name, context, item, type, head);

    cr_assert_eq(rc, SUCCESS, "custom_action_init() failed");
    cr_assert_eq(action.action_name, action_name, "custom_action_init() didn't "
                 "set action.action_name");
    cr_assert_eq(action.context, context, "custom_action_init() didn't set "
                 "action.context");
    cr_assert_eq(action.item, item, "custom_action_init() didn't set action.item");
    cr_assert_eq(action.type, type, "custom_action_init() didn't set action.type");
    cr_assert_eq(action.head, head, "custom_action_init() didn't set action.head");
}

/* Checks that a new custom action with a branch type AST block is initialized 
without interruption */
Test(custom_action_t, init_BRANCH)
{  
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = BRANCH;

    AST_block_t *head = AST_block_new(block, block_type);
    
    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;
    custom_action_t action;
    
    rc = custom_action_init(&action, action_name, context, item, type, head);
    
    cr_assert_eq(rc, SUCCESS, "custom_action_init() failed");
    cr_assert_eq(action.action_name, action_name, "custom_action_init() didn't "
                 "set action.action_name");
    cr_assert_eq(action.context, context, "custom_action_init() didn't set "
                 "action.context");
    cr_assert_eq(action.item, item, "custom_action_init() didn't set action.item");
    cr_assert_eq(action.type, type, "custom_action_init() didn't set action.type");
    cr_assert_eq(action.head, head, "custom_action_init() didn't set action.head");
}

/* Checks that a new custom action with a conditional type AST block is initialized 
without interruption */
Test(custom_action_t, init_CONDITIONAL)
{  
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONDITIONAL;

    AST_block_t *head = AST_block_new(block, block_type);
    
    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;
    custom_action_t action;
    
    rc = custom_action_init(&action, action_name, context, item, type, head);
    
    cr_assert_eq(rc, SUCCESS, "custom_action_init() failed");
    cr_assert_eq(action.action_name, action_name, "custom_action_init() didn't "
                 "set action.action_name");
    cr_assert_eq(action.context, context, "custom_action_init() didn't set "
                 "action.context");
    cr_assert_eq(action.item, item, "custom_action_init() didn't set action.item");
    cr_assert_eq(action.type, type, "custom_action_init() didn't set action.type");
    cr_assert_eq(action.head, head, "custom_action_init() didn't set action.head");
}

/* Checks that a new custom action with an action type AST block is initialized 
without interruption */
Test(custom_action_t, init_ACTION)
{  
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = ACTION;

    AST_block_t *head = AST_block_new(block, block_type);
    
    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;
    custom_action_t action;
    
    rc = custom_action_init(&action, action_name, context, item, type, head);
    
    cr_assert_eq(rc, SUCCESS, "custom_action_init() failed");
    cr_assert_eq(action.action_name, action_name, "custom_action_init() didn't "
                 "set action.action_name");
    cr_assert_eq(action.context, context, "custom_action_init() didn't set "
                 "action.context");
    cr_assert_eq(action.item, item, "custom_action_init() didn't set action.item");
    cr_assert_eq(action.type, type, "custom_action_init() didn't set action.type");
    cr_assert_eq(action.head, head, "custom_action_init() didn't set action.head");
}

/* Checks that a new custom action with a control type AST block is freed without
interruption */
Test(custom_action_t, free_CONTROL)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONTROL;

    AST_block_t *head = AST_block_new(block, block_type);

    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;

    custom_action_t *action = custom_action_new(action_name, context, item, type, head);

    cr_assert_not_null(action, "custom_action_new() failed");
    
    rc = custom_action_free(action);

    cr_assert_eq(rc, SUCCESS, "custom_action_free() failed");
}

/* Checks that a new custom action with a branch type AST block is freed without
interruption */
Test(custom_action_t, free_BRANCH)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = BRANCH;

    AST_block_t *head = AST_block_new(block, block_type);

    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;

    custom_action_t *action = custom_action_new(action_name, context, item, type, head);

    cr_assert_not_null(action, "custom_action_new() failed");
    
    rc = custom_action_free(action);

    cr_assert_eq(rc, SUCCESS, "custom_action_free() failed");
}

/* Checks that a new custom action with a conditional type AST block is freed without
interruption */
Test(custom_action_t, free_CONDITIONAL)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = CONDITIONAL;

    AST_block_t *head = AST_block_new(block, block_type);

    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;

    custom_action_t *action = custom_action_new(action_name, context, item, type, head);

    cr_assert_not_null(action, "custom_action_new() failed");
    
    rc = custom_action_free(action);

    cr_assert_eq(rc, SUCCESS, "custom_action_free() failed");
}

/* Checks that a new custom action with an action type AST block is freed without
interruption */
Test(custom_action_t, free_ACTION)
{
    block_t *block = malloc(sizeof(block_t));
    block_type_t block_type = ACTION;

    AST_block_t *head = AST_block_new(block, block_type);

    char *action_name = "act_PUSH";
    char *context = "item";
    char *item = "obj_CHAIR";
    char *type = "paladin";
    int rc;

    custom_action_t *action = custom_action_new(action_name, context, item, type, head);

    cr_assert_not_null(action, "custom_action_new() failed");
    
    rc = custom_action_free(action);

    cr_assert_eq(rc, SUCCESS, "custom_action_free() failed");
}
