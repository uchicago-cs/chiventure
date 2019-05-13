#include <stdlib.h>
#include "utlist.h"
#include "actionmanagement.h"

typedef struct list_t {
    void* data;
    struct list_t *next, *prev;
} list_t;



list_t* get_actions_kind1()
{
    // SYNONYM TAKE
    list_t *head_take = NULL;
    LL_APPEND(head_take, "pick up");
    // SYNONYM CONSUME
    list_t *head_consume = NULL;
    LL_APPEND(head_consume, "eat");
    LL_APPEND(head_consume, "drink");

    // LIST OF ACTIONS
    list_t *head = NULL;
    LL_APPEND(head,action_new(OPEN, "open", NULL, ITEM));
    LL_APPEND(head,action_new(CLOSE, "close", NULL, ITEM));
    LL_APPEND(head,action_new(PUSH, "push", NULL, ITEM));
    LL_APPEND(head,action_new(PULL, "pull", NULL, ITEM));
    LL_APPEND(head,action_new(EXAMINE, "examine", NULL, ITEM));
    LL_APPEND(head,action_new(TURN_ON, "turn on", NULL, ITEM));
    LL_APPEND(head,action_new(TURN_OFF, "turn off", NULL, ITEM));
    LL_APPEND(head,action_new(TAKE, "take", take_synonyms, ITEM));
    LL_APPEND(head,action_new(DROP, "drop", NULL, ITEM));
    LL_APPEND(head,action_new(CONSUME, "consume", consume_synonyms, ITEM));


}