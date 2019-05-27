#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "utlist.h"
#include "get_actions.h"

void check_search(list_action_type_t *head, char *query, int expected_index)
{
    list_action_type_t *elt;
    LL_SEARCH_SCALAR(head,elt,c_name,query);
    cr_assert_eq(elt->act->c_name,valid_actions[expected_index]->c_name,
                 "Searched using query %s. Found the element %s of the kind %d.\n",
                 query, elt->act->c_name, elt->act->kind);
}

/* Checks to see if the action list called can be iterated over using string */
Test(get_actions, search)
{
    list_action_type_t *actions = get_supported_actions();
    check_search(actions, "open", 0);
    check_search(actions, "close", 1);
    check_search(actions, "put on", 13);
}
