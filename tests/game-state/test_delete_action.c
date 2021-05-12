#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include "game-state/game_action.h"
#include "action_management/actionmanagement.h"

/* helper function that creates the same list to test and takes in the 
 * action to delete as a parameter
 */
int delete_helper(list_action_type_t *act, list_action_type_t *a)
{
    int rc;
    rc = delete_action(&act, a);

    //go through each item to make sure it's not there
    list_action_type_t *temp;
    temp = act;
    while (temp != NULL)
    {
	cr_assert_neq(temp->act, a, "delete_action() didn't remove action");
	temp = temp->next;
    }

    return SUCCESS;
}

/* checks if delete_action can delete the first node */
Test(delete_action, delete_first)
{   
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);

    //organize action_types into a linked list
    list_action_type_t *first, *second, *last;
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
    rc = delete_helper(first, first);

    cr_assert_eq(rc, SUCCESS, "delete_action test 1 failed");
    free(first);
    free(second);
    action_type_free(eat);
    free(last);
    action_type_free(go);
    action_type_free(open);
}

/* checks if delete_action can delete the middle node */
Test(delete_action, delete_middle)
{   
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);

    //organize action_types into a linked list
    list_action_type_t *first, *second, *last;
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
    rc = delete_helper(first, second);

    cr_assert_eq(rc, SUCCESS, "delete_action test 2 failed");
    free(first);
    free(second);
    free(last);
    action_type_free(eat);
    action_type_free(go);
    action_type_free(open);
}

/* checks if delete_action can delete the last node */
Test(delete_action, delete_last)
{   
    action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM);
    go = action_type_new("go", PATH);
    open = action_type_new("open", ITEM);

    //organize action_types into a linked list
    list_action_type_t *first, *second, *last;
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
    rc = delete_helper(first, last);

    cr_assert_eq(rc, SUCCESS, "delete_action test 3 failed");
    free(first);
    free(second);
    free(last);
    action_type_free(eat);
    action_type_free(go);
    action_type_free(open);
		      
}

