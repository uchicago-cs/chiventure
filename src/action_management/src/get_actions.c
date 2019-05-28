#include <stdlib.h>
#include <string.h>
#include "utlist.h"
#include "actionmanagement.h"
#include "action_structs.h"


static action_type_t valid_actions[] = {
    // KIND 1
    {"open", ITEM},
    {"close", ITEM},
    {"push", ITEM},
    {"pull", ITEM},
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


static int NUM_ACTIONS = sizeof(valid_actions) / sizeof(action_type_t);


list_action_type_t *get_supported_actions()
{
    list_action_type_t *temp = NULL;
    int i;

    for (i = 0; i < NUM_ACTIONS; i++) {
        list_action_type_t *add = (list_action_type_t*)malloc(sizeof(list_action_type_t));
        action_type_t *add_data = action_type_new(valid_actions[i].c_name,
                                                  valid_actions[i].kind);
        add->act = add_data;
        LL_PREPEND(temp,add);
        temp = add;
    }
    return temp;
}

/* THIS FUNCTION IS USED IN TEST_GET_ACTIONS.C
 * BUT IS LEFT HERE FOR REFERENCE

action_type_t *search_supported_actions(char *query)
{
    list_action_type_t *head, *temp;
    head = get_supported_actions();
    for (temp = head; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->c_name,query) == 0)
        {
            return temp;
        }        
    }
    return NULL;
}

*/
