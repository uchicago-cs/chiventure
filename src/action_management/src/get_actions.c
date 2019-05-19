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

/* the number of each of the kinds of actions there currently are */
static int NUM_ITEM = 10;
static int NUM_PATH = 2;
static int NUM_ITEM_ITEM = 2;

list_actions *get_supported_actions(enum action_kind kind)
{
    list_actions *temp = NULL;
    int i;

    switch(kind)
    {
        case ITEM:
            for(i = 0; i <= --NUM_ITEM; i++) 
            {
                list_actions *add = (list_actions*)malloc(sizeof(list_actions));
                action_type_t *add_data = action_new(valid_actions[i].c_name,
                                                     valid_actions[i].kind);
                add->data = add_data;
                LL_PREPEND(temp,add);
                temp = add;
            }
            break;

        case PATH:
            for(i = NUM_ITEM; i <= --(NUM_ITEM+NUM_PATH); i++) 
            {
                list_actions *add = (list_actions*)malloc(sizeof(list_actions));
                action_type_t *add_data = action_new(valid_actions[i].c_name,
                                                     valid_actions[i].kind);
                add->data = add_data;
                LL_PREPEND(temp,add);
                temp = add;
            }
            break;

        case ITEM_ITEM:
            for(i = NUM_ITEM+NUM_PATH; i <= --(NUM_ITEM+NUM_PATH+NUM_ITEM_ITEM); i++) 
            {
                list_actions *add = (list_actions*)malloc(sizeof(list_actions));
                action_type_t *add_data = action_new(valid_actions[i].c_name,
                                                     valid_actions[i].kind);
                add->data = add_data;
                LL_PREPEND(temp,add);
                temp = add;
            }
            break;
    }
    return temp;
}