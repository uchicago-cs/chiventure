#include <stdlib.h>
#include "utlist.h"
#include "actionmanagement.h"
#include "action_structs.h"

static action_type_t valid_actions[] =
{
/* KIND 1 */
    {"open", ITEM},
    {"close", ITEM},
    {"push",ITEM},
    {"pull", ITEM},
    {"examine",ITEM},
    {"turn on", ITEM},
    {"turn off",ITEM},
    {"take", ITEM},
    {"drop",ITEM},
    {"consume", ITEM},
/* KIND 2 */
    {"go",PATH},
    {"enter",PATH},
/* KIND 3 */
    {"use on",ITEM_ITEM},
    {"put on",ITEM_ITEM}
};

static int NUM_ACTIONS = sizeof(valid_actions) / sizeof(action_type_t);


list_actions *get_supported_actions(enum action_kind kind)
{
    action_type_t temp = NULL;
    int i;

    switch(kind)
    {
        case 1:
            for(i = 0; i <= 9; i++) 
            {
                LL_APPEND(temp,valid_actions[i]);
                temp = valid_actions[i];
            }
            break;

        case 2:
            for(i = 10; i <= 11; i++) 
            {
                LL_APPEND(temp,valid_actions[i]);
                temp = valid_actions[i];
            }
            break;

        case 3:
            for(i = 12; i <= 13; i++) 
            {
                LL_APPEND(temp,valid_actions[i]);
                temp = valid_actions[i];
            }
            break;
    }
}