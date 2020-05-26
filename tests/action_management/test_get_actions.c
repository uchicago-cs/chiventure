#include <stdlib.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "common/utlist.h"
#include "action_management/actionmanagement.h"


#define NUM_ACTIONS (17)


Test(get_actions, count)
{
    list_action_type_t *head, *temp;
    int out = 0;
    head = get_supported_actions();
    for (temp = head; temp != NULL; temp = temp->next)
    {
        out++;
    }
    cr_assert_eq(out, NUM_ACTIONS,
                 "Expected %d actions, got %d actions when counting through list.\n",
                 NUM_ACTIONS, out);
}


action_type_t *search_supported_actions(char *query)
{
    list_action_type_t *head, *temp;
    head = get_supported_actions();
    for (temp = head; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->act->c_name, query) == 0)
        {
            return temp->act;
        }
    }
    return NULL;
}


/* Checks to see if the action list called can be iterated over using string */
Test(get_actions, search_success)
{
    action_type_t *open, *consume, *go, *walk, *use, *use_on, *pick_up, *drink, *eat;
    open = search_supported_actions("OPEN");
    consume = search_supported_actions("CONSUME");
    go = search_supported_actions("GO");
    walk = search_supported_actions("WALK");
    use = search_supported_actions("USE");
    use_on = search_supported_actions("USE_ON");
    pick_up = search_supported_actions("PICKUP");
    drink = search_supported_actions("DRINK");
    eat = search_supported_actions("EAT");

    cr_assert_neq(open, NULL,
                  "search_supported_actions returned a null for query \"open\".\n");
    cr_assert_neq(consume, NULL,
                  "search_supported_actions returned a null for query \"consume\".\n");
    cr_assert_neq(go, NULL,
                  "search_supported_actions returned a null for query \"go\".\n");
    cr_assert_neq(walk, NULL,
                  "search_supported_actions returned a null for query \"walk\".\n");
    cr_assert_neq(use, NULL,
                  "search_supported_actions returned a null for query \"use\".\n");
    cr_assert_neq(use_on, NULL,
                  "search_supported_actions returned a null for query \"use on\".\n");
    cr_assert_neq(pick_up, NULL,
                  "search_supported_actions returned a null for query \"pick up\".\n");
    cr_assert_neq(drink, NULL,
                  "search_supported_actions returned a null for query \"drink\".\n");
    cr_assert_neq(eat, NULL,
                  "search_supported_actions returned a null for query \"eat\".\n");

    cr_assert_eq(open->kind, ITEM,
                 "Expected the action kind %d, but got action kind %d.\n",
                 ITEM, open->kind);
    cr_assert_eq(consume->kind, ITEM,
                 "Expected the action kind %d, but got action kind %d.\n",
                 ITEM, consume->kind);
    cr_assert_eq(go->kind, PATH,
                 "Expected the action kind %d, but got action kind %d.\n",
                 PATH, go->kind);
    cr_assert_eq(walk->kind, PATH,
                 "Expected the action kind %d, but got action kind %d.\n",
                 PATH, walk->kind);
    cr_assert_eq(use_on->kind, ITEM_ITEM,
                 "Expected the action kind %d, but got action kind %d.\n",
                 ITEM_ITEM, use_on->kind);
    cr_assert_eq(use->kind, ITEM,
                 "Expected the action kind %d, but got action kind %d.\n",
                 ITEM, use->kind);
    cr_assert_eq(pick_up->kind, ITEM,
                 "Expected the action kind %d, but got action kind %d.\n",
                 ITEM, pick_up->kind);
    cr_assert_eq(drink->kind, ITEM,
                 "Expected the action kind %d, but got action kind %d.\n",
                 ITEM, drink->kind);
    cr_assert_eq(eat->kind, ITEM,
                 "Expected the action kind %d, but got action kind %d.\n",
                 ITEM, eat->kind);
}


Test(get_actions, search_failure)
{
    action_type_t *dance, *jump, *fight;
    dance = search_supported_actions("dance");
    jump = search_supported_actions("jump");
    fight = search_supported_actions("fight");
    cr_assert_eq(dance, NULL,
                 "search_supported_actions returned a pointer for invalid query \"dance\".\n");
    cr_assert_eq(jump, NULL,
                 "search_supported_actions returned a pointer for invalid query \"jump\".\n");
    cr_assert_eq(fight, NULL,
                 "search_supported_actions returned a pointer for invalid query \"fight\".\n");
}
