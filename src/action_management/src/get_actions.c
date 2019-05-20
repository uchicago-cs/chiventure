#include <stdlib.h>
#include "utlist.h"
#include "actionmanagement.h"
#include "action_structs.h"


static action_type_t valid_actions[] =
{
// KIND 1
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
// KIND 2
    {"go",PATH}, // index = 10
    {"enter",PATH},
// KIND 3
    {"use on",ITEM_ITEM}, // index = 12
    {"put on",ITEM_ITEM}
};

static int NUM_ACTIONS = sizeof(valid_actions) / sizeof(action_type_t);

// the index which is currently holding the first action of each kind
static int INDEX_ITEM = 0;
static int INDEX_PATH = 10;
static int INDEX_ITEM_ITEM = 12;

list_actions *get_supported_actions(enum action_kind kind)
{
    list_actions *temp = NULL;
    int i;

    switch(kind)
    {
        case ITEM:
            for(i = 0; i < INDEX_PATH; i++) 
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
            for(i = INDEX_PATH; i < INDEX_ITEM_ITEM; i++) 
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
            for(i = INDEX_ITEM_ITEM; i < NUM_ACTIONS; i++) 
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