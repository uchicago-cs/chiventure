#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "utlist.h"
#include "actionmanagement.h"

action_type_t *search_supported_actions(char *query)
{
    list_action_type_t *head, *temp;
    head = get_supported_actions();
    for (temp = head; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->act->c_name,query) == 0)
        {
            return temp->act;
        }        
    }
    return NULL;
}

/* Checks to see if the action list called can be iterated over using string */
Test(get_actions, search)
{
    action_type_t *open, *consume, *go, *use_on;
    open = search_supported_actions("open");
    consume = search_supported_actions("consume");
    go = search_supported_actions("go");
    use_on = search_supported_actions("use on");

    cr_assert_neq(open, NULL, 
                  "search_supported_actions returned a null for query \"open\".\n");
    cr_assert_neq(consume, NULL, 
                  "search_supported_actions returned a null for query \"consume\".\n");
    cr_assert_neq(go, NULL, 
                  "search_supported_actions returned a null for query \"go\".\n");
    cr_assert_neq(use_on, NULL, 
                  "search_supported_actions returned a null for query \"use on\".\n");
}
