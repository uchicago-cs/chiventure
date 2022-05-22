/*
 * Basic functions and structs for action blocks to be used
 * in custom-actions implementation.
 *
 * Please see "action_block.h" for function documentation.
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "ast_block.h"
#include "action_block.h"
#include "custom-actions-effect.h"
#include "game-state/game.h"

/* See action_block.h */
action_block_t *action_block_new(action_enum_t action_type, int num_args,
                                 action_param_t *action_params)
{
    action_block_t *action;
    int new_action;
    block_type_t block_type = ACTION;

    action = malloc(sizeof(action_block_t));

    if (action == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        return NULL;
    }

    new_action = action_block_init(action, action_type, num_args, action_params);
    if (new_action != SUCCESS)
    {
        fprintf(stderr, "Error: Could not initialize action_block_t\n");
        return NULL;
    }

    return action;
}

/* See action_block.h */
AST_block_t *AST_action_block_new(action_enum_t action_type, int num_args,
                                  action_param_t *action_params)
{
    AST_block_t *ast;
    action_block_t *action;
    int new_action;
    block_type_t block_type = ACTION;

    action = malloc(sizeof(action_block_t));
    ast = malloc(sizeof(AST_block_t));

    if (action == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        return NULL;
    }

    if (ast == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        return NULL;
    }

    new_action = action_block_init(action, action_type, num_args, action_params);
    if (new_action != SUCCESS)
    {
        fprintf(stderr, "Error: Could not initialize action_block_t\n");
        return NULL;
    }

    block_t *block = malloc(sizeof(block));

    if (block == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        return NULL;
    }

    block->action_block = action;
    ast = AST_block_new(block, block_type);
    return ast;
}

/* See action_block.h */
int action_block_init(action_block_t *action, action_enum_t action_type,
                      int num_args, action_param_t *action_params)
{
    assert(action != NULL);
    assert(num_args > 0);
    assert(action_params != NULL);

    action->action_type = action_type;
    action->num_args = num_args;
    action->action_params = action_params;

    return SUCCESS;
}

/* See action_block.h */
int action_block_free(action_block_t *action)
{
    assert(action != NULL);

    free(action);

    return SUCCESS;
}

/* See action_block.h */
int exec_action_block(action_block_t *a)
{
    int rc;
    unsigned n; // number of arguments corresponding to action type

    switch (a->action_type)
    {

    case TELEPORT:
    case SET:
        n = 2;
        break;
    case ADDITION:
    case SUBTRACT:
    case MULTIPLY:
    case DIVIDE:
    case GEN:
        n = 3;
        break;
    default:
        return FAILURE;
    }

    if (a->num_args != n)
    {
        return FAILURE;
    }

    switch (a->action_type)
    {

    case SET:
        rc = set_attr(a->action_params->args[0], a->action_params->args[1]);
        break;
    case ADDITION:
        rc = add_attr(a->action_params->args[0], a->action_params->args[1], a->action_params->args[2]);
        break;
    case SUBTRACT:
        rc = sub_attr(a->action_params->args[0], a->action_params->args[1], a->action_params->args[2]);
        break;
    case MULTIPLY:
        rc = mult_attr(a->action_params->args[0], a->action_params->args[1], a->action_params->args[2]);
        break;
    case DIVIDE:
        rc = div_attr(a->action_params->args[0], a->action_params->args[1], a->action_params->args[2]);
        break;
    case TELEPORT:
        rc = move_room(a->action_params->game, a->action_params->room);
        rc = (rc == SUCCESS) ? SUCCEEDS : FAILS;
        break; 
    case GEN:
        if (a->action_params->args[0]->attribute_tag != INTEGER ||
            a->action_params->args[1]->attribute_tag != INTEGER)
        {
            return FAILURE;
        }
        rc = gen_attrval(a->action_params->args[0]->attribute_value.int_val,
                         a->action_params->args[1]->attribute_value.int_val,
                         a->action_params->args[2]);
        break;
    default:
        return FAILURE;
    }

    return (rc == 2) ? SUCCESS : FAILURE;
}
