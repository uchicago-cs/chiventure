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
        fprintf(stderr, "Could not initialize this action type");
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
    assert(g);
    assert(g->current_player); // assumes game_t has a field for current player
    assert(a);
    assert(i);
    if (a->kind != ITEM) {
        fprintf(stderr, "The action type provided is not of the correct kind.\n");
        return FAILURE;
    }
    int allowed = FAILURE;
    for (int action = 0; action < i->num_allowed_actions; action++)
        if (!allowed)
            allowed = SUCCESS;
    if (allowed != SUCCESS) {
        fprintf(stderr, "The action can not be done with this item.\n");
        return FAILURE;
    }
    switch (allowed) {
    case PUSH:
    case PULL:
    case OPEN:
    case CLOSE:
    case TURN_ON:
    case TURN_OFF: {
        // See game.h
        int toggle = toggle_condition(g, a, i);
        if (toggle != SUCCESS) {
            fprintf(stderr, "%s failed", a->c_name);
            return FAILURE;
        }
        break;
    }
    case EXAMINE: {
        // See game.h
        int describe = get_long_desc(i);
        if (describe != SUCCESS) {
            fprintf(stderr, "%s failed", a->c_name);
            return FAILURE;
        }
        break;
    }
    case DROP: {
        // See game.h
        int drop = remove_inventory_item(g->current_player, i);
        if (drop != SUCCESS) {
            fprintf(stderr, "Object could not be removed from inventory.\n");
            return FAILURE;
        }
    }
    case TAKE: {
        // See game.h
        int take = take_object(i);
        if (take != SUCCESS) {
            fprintf(stderr, "item can't be taken");
            return FAILURE;
        }
        // See game.h
        int add = add_inventory_item(g->current_player, i);
        if (add != SUCCESS) {
            fprintf(stderr, "item was not taken");
            return FAILURE;
        }
        break;
    }
    case CONSUME: {
        // See game.h
        int consumed = remove_inventory_item(g->current_player, i);
        if (consumed != SUCCESS) {
            fprintf(stderr, "Object could not be removed from inventory.\n");
            return FAILURE;
        }
        // See game.h
        int boosted = change_health(g->current_player, i->change,
                                    g->current_player->max_health);
        if (boosted) {
            fprintf(stderr, "Player's health is %d", boosted);
        }
        break;
    }
    default:
        fprintf(stderr, "Action is not of the correct type.\n");
        return FAILURE;
    }
    return SUCCESS;
}


// KIND 2
/* See actionmanagement.h */
int do_path_action(game_t *g, action_type_t *a, path_t *p)
{
    assert(g);
    assert(a);
    if (a->kind != PATH) {
        fprintf(stderr, "The action type provided is not of the correct kind.\n");
        return FAILURE;
    }
    // See game.h
    int moved = player_move(g, p);
    if (moved == SUCCESS) {
        return SUCCESS;
    } else {
        fprintf(stderr, "Player was unable to move.\n");
        return FAILURE;
    }
}


// KIND 3
/* See actionmanagement.h */
int do_item_item_action(game_t *g, action_type_t *a,
                     item_t *direct, item_t *indirect)
{
    assert(g);
    assert(g->current_player);
    assert(a);
    assert(direct);
    assert(indirect);
    if (a->kind != ITEM_ITEM) {
        fprintf(stderr, "The action type provided is not of the correct kind.\n");
        return FAILURE;
    }
    int allowed = FAILURE;
    for (int action = 0; action < direct->num_allowed_actions; action++)
        if (!allowed)
            allowed = SUCCESS;
    if (allowed != SUCCESS) {
        fprintf(stderr, "The action can not be done to this item.\n");
        return FAILURE;
    }
    // See game.h
    int moved = remove_inventory_item(g->current_player, direct);
    if (moved != SUCCESS) {
        fprintf(stderr, "Object could not be moved from inventory.\n");
        return FAILURE;
    }
    fprintf(stderr, "%s", indirect->status_change); // notifies status change
    return SUCCESS;
}
