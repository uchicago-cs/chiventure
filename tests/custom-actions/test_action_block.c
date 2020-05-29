#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_block.h"
#include "ast_block.h"
#include "game-state/item.h"

/* Checks that a new action block with SET type is created without interruption */
Test(action_block_t, new_SET)
{
    action_enum_t action_type = SET;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action_block_t* new_action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                 "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                 "set new_action->num_args");
    cr_assert_eq(new_action->args, &args, "action_block_new() didn't set "
                 "new_action->args");
    
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action_block_t* new_action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                 "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                 "set new_action->num_args");
    cr_assert_eq(new_action->args, &args, "action_block_new() didn't set "
                 "new_action->args");
    
    action_block_free(new_action);
}

/* Checks that a new action block with MOVE type is created without interruption */
Test(action_block_t, new_MOVE)
{
    action_enum_t action_type = MOVE;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action_block_t* new_action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                 "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                 "set new_action->num_args");
    cr_assert_eq(new_action->args, &args, "action_block_new() didn't set "
                 "new_action->args");
    
    action_block_free(new_action);
}

/* Checks that a new action block with ARITHMETIC type is created without interruption */
Test(action_block_t, new_ARITHMETIC)
{
    action_enum_t action_type = ARITHMETIC;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action_block_t* new_action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                 "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                 "set new_action->num_args");
    cr_assert_eq(new_action->args, &args, "action_block_new() didn't set "
                 "new_action->args");
    
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    
    action_block_t* new_action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                 "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                 "set new_action->num_args");
    cr_assert_eq(new_action->args, &args, "action_block_new() didn't set "
                 "new_action->args");
    
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action_block_t* new_action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                 "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                 "set new_action->num_args");
    cr_assert_eq(new_action->args, &args, "action_block_new() didn't set "
                 "new_action->args");
    
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t* ast = AST_action_block_new(action_type, num_args, &args);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                 "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->args, &args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t* ast = AST_action_block_new(action_type, num_args, &args);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                 "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->args, &args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                 "ast->block_type");
    
    AST_block_free(ast);
}

/* Checks that a new action AST block with MOVE type is created without interruption */
Test(AST_action_block_t, new_ast_MOVE)
{   
    action_enum_t action_type = MOVE;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    block_type_t block_type = ACTION;
    
    AST_block_t* ast = AST_action_block_new(action_type, num_args, &args);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                 "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->args, &args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->args");
    cr_assert_eq(ast->block_type, block_type, "AST_action_block_new() didn't set "
                 "ast->block_type");
    
    AST_block_free(ast);
}

/* Checks that a new action AST block with ARITHMETIC type is created without interruption */
Test(AST_action_block_t, new_ast_ARITHMETIC)
{   
    action_enum_t action_type = ARITHMETIC;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t* ast = AST_action_block_new(action_type, num_args, &args);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                 "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->args, &args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t* ast = AST_action_block_new(action_type, num_args, &args);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                 "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->args, &args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    block_type_t block_type = ACTION;

    AST_block_t* ast = AST_action_block_new(action_type, num_args, &args);

    cr_assert_not_null(ast, "AST_action_block_new() failed");

    cr_assert_eq(ast->block->action_block->action_type, action_type, "AST_action_block_new() didn't set "
                 "ast->block->action_block->action_type");
    cr_assert_eq(ast->block->action_block->num_args, num_args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->num_args");
    cr_assert_eq(ast->block->action_block->args, &args, "AST_action_block_new() didn't set "
                 "ast->block->action_block->args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, &args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                 "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                 "action.num_args");
    cr_assert_eq(action.args, &args, "action_block_init() didn't set action.args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, &args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                 "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                 "action.num_args");
    cr_assert_eq(action.args, &args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with MOVE type is initialized without interruption */
Test(action_block_t, init_MOVE)
{
    action_block_t action;
    int rc;
    action_enum_t action_type = MOVE;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, &args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                 "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                 "action.num_args");
    cr_assert_eq(action.args, &args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with ARITHMETIC type is initialized without interruption */
Test(action_block_t, init_ARITHMETIC)
{
    action_block_t action;
    int rc;
    action_enum_t action_type = ARITHMETIC;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, &args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                 "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                 "action.num_args");
    cr_assert_eq(action.args, &args, "action_block_init() didn't set action.args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, &args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                 "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                 "action.num_args");
    cr_assert_eq(action.args, &args, "action_block_init() didn't set action.args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    rc = action_block_init(&action, action_type, num_args, &args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                 "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                 "action.num_args");
    cr_assert_eq(action.args, &args, "action_block_init() didn't set action.args");
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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, &args);

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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with MOVE type is freed without interruption */
Test(action_block_t, free_MOVE)
{
    action_block_t *action;
    action_enum_t action_type = MOVE;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with ARITHMETIC type is freed without interruption */
Test(action_block_t, free_ARITHMETIC)
{
    action_block_t *action;
    action_enum_t action_type = ARITHMETIC;
    int rc;
    int num_args = 1;
    char *attr_name1 = "attribute1";
    enum attribute_tag attribute_tag = INTEGER;
    attribute_value_t attribute_value;
    attribute_value.int_val = 1;
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;
    
    action = action_block_new(action_type, num_args, &args);

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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, &args);

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
    attribute_t *args = malloc(sizeof(attribute_t));
    UT_hash_handle hh = hh;
    args->hh = hh;
    args->attribute_key = attr_name1;
    args->attribute_tag = attribute_tag;
    args->attribute_value = attribute_value;

    action = action_block_new(action_type, num_args, &args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
} 
