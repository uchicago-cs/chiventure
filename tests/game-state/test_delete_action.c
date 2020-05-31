#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include "game-state/game_action.h"
#include "action_management/action_structs.h"

/* helper function that creates the same list to test and takes in the 
 * action to delete as a parameter
 */
int delete_helper(action_type_t *a)
{
    struct action_type_t *eat, *go, *open;
    eat = action_type_new("eat", ITEM, 0);
    go = action_type_new("go", PATH, 0);
    open = action_type_new("openn", ITEM, 0);

    //organize action_types into a linked list
    struct list_action_type_t *first, *second, *last, *temp;
    last->act = open;
    last->next = NULL;
    second->act = go;
    second->next = last;
    first->act = eat;
    first->next = second;

    int rc;
    rc = delete_action(first_condition, a);

    //go through each item to make sure ut's not there
    temp = &first
    while (temp != NULL)
    {
	cr_assert_not_eq(temp, a, "delete_action() didn't remove action");
    }

    return SUCCESS;
}

/* checks if delete_action can delete the first node */
Test(delete_action,delete_first)
{   
    int rc;
    rc = delete_helper(eat);
}

/* checks if delete_action can delete the middle node */
Test(delete_action,delete_middle)
{   
    int rc;
    rc = delete_helper(go);
}

/* checks if delete_action can delete the last node */
Test(delete_action,delete_last)
{   
    int rc;
    rc = delete_helper(open);
}

