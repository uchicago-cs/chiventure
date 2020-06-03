#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include "game-state/game_action.h"
#include "action_management/actionmanagement.h"

/* helper function that deletes an action from the list */
int delete_helper(action_type_t *a, list_action_type_t *act)
{
    list_action_type_t *temp;

    int rc;
    rc = delete_action(act, a);

    //go through each item to make sure ut's not there
    temp = act;
    while (temp != NULL)
    {
	cr_assert_neq(temp, a, "delete_action() didn't remove action");
    }

    return SUCCESS;
}

/* checks if delete_action can delete the first node */
Test(delete_action,delete_first)
{   
    //make action_type_t
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);
    
    //organize action_types into a linked list 
    list_action_type_t *first, *second, *last, *temp;
    first = malloc(sizeof(list_action_type_t));
    second = malloc(sizeof(list_action_type_t));
    last = malloc(sizeof(list_action_type_t));
    last->act = open;
    last->next = NULL;
    second->act = go;
    second->next = last;
    first->act = eat;
    first->next = second;

    int rc;
    rc = delete_helper(eat, first);

    free(last);
    free(second);
    free(first);
}

/* checks if delete_action can delete the middle node */
Test(delete_action,delete_middle)
{   
    //make action_type_t
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);
    
    //organize action_types into a linked list 
    list_action_type_t *first, *second, *last, *temp;
    first = malloc(sizeof(list_action_type_t));
    second = malloc(sizeof(list_action_type_t));
    last = malloc(sizeof(list_action_type_t));
    last->act = open;
    last->next = NULL;
    second->act = go;
    second->next = last;
    first->act = eat;
    first->next = second;

    int rc;
    rc = delete_helper(go, first);

    free(last);
    free(second);
    free(first);
}

/* checks if delete_action can delete the last node */
Test(delete_action,delete_last)
{   
    //make action_type_t
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);
    
    //organize action_types into a linked list 
    list_action_type_t *first, *second, *last, *temp;
    first = malloc(sizeof(list_action_type_t));
    second = malloc(sizeof(list_action_type_t));
    last = malloc(sizeof(list_action_type_t));
    last->act = open;
    last->next = NULL;
    second->act = go;
    second->next = last;
    first->act = eat;
    first->next = second;

    int rc;
    rc = delete_helper(open, first);

    free(last);
    free(second);
    free(first);
}

