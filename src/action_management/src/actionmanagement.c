#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "actionmanagement.h"
#include "common.h"


#define BUFFER_SIZE (100)
#define WRONG_KIND (1)
#define NOT_ALLOWED (2)


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
    free(a);
    return SUCCESS;
}


/* ========================================================================== */


/* KIND 1
 * See actionmanagement.h */
int do_item_action(game_t *g, action_type_t *a, item_t *i, char **ret_string)
{
    // a couple confirmation checks
    assert(g);
    assert(g->curr_player); // needed for sprint 4
    assert(a);
    assert(i);
    char *string = malloc(BUFFER_SIZE); // buffer
    // checks if the action type is the correct kind
    if (a->kind != ITEM) {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }
    // checks if the action can be used on the item
    int allowed = allowed_action(i, a->c_name);
    if (allowed != SUCCESS) {
        sprintf(string, "Action %s can't be requested on item %s",
                a->c_name, i->item_id);
        *ret_string = string;
        return NOT_ALLOWED;
    }
    /* TODO: implement the rest of this function, using game_state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    sprintf(string, "Requested action %s on item %s",
            a->c_name, i->item_id);
    *ret_string = string;
    return SUCCESS;
}


/* KIND 2
 * See actionmanagement.h */
int do_path_action(game_t *g, action_type_t *a, path_t *p, char **ret_string)
{
    assert(g);
    assert(g->curr_player);
    assert(a);
    char *string = malloc(BUFFER_SIZE); // buffer
    // checks if the action type is the correct kind
    if (a->kind != PATH) {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }
    /* TODO: implement the rest of this function, using game state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    sprintf(string, "Requested action %s in direction %s into room %s",
            a->c_name, p->direction, p->dest->room_id);
    *ret_string = string;
    return SUCCESS;
}


/* KIND 3
 * See actionmanagement.h */
int do_item_item_action(game_t *g, action_type_t *a, item_t *direct, 
                          item_t *indirect, char **ret_string)
{
    assert(g);
    assert(a);
    assert(g->curr_player); // needed for sprint 4
    assert(direct);
    assert(indirect);
    char *string = malloc(BUFFER_SIZE); // buffer
    // checks if the action type is the correct kind
    if (a->kind != ITEM_ITEM) {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }
    // checks if the action can be used on the item
    int allowed = allowed_action(indirect, a->c_name);
    if (allowed != SUCCESS) {
        sprintf(string, "Action %s can't be requested on item %s",
                a->c_name, indirect->item_id);
        *ret_string = string;
        return NOT_ALLOWED;
    }
    /* TODO: implement the rest of this function, using game state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    sprintf(string, "Requested action %s with %s on %s",
            a->c_name, direct->item_id, indirect->item_id);
    *ret_string = string;
    return SUCCESS;
}
