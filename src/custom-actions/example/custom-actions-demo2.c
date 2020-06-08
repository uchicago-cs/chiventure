#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ast_block.h"
#include "action_block.h"
#include "branch_block.h"
#include "conditional_block.h"
#include "control_block.h"
#include "custom_action.h"
#include "interface.h"

void add_custom_action()
{
    block_t *block1 = malloc(sizeof(block_t));
    block_type_t block_type1 = ACTION;
    AST_block_t *head1 = AST_block_new(block1, block_type1);
    char *action_name1 = "act_PUSH";
    char *context1 = "chair";
    char *item1 = "obj_SPINACH";
    char *type1 = "wizard";
    custom_action_t *new_action1 = custom_action_new(action_name1, context1,
                                                     item1, type1, head1);
    if (new_action1 == NULL)
    {
        return;
    }

    printf("\n\n");
    printf("Created a new custom action: act_PUSH");
    printf("\taction_name:\t\tact_PUSH");
    printf("\tcontext:\t\tchair");
    printf("\titem:\t\tobj_SPINACH");
    printf("\ttype:\t\twizard\n\n");

    block_t *block2 = malloc(sizeof(block_t));
    block_type_t block_type2 = CONDITIONAL;
    AST_block_t *head2 = AST_block_new(block2, block_type2);
    char *action_name2 = "act_THROW";
    char *context2 = "chair";
    char *item2 = "obj_SPADE";
    char *type2 = "druid";
    custom_action_t *new_action2 = custom_action_new(action_name2, context2,
                                                     item2, type2, head2);
    if (new_action2 == NULL)
    {
        return;
    }

    printf("Created a new custom action: act_THROW");
    printf("\taction_name:\t\tact_THROW");
    printf("\tcontext:\t\tchair");
    printf("\titem:\t\tobj_SPADE");
    printf("\ttype:\t\tdruid\n\n");

    block_t *block3 = malloc(sizeof(block_t));
    block_type_t block_type3 = BRANCH;
    AST_block_t *head3 = AST_block_new(block3, block_type3);
    char *action_name3 = "act_PLANT";
    char *context3 = "soil";
    char *item3 = "obj_ORANGE_SEED";
    char *type3 = "ranger";
    custom_action_t *new_action3 = custom_action_new(action_name3, context3,
                                                     item3, type3, head3);
    if (new_action3 == NULL)
    {
        return;
    }

    printf("Created a new custom action: act_PLANT");
    printf("\taction_name:\t\tact_PLANT");
    printf("\tcontext:\t\tsoil");
    printf("\titem:\t\tobj_ORANGE_SEED");
    printf("\ttype:\t\tranger\n\n");

    int rc = add_custom_action_to_game(new_action1);
    if (rc == FAILURE)
    {
        return;
    }
    printf("added act_PUSH to game");

    rc = add_custom_action_to_game(new_action2);
    if (rc == FAILURE)
    {
        return;
    }
    printf("added act_THROW to game");

    rc = add_custom_action_to_game(new_action3);
    if (rc == FAILURE)
    {
        return;
    }
    printf("added act_PLANT to game");

    printf("\n\n\n");

    custom_action_t *found = search_for_custom_action(action_name1);

    printf("Searching for \"act_PUSH\" in game...");
    if (found != NULL && found->action_name == action_name1)
    {
        printf("Found in game!\n");
    }
    else
    {
        printf("Not found in game.\n");
    }

    found = search_for_custom_action(action_name3);

    printf("Searching for \"act_PLANT\" in game...");
    if (found != NULL && found->action_name == action_name3)
    {
        printf("Found in game!\n");
    }
    else
    {
        printf("Not found in game.\n");
    }

    found = search_for_custom_action(action_name2);
    printf("Searching for \"act_THROW\" in game...");
    if (found != NULL && found->action_name == action_name2)
    {
        printf("Found in game!\n");
    }
    else
    {
        printf("Not found in game.\n");
    }

    // now tries to find an action that is NOT in the list

    char *action_name4 = "act_EAT";
    found = search_for_custom_action(action_name2);
    printf("Searching for \"act_EAT\" in game...");
    if (found != NULL)
    {
        printf("Found in game!\n");
    }
    else
    {
        printf("Not found in game.\n");
    }
}
