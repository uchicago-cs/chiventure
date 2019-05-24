#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "actionmanagement.h"
#include "common.h"


/* See actionmanagement.h */
action_type_t *action_type_new(char *c_name, enum action_kind kind)
{
    action_type_t *a = malloc(sizeof(action_type_t));

    if (a == NULL) {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    int new_a = action_type_init(a, c_name, kind);
    if (new_a != SUCCESS) {
        fprintf(stderr, "Could not initialize action type %s", c_name);
        return NULL;
    }

    return a;
}


/* See actionmanagement.h */
int action_type_init(action_type_t *a, char *c_name, enum action_kind kind)
{
    assert(a);
    a->c_name = c_name;
    a->kind = kind;

    return SUCCESS;
}


/* See actionmanagement.h */
void action_type_free(action_type_t *a)
{
    assert(a);
    assert(a->c_name);
    free(a->c_name);
    free(a);
    return;
}


/* ========================================================================== */


// KIND 1
/* See actionmanagement.h */
int do_item_action(game_t *g, action_type_t *a, item_t *i)
{
    // a couple confirmation checks
    assert(g);
    assert(g->curr_player);
    assert(a);
    assert(i);
    if (a->kind != ITEM) {
        fprintf(stderr, "The action type provided is not of the correct kind.\n");
        return FAILURE;
    }
    // TODO: implement the rest of this function, using game_state funcs
    printf("Performed action %s on item %s", a->c_name, i->item_id);
    return SUCCESS;
}


// KIND 2
/* See actionmanagement.h */
int do_path_action(game_t *g, action_type_t *a, path_t *p)
{
    assert(g);
    assert(g->curr_player);
    assert(a);
    if (a->kind != PATH) {
        fprintf(stderr, "The action type provided is not of the correct kind.\n");
        return FAILURE;
    }
    // TODO: implement the rest of this function, using game state funcs
    printf("Performed movement %s using %s into the room %s.",
           a->c_name, p->direction, p->dest);
    return SUCCESS;
}


// KIND 3
/* See actionmanagement.h */
int do_item_item_action(game_t *g, action_type_t *a,
                        item_t *direct, item_t *indirect)
{
    assert(g);
    assert(g->curr_player);
    assert(a);
    assert(direct);
    assert(indirect);
    if (a->kind != ITEM_ITEM) {
        fprintf(stderr, "The action type provided is not of the correct kind.\n");
        return FAILURE;
    }
    printf("Performed action %s with %s on %s.",
           a->c_name, direct->item_id, indirect->item_id);
    return SUCCESS;
}
