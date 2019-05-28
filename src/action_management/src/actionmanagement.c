#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "actionmanagement.h"
#include "common.h"
#include <string.h>
#include "item.h"

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
int action_type_free(action_type_t *a)
{
    assert(a);
    assert(a->c_name);
    free(a->c_name);
    free(a);
    return SUCCESS;
}


/* ========================================================================== */


/* KIND 1
 * See actionmanagement.h */
char *do_item_action(game_t *g, action_type_t *a, item_t *i)
{
    // a couple confirmation checks
    assert(g);
    assert(g->curr_player); // needed for sprint 4
    assert(a);
    assert(i);
    char *ret_string = malloc(100); // buffer
    ret_string[0] = '\0';
    // checks if the action type is the correct kind
    if (a->kind != ITEM) {
        strcat(ret_string, "The action type provided is not of the correct kind");
        return ret_string;
    }
    // checks if the action can be used on the item
    int allowed = allowed_action(i, a->c_name);
    if (allowed != SUCCESS) {
        strcat(ret_string, "Action ");
        strcat(ret_string, a->c_name);
        strcat(ret_string, "can't be requested on item ");
        strcat(ret_string, i->item_id);
        return ret_string;
    }
    /* TODO: implement the rest of this function, using game_state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    strcat(ret_string, "Requested action ");
    strcat(ret_string, a->c_name);
    strcat(ret_string, " on item ");
    strcat(ret_string, i->item_id);
    return ret_string;
}


/* KIND 2
 * See actionmanagement.h */
char *do_path_action(game_t *g, action_type_t *a, path_t *p)
{
    assert(g);
    assert(g->curr_player);
    assert(a);
    char *ret_string = malloc(100); // buffer
    ret_string[0] = '\0';
    // checks if the action type is the correct kind
    if (a->kind != PATH) {
        strcat(ret_string, "The action type provided is not of the correct kind");
        return ret_string;
    }
    /* TODO: implement the rest of this function, using game state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    strcat(ret_string, "Requested action ");
    strcat(ret_string, a->c_name);
    strcat(ret_string, " in direction ");
    strcat(ret_string, p->direction);
    strcat(ret_string, " into room ");
    strcat(ret_string, p->dest);
    return ret_string;

}
/* KIND 3
 * See actionmanagement.h */
char *do_item_item_action(game_t *g, action_type_t *a,
                        item_t *direct, item_t *indirect)
{
    assert(g);
    assert(a);
    assert(g->curr_player); // needed for sprint 4
    assert(direct);
    assert(indirect);
    char *ret_string = malloc(100); // buffer
    ret_string[0] = '\0';
    // checks if the action type is the correct kind
    if (a->kind != ITEM_ITEM) {
        strcat(ret_string, "The action type provided is not of the correct kind");
        return ret_string;
    }
    // checks if the action can be used on the item
    int allowed = allowed_action(indirect, a->c_name);
    if (allowed != SUCCESS) {
        strcat(ret_string, "Action ");
        strcat(ret_string, a->c_name);
        strcat(ret_string, "can't be requested on item ");
        strcat(ret_string, indirect->item_id);
        return ret_string;
    }
    /* TODO: implement the rest of this function, using game state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    strcat(ret_string, "Requested action ");
    strcat(ret_string, a->c_name);
    strcat(ret_string, " with ");
    strcat(ret_string, direct->item_id);
    strcat(ret_string, " on ");
    strcat(ret_string, indirect->item_id);
    return ret_string;
}
