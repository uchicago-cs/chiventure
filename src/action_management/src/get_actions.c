#include <stdlib.h>
#include <string.h>
#include "utlist.h"
#include "actionmanagement.h"
#include "action_structs.h"


static action_type_t valid_actions[] = {
    // KIND 1
    {"OPEN", ITEM},
    {"CLOSE", ITEM},
    {"PUSH", ITEM},
    {"PULL", ITEM},
    {"TURN_ON", ITEM},
    {"TURN_OFF", ITEM},
    {"TAKE", ITEM},
    {"DROP", ITEM},
    {"CONSUME", ITEM},
    // KIND 2
    {"GO", PATH},
    {"ENTER", PATH},
    // KIND 3
    {"USE_ON", ITEM_ITEM},
    {"PUT_ON", ITEM_ITEM}
};


static int NUM_ACTIONS = sizeof(valid_actions) / sizeof(action_type_t);


list_action_type_t *get_supported_actions()
{
    list_action_type_t *temp = NULL;

    for (int i = 0; i < NUM_ACTIONS; i++) {
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
 * head: SHOULD BE GET_SUPPORTED_ACTIONS()
 * query: SHOULD BE A VALID LOWERCASE ACTION STRING C_NAME, e.g. "go", "pull", "open"
action_type_t *search_supported_actions(list_action_type_t* head, char *query)
{
    list_action_type_t *temp;
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
