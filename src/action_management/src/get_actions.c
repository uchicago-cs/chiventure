#include <stdlib.h>
#include <string.h>

#include "common/utlist.h"
#include "action_management/actionmanagement.h"


static action_type_t valid_actions[] =
{
    // KIND 1
    {"OPEN", ITEM},
    {"CLOSE", ITEM},
    {"PUSH", ITEM},
    {"PULL", ITEM},
    {"TURNON", ITEM},
    {"TURNOFF", ITEM},
    {"TAKE", ITEM},
    {"DROP", ITEM},
    {"CONSUME", ITEM},
    // KIND 2
    {"GO", PATH},
    // KIND 3
    {"USE", ITEM_ITEM},
    {"PUT", ITEM_ITEM}
};


static int NUM_ACTIONS = sizeof(valid_actions) / sizeof(action_type_t);


list_action_type_t *get_supported_actions()
{
    list_action_type_t *temp = NULL;

    for (int i = 0; i < NUM_ACTIONS; i++)
    {
        list_action_type_t *add = (list_action_type_t*)malloc(sizeof(list_action_type_t));
        action_type_t *add_data = action_type_new(valid_actions[i].c_name,
                                  valid_actions[i].kind, 0);
        add->act = add_data;
        LL_PREPEND(temp,add);
        temp = add;
    }
    return temp;
}
