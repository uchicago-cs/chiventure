#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "action_block.h"
#include "item.h"
#include "attribute_functions.h"

/* Checks that a new action block with SET type is created without interruption */
Test(action_block_t, new_SET)
{
    action_type_t action_type = SET;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    *args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                "set new_action->num_args");
    cr_assert_eq(new_action->args, args, "action_block_new() didn't set "
                "new_action->args");
}

/* Checks that a new action block with SAY type is created without interruption */
Test(action_block_t, new_SAY)
{   
    action_type_t action_type = SAY;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    *args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                "set new_action->num_args");
    cr_assert_eq(new_action->args, args, "action_block_new() didn't set "
                "new_action->args");
}

/* Checks that a new action block with MOVE type is created without interruption */
Test(action_block_t, new_MOVE)
{   
    action_type_t action_type = MOVE;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    *args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                "set new_action->num_args");
    cr_assert_eq(new_action->args, args, "action_block_new() didn't set "
                "new_action->args");
}

/* Checks that a new action block with ADDSUBMULTDIV type is created without interruption */
Test(action_block_t, new_ADDSUBMULTDIV)
{   
    action_type_t action_type = ADDSUBMULTDIV;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    *args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                "set new_action->num_args");
    cr_assert_eq(new_action->args, args, "action_block_new() didn't set "
                "new_action->args");
}

/* Checks that a new action block with GEN type is created without interruption */
Test(action_block_t, new_GEN)
{   
    action_type_t action_type = GEN;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    *args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                "set new_action->num_args");
    cr_assert_eq(new_action->args, args, "action_block_new() didn't set "
                "new_action->args");
}

/* Checks that a new action block with EXEC type is created without interruption */
Test(action_block_t, new_EXEC)
{   
    action_type_t action_type = EXEC;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action_block_t* new_action = action_block_new(action_type, num_args, 
                                                    *args);

    cr_assert_not_null(new_action, "action_block_new() failed");

    cr_assert_eq(new_action->action_type, action_type, "action_block_new() "
                "didn't set new_action->action_type");
    cr_assert_eq(new_action->num_args, num_args, "action_block_new() didn't "
                "set new_action->num_args");
    cr_assert_eq(new_action->args, args, "action_block_new() didn't set "
                "new_action->args");
}

/* Checks that a new action block with SET type is initialized without interruption */
Test(action_block_t, init_SET)
{
    action_block_t action;
    int rc;
    action_type_t action_type = SET;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    rc = action_block_init(&action, action_type, num_args, *args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                "action.num_args");
    cr_assert_eq(action.args, args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with SAY type is initialized without interruption */
Test(action_block_t, init_SAY)
{
    action_block_t action;
    int rc;
    action_type_t action_type = SAY;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    rc = action_block_init(&action, action_type, num_args, *args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                "action.num_args");
    cr_assert_eq(action.args, args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with MOVE type is initialized without interruption */
Test(action_block_t, init_MOVE)
{
    action_block_t action;
    int rc;
    action_type_t action_type = MOVE;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    rc = action_block_init(&action, action_type, num_args, *args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                "action.num_args");
    cr_assert_eq(action.args, args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with ADDSUBMULTDIV type is initialized without interruption */
Test(action_block_t, init_ADDSUBMULTDIV)
{
    action_block_t action;
    int rc;
    action_type_t action_type = ADDSUBMULTDIV;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    rc = action_block_init(&action, action_type, num_args, *args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                "action.num_args");
    cr_assert_eq(action.args, args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with GEN type is initialized without interruption */
Test(action_block_t, init_GEN)
{
    action_block_t action;
    int rc;
    action_type_t action_type = GEN;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    rc = action_block_init(&action, action_type, num_args, *args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                "action.num_args");
    cr_assert_eq(action.args, args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with EXEC type is initialized without interruption */
Test(action_block_t, init_EXEC)
{
    action_block_t action;
    int rc;
    int num_args = 1;
    action_type_t action_type = EXEC;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    rc = action_block_init(&action, action_type, num_args, *args);

    cr_assert_eq(rc, SUCCESS, "action_block_init() failed");
    cr_assert_eq(action.action_type, action_type, "action_block_init() didn't "
                "set action.action_type");
    cr_assert_eq(action.num_args, num_args, "action_block_init() didn't set "
                "action.num_args");
    cr_assert_eq(action.args, args, "action_block_init() didn't set action.args");
}

/* Checks that a new action block with SET type is freed without interruption */
Test(action_block_t, free_SET)
{
    action_block_t *action;
    action_type_t action_type = SET;
    int rc;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action = action_block_new(action_type, num_args, *args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with SAY type is freed without interruption */
Test(action_block_t, free_SAY)
{
    action_block_t *action;
    action_type_t action_type = SAY;
    int rc;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action = action_block_new(action_type, num_args, *args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with MOVE type is freed without interruption */
Test(action_block_t, free_MOVE)
{
    action_block_t *action;
    action_type_t action_type = MOVE;
    int rc;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action = action_block_new(action_type, num_args, *args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with ADDSUBMULTDIV type is freed without interruption */
Test(action_block_t, free_ADDSUBMULTDIV)
{
    action_block_t *action;
    action_type_t action_type = ADDSUBMULTDIV;
    int rc;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action = action_block_new(action_type, num_args, *args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with GEN type is freed without interruption */
Test(action_block_t, free_GEN)
{
    action_block_t *action;
    action_type_t action_type = GEN;
    int rc;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action = action_block_new(action_type, num_args, *args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
}

/* Checks that a new action block with EXEC type is freed without interruption */
Test(action_block_t, free_EXEC)
{
    action_block_t *action;
    action_type_t action_type = EXEC;
    int rc;
    int num_args = 1;
    UT_hash_handle hh = __;
    attribute_value_t int_val = 1;
    enum attribute_tag attribute_tag = INTEGER
    char *name = "attribute"
    attribute_t **args = attribute_new(hh, name, attribute_tag, int_val);

    action = action_block_new(action_type, num_args, *args);

    cr_assert_not_null(action, "action_block_new() failed");

    rc = action_block_free(action);

    cr_assert_eq(rc, SUCCESS, "action_block_free() failed");
} 
