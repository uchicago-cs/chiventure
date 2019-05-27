#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <criterion/criterion.h>
#include "utlist.h"
#include "actionmanagement.h"

static action_type_t valid_actions[] = {
    // KIND 1
    {"open", ITEM},
    {"close", ITEM},
    {"push", ITEM},
    {"pull", ITEM},
    {"examine", ITEM},
    {"turn on", ITEM},
    {"turn off", ITEM},
    {"take", ITEM},
    {"drop", ITEM},
    {"consume", ITEM},
    // KIND 2
    {"go", PATH},
    {"enter", PATH},
    // KIND 3
    {"use on", ITEM_ITEM},
    {"put on", ITEM_ITEM}
};

void check_search(list_action_type_t *head, char *query, int expected_index)
{
    list_action_type_t *elt;
    LL_SEARCH(head,elt,valid_actions[expected_index],strcmp);
    int strcmp_result = strcmp(elt->act->c_name,valid_actions[expected_index].c_name)
    cr_assert_eq(strcmp_result,0,
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
