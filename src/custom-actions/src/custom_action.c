/* 
 * Basic functions and structs for custom actions to be used in 
 * custom-actions implementation. 
 *
 * Please see "custom_action.h" for function documentation. 
 */

#include <stdlib.h>
#include <stdio.h>
#include "game-state/item.h"
#include "custom_action.h"

/* See custom_action.h */
custom_action_t* custom_action_new(char *action_name, char *context, char *item, 
                                   char *type, AST_block_t *head)
{
    custom_action_t *action;
    int new_action;

    action = malloc(sizeof(custom_action_t));

    if (action == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory\n");
        return NULL;
    }

    new_action = custom_action_init(action, action_name, context, item, type, head);
    if (new_action != SUCCESS)
    {
        fprintf(stderr, "Error: Could not initialize custom_action_t\n");
        return NULL;
    }

    return action;
}

/* See custom_action.h */
int custom_action_init(custom_action_t *action, char *action_name, char *context, 
                       char *item, char *type, AST_block_t *head)
{
    assert(action != NULL);
    assert(action_name != NULL);
    assert(context != NULL);
    assert(item != NULL);
    assert(type != NULL);
    assert(head != NULL);

    action->action_name = action_name;
    action->context = context;
    action->item = item;
    action->type = type;
    action->head = head;

    return SUCCESS;
}

/* See custom_action.h */
int custom_action_free(custom_action_t *action)
{
    assert(action != NULL);

    AST_block_free(action->head);
    free(action);

    return SUCCESS;
}
