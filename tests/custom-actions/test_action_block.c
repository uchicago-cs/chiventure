#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_block.h"
#include "ast_block.h"
#include "game-state/item.h"
#include "game-state/game.h"
#include "game-state/room.h"

/* Checks that a new action block with SET type is created without interruption */
Test(action_block_t, new_SET)
{
    action_enum_t action_type = SET;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action_block_t *new_action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                                                       "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                                                 "set new_action->num_args");
    cr_assert_eq(new_action->action_params->args, action_params->args, "action_block_new() didn't set "
                                                                        "new_action->action_params->args");

    action_block_free(new_action);
}

/* Checks that a new action block with SAY type is created without interruption */
Test(action_block_t, new_SAY)
{
    action_enum_t action_type = SAY;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action_block_t *new_action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                                                       "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                                                 "set new_action->num_args");
    cr_assert_eq(new_action->action_params->args, action_params->args, "action_block_new() didn't set "
                                                                        "new_action->action_params->args");

    action_block_free(new_action);
}

/* Checks that a new action block with TELEPORT type is created without interruption */
Test(action_block_t, new_TELEPORT)
{
    action_enum_t action_type = TELEPORT;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action_block_t *new_action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                                                       "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                                                 "set new_action->num_args");
    cr_assert_eq(new_action->action_params->args, action_params->args, "action_block_new() didn't set "
                                                                        "new_action->action_params->args");

    action_block_free(new_action);
}

/* Checks that a new action block with ADDITION type is created without interruption */
Test(action_block_t, new_ADDITION)
{
    action_enum_t action_type = ADDITION;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action_block_t *new_action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                                                       "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                                                 "set new_action->num_args");
    cr_assert_eq(new_action->action_params->args, action_params->args, "action_block_new() didn't set "
                                                                        "new_action->action_params->args");

    action_block_free(new_action);
}

/* Checks that a new action block with GEN type is created without interruption */
Test(action_block_t, new_GEN)
{
    action_enum_t action_type = GEN;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action_block_t *new_action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                                                       "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                                                 "set new_action->num_args");
    cr_assert_eq(new_action->action_params->args, action_params->args, "action_block_new() didn't set "
                                                                        "new_action->action_params->args");

    action_block_free(new_action);
}

/* Checks that a new action block with EXEC type is created without interruption */
Test(action_block_t, new_EXEC)
{
    action_enum_t action_type = EXEC;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action_block_t *new_action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                                                       "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                                                 "set new_action->num_args");
    cr_assert_eq(new_action->action_params->args, action_params->args, "action_block_new() didn't set "
                                                                        "new_action->action_params->args");

    action_block_free(new_action);
}

/* Checks that a new action AST block with SET type is created without interruption */
Test(AST_action_block_t, new_ast_SET)
{
    action_enum_t action_type = SET;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t *ast = AST_action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                                                                     "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                                                               "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->action_params->args, action_params->args, "AST_action_block_new() didn't set "
                                                                                      "ast->block->action_block->action_params->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                                              "ast->block_type");

    AST_block_free(ast);
}

/* Checks that a new action AST block with SAY type is created without interruption */
Test(AST_action_block_t, new_ast_SAY)
{
    action_enum_t action_type = SAY;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t *ast = AST_action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                                                                     "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                                                               "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->action_params->args, action_params->args, "AST_action_block_new() didn't set "
                                                                                      "ast->block->action_block->action_params->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                                              "ast->block_type");

    AST_block_free(ast);
}

/* Checks that a new action AST block with TELEPORT type is created without interruption */
Test(AST_action_block_t, new_ast_TELEPORT)
{
    action_enum_t action_type = TELEPORT;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t *ast = AST_action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                                                                     "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                                                               "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->action_params->args, action_params->args, "AST_action_block_new() didn't set "
                                                                                      "ast->block->action_block->action_params->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                                              "ast->block_type");

    AST_block_free(ast);
}

/* Checks that a new action AST block with ADDITION type is created without interruption */
Test(AST_action_block_t, new_ast_ADDITION)
{
    action_enum_t action_type = ADDITION;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh; 
    args[0]->hh = hh;
    args[0]->attribute_key = attr_name1;
    args[0]->attribute_tag = attribute_tag;
    args[0]->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t *ast = AST_action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                                                                     "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                                                               "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->action_params->args, action_params->args, "AST_action_block_new() didn't set "
                                                                                      "ast->block->action_block->action_params->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                                              "ast->block_type");

    AST_block_free(ast);
}

/* Checks that a new action AST block with GEN type is created without interruption */
Test(AST_action_block_t, new_ast_GEN)
{
    action_enum_t action_type = GEN;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t *ast = AST_action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                                                                     "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                                                               "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->action_params->args, action_params->args, "AST_action_block_new() didn't set "
                                                                                      "ast->block->action_block->action_params->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                                              "ast->block_type");

    AST_block_free(ast);
}

/* Checks that a new action AST block with EXEC type is created without interruption */
Test(AST_action_block_t, new_ast_EXEC)
{
    action_enum_t action_type = EXEC;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t *ast = AST_action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                                                                     "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                                                               "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->action_params->args, action_params->args, "AST_action_block_new() didn't set "
                                                                                      "ast->block->action_block->action_params->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                                              "ast->block_type");

    AST_block_free(ast);
}

/* Checks that a new action block with SET type is initialized without interruption */
Test(action_block_t, init_SET)
{
    action_block_t action;
    int rc;
    action_enum_t action_type = SET;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, action_params);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                                                  "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                                            "action.num_args");
    cr_assert_eq(action.action_params->args, action_params->args, "action_block_init() didn't set action.action_params->args");
}

/* Checks that a new action block with SAY type is initialized without interruption */
Test(action_block_t, init_SAY)
{
    action_block_t action;
    int rc;
    action_enum_t action_type = SAY;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, action_params);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                                                  "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                                            "action.num_args");
    cr_assert_eq(action.action_params->args, action_params->args, "action_block_init() didn't set action.action_params->args");
}

/* Checks that a new action block with TELEPORT type is initialized without interruption */
Test(action_block_t, init_MOVE)
{
    action_block_t action;
    int rc;
    action_enum_t action_type = TELEPORT;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, action_params);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                                                  "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                                            "action.num_args");
    cr_assert_eq(action.action_params->args, action_params->args, "action_block_init() didn't set action.action_params->args");
}

/* Checks that a new action block with ADDITION type is initialized without interruption */
Test(action_block_t, init_ADDITION)
{
    action_block_t action;
    int rc;
    action_enum_t action_type = ADDITION;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, action_params);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                                                  "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                                            "action.num_args");
    cr_assert_eq(action.action_params->args, action_params->args, "action_block_init() didn't set action.action_params->args");
}

/* Checks that a new action block with GEN type is initialized without interruption */
Test(action_block_t, init_GEN)
{
    action_block_t action;
    int rc;
    action_enum_t action_type = GEN;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, action_params);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                                                  "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                                            "action.num_args");
    cr_assert_eq(action.action_params->args, action_params->args, "action_block_init() didn't set action.action_params->args");
}

/* Checks that a new action block with EXEC type is initialized without interruption */
Test(action_block_t, init_EXEC)
{
    action_block_t action;
    int rc;
    int num_args = 1;
    action_enum_t action_type = EXEC;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, action_params);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                                                  "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                                            "action.num_args");
    cr_assert_eq(action.action_params->args, action_params->args, "action_block_init() didn't set action.action_params->args");
}

/* Checks that a new action block with SET type is freed without interruption */
Test(action_block_t, free_SET)
{
    action_block_t *action;
    action_enum_t action_type = SET;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with SAY type is freed without interruption */
Test(action_block_t, free_SAY)
{
    action_block_t *action;
    action_enum_t action_type = SAY;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with TELEPORT type is freed without interruption */
Test(action_block_t, free_TELEPORT)
{
    action_block_t *action;
    action_enum_t action_type = TELEPORT;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with ADDITION type is freed without interruption */
Test(action_block_t, free_ADDITION)
{
    action_block_t *action;
    action_enum_t action_type = ADDITION;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with GEN type is freed without interruption */
Test(action_block_t, free_GEN)
{
    action_block_t *action;
    action_enum_t action_type = GEN;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with EXEC type is freed without interruption */
Test(action_block_t, free_EXEC)
{
    action_block_t *action;
    action_enum_t action_type = EXEC;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    action_param_t *action_params = malloc(sizeof(action_param_t));
    attribute_t **args = malloc(sizeof(attribute_t*));
    attribute_t *arg = malloc(sizeof(attribute_t));
    args[0] = arg; 
    action_params->args = args; 
    UT_hash_handle hh = hh;
    args[0]->hh = hh;
    action_params->args[0]->attribute_key = attr_name1;
    action_params->args[0]->attribute_tag = attribute_tag;
    action_params->args[0]->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, action_params);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Tests behavior of action block execution function with actions that
 *  set attribute values
 */
Test(exec_action_block, set)
{
    action_block_t *act1, *act2, *act3;
    action_param_t *action_params1, *action_params2;
    attribute_t **args1, **args2;
    attribute_t *attr1, *attr2, *attr3;
    attribute_value_t val1, val2, val3;
    int rc1, rc2, rc3;

    attr1 = malloc(sizeof(attribute_t));
    attr1->attribute_key = "attr1";
    attr1->attribute_tag = INTEGER;
    val1.int_val = 1;
    attr1->attribute_value = val1;

    attr2 = malloc(sizeof(attribute_t));
    attr2->attribute_key = "attr2";
    attr2->attribute_tag = INTEGER;
    val2.int_val = 2;
    attr2->attribute_value = val2;

    attr3 = malloc(sizeof(attribute_t));
    attr3->attribute_key = "attr3";
    attr3->attribute_tag = CHARACTER;
    val3.char_val = 'b';
    attr3->attribute_value = val3;

    args1 = (attribute_t**)malloc(sizeof(attribute_t*) * 2);
    args1[0] = attr1;
    args1[1] = attr2;

    args2 = (attribute_t**)malloc(sizeof(attribute_t*) * 2);
    args2[0] = attr1;
    args2[1] = attr3;

    action_params1 = (action_param_t*)malloc(sizeof(action_param_t));
    action_params2 = (action_param_t*)malloc(sizeof(action_param_t));

    action_params1->args = args1;
    action_params2->args = args2;

    act1 = action_block_new(SET, 2, action_params1);
    act2 = action_block_new(SET, 3, action_params1);
    act3 = action_block_new(SET, 2, action_params2);

    rc1 = exec_action_block(act1);
    rc2 = exec_action_block(act2);
    rc3 = exec_action_block(act3);

    cr_assert_eq(rc1, SUCCESS, "Expected SUCCESS but exec_action_block "
                               "returned FAILURE with action type SET");
    cr_assert_eq(attr1->attribute_value.int_val, 2,
                 "exec_action_block() failed to set value of attribute");

    cr_assert_eq(rc2, FAILURE, "exec_action_block() failed to recognize "
                               "invalid number of arguments");

    cr_assert_eq(rc3, FAILURE, "exec_action_block() failed to recognize "
                               "failure of effect-applying function");
}

/* Helper to test action block execution with arithmetic action types
 */
void test_arithmetic_act(int i1, int i2, int exp, action_enum_t op)
{
    action_block_t *act1, *act2, *act3;
    attribute_t **args1, **args2;
    attribute_t *attr1, *attr2, *attr3, *attr4;
    action_param_t *action_params1, *action_params2;
    attribute_value_t val1, val2, val3, val4;
    int rc1, rc2, rc3;

    attr1 = malloc(sizeof(attribute_t));
    attr1->attribute_key = "attr1";
    attr1->attribute_tag = INTEGER;
    val1.int_val = i1;
    attr1->attribute_value = val1;

    attr2 = malloc(sizeof(attribute_t));
    attr2->attribute_key = "attr2";
    attr2->attribute_tag = INTEGER;
    val2.int_val = i2;
    attr2->attribute_value = val2;

    attr3 = malloc(sizeof(attribute_t));
    attr3->attribute_key = "attr3";
    attr3->attribute_tag = CHARACTER;
    val3.char_val = 'b';
    attr3->attribute_value = val3;

    attr4 = malloc(sizeof(attribute_t));
    attr4->attribute_key = "attr2";
    attr4->attribute_tag = INTEGER;
    val4.int_val = 0;
    attr4->attribute_value = val4;

    args1 = (attribute_t**)malloc(sizeof(attribute_t*) * 3);
    args1[0] = attr1;
    args1[1] = attr2;
    args1[2] = attr4;

    args2 = (attribute_t**)malloc(sizeof(attribute_t*) * 3);
    args2[0] = attr1;
    args2[1] = attr3;
    args2[2] = attr4;

    action_params1 = (action_param_t*)malloc(sizeof(action_param_t));
    action_params2 = (action_param_t*)malloc(sizeof(action_param_t));

    action_params1->args = args1;
    action_params2->args = args2;

    act1 = action_block_new(op, 3, action_params1);
    act2 = action_block_new(op, 2, action_params1);
    act3 = action_block_new(op, 3, action_params2);

    rc1 = exec_action_block(act1);
    rc2 = exec_action_block(act2);
    rc3 = exec_action_block(act3);

    cr_assert_eq(rc1, SUCCESS, "Expected SUCCESS but exec_action_block "
                               "returned FAILURE");
    cr_assert_eq(attr4->attribute_value.int_val, exp,
                 "exec_action_block() failed to store result in attribute");

    cr_assert_eq(rc2, FAILURE, "exec_action_block() failed to recognize "
                               "invalid number of arguments");

    cr_assert_eq(rc3, FAILURE, "exec_action_block() failed to recognize "
                               "failure of effect-applying function");
}

/* Tests behavior of action block execution function with actions that
 *  add attribute values
 */
Test(exec_action_block, add)
{
    test_arithmetic_act(1, 2, 3, ADDITION);
}

/* Tests behavior of action block execution function with actions that
 *  subtract attribute values
 */
Test(exec_action_block, subtract)
{
    test_arithmetic_act(1, 2, -1, SUBTRACT);
}

/* Tests behavior of action block execution function with actions that
 *  multiply attribute values
 */
Test(exec_action_block, multiply)
{
    test_arithmetic_act(3, 8, 24, MULTIPLY);
}

/* Tests behavior of action block execution function with actions that
 *  divide attribute values
 */
Test(exec_action_block, divide)
{
    test_arithmetic_act(12, 3, 4, DIVIDE);
}

/* Tests behavior of action block execution function with actions that
 *  generate an attribute value
 */
Test(exec_action_block, gen)
{
    action_block_t *act1, *act2, *act3;
    attribute_t **args1, **args2;
    action_param_t *action_params1, *action_params2;
    attribute_t *attr1, *attr2, *attr3, *attr4;
    attribute_value_t val1, val2, val3, val4;
    int rc1, rc2, rc3;

    attr1 = malloc(sizeof(attribute_t));
    attr1->attribute_key = "attr1";
    attr1->attribute_tag = INTEGER;
    val1.int_val = 1;
    attr1->attribute_value = val1;

    attr2 = malloc(sizeof(attribute_t));
    attr2->attribute_key = "attr2";
    attr2->attribute_tag = INTEGER;
    val2.int_val = 10;
    attr2->attribute_value = val2;

    attr3 = malloc(sizeof(attribute_t));
    attr3->attribute_key = "attr3";
    attr3->attribute_tag = CHARACTER;
    val3.char_val = 'b';
    attr3->attribute_value = val3;

    attr4 = malloc(sizeof(attribute_t));
    attr4->attribute_key = "attr2";
    attr4->attribute_tag = INTEGER;
    val4.int_val = 0;
    attr4->attribute_value = val4;

    args1 = (attribute_t**)malloc(sizeof(attribute_t*) * 3);
    args1[0] = attr1;
    args1[1] = attr2;
    args1[2] = attr4;

    args2 = (attribute_t**)malloc(sizeof(attribute_t*) * 3);
    args2[0] = attr1;
    args2[1] = attr3;
    args2[2] = attr4;

    action_params1 = (action_param_t*)malloc(sizeof(action_param_t));
    action_params2 = (action_param_t*)malloc(sizeof(action_param_t));

    action_params1->args = args1;
    action_params2->args = args2;

    act1 = action_block_new(GEN, 3, action_params1);
    act2 = action_block_new(GEN, 2, action_params1);
    act3 = action_block_new(GEN, 3, action_params2);

    rc1 = exec_action_block(act1);
    rc2 = exec_action_block(act2);
    rc3 = exec_action_block(act3);

    cr_assert_eq(rc1, SUCCESS, "Expected SUCCESS but exec_action_block "
                               "returned FAILURE with action type GEN");
    cr_assert_geq(attr4->attribute_value.int_val, 0,
                  "exec_action_block() failed to store sum in attribute");
    cr_assert_leq(attr4->attribute_value.int_val, 10,
                  "exec_action_block() failed to store sum in attribute");

    cr_assert_eq(rc2, FAILURE, "exec_action_block() failed to recognize "
                               "invalid number of arguments");

    cr_assert_eq(rc3, FAILURE, "exec_action_block() failed to recognize "
                               "failure of effect-applying function");
}

/* Tests behavior of action block execution function with actions that
 *  teleport a player
 */
Test(exec_action_block, teleport)
{
    action_block_t *act1, *act2, *act3;
    game_t *game1 = game_new("Welcome to Chiventure!");
    game_t *game2 = game_new("Welcome to Chiventure 2!");
    room_t *room1 = room_new("vroom1", "test room", "yes this is a test room");
    room_t *room2 = room_new("nroom", "test next door", "KND number 1");
    room_t *room3 = room_new("xroom", "last room", "here");
    action_param_t *action_params1, *action_params2;
    int rc1, rc2, rc3;
    add_room_to_game(game1, room1);
    add_room_to_game(game1, room2);
    add_room_to_game(game1, room3);
    add_room_to_game(game2, room1);
    add_room_to_game(game2, room2);
    add_room_to_game(game2, room3);
    game1->curr_room = room1;
    game2->curr_room = room1;

    action_params1 = (action_param_t*)malloc(sizeof(action_param_t));
    action_params2 = (action_param_t*)malloc(sizeof(action_param_t));

    action_params1->game = game1;
    action_params1->room = room2;

    action_params2->game = game2;
    action_params2->room = room3;

    act1 = action_block_new(TELEPORT, 2, action_params1);
    act2 = action_block_new(TELEPORT, 1, action_params1);
    act3 = action_block_new(TELEPORT, 2, action_params2);

    rc1 = exec_action_block(act1);
    rc2 = exec_action_block(act2);
    rc3 = exec_action_block(act3);

    cr_assert_eq(rc1, SUCCESS, "Expected SUCCESS but exec_action_block "
                               "returned FAILURE with action type TELEPORT");

    cr_assert_eq(rc2, FAILURE, "exec_action_block() failed to recognize "
                               "invalid number of arguments");

    cr_assert_eq(rc1, SUCCESS, "Expected SUCCESS but exec_action_block "
                               "returned FAILURE with action type TELEPORT");
    cr_assert_str_eq(game1->curr_room->room_id, room2->room_id,
                     "Expected curr_room to be room2"
                     "returned a different room with action type TELEPORT");
    cr_assert_str_eq(game2->curr_room->room_id, room3->room_id,
                     "Expected curr_room to be room3"
                     "returned a different room with action type TELEPORT");
}
