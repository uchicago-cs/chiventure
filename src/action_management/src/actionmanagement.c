#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "actionmanagement.h"
#include "common.h"

// See actionmanagement.h
action_t *action_new(enum actions act, char *c_name,
                     list_t *synonyms, enum action_kind kind)
{
    action_t *a = malloc(sizeof(action_t));

    if (a == NULL) {
        fprintf(stderr, "Could not allocate memory");
        return NULL;
    }

    int new_a = action_init(a, act, c_name, synonyms, kind);
    if (new_a != SUCCESS) {
        fprintf(stderr, "Could not initialize this action");
        return NULL;
    }

    return a;
}


// See actionmanagement.h
int action_init(action_t *a, enum actions act, char *c_name,
                list_t *synonyms, enum action_kind kind)
{
    assert(a);

    a->act = act;
    a->c_name = c_name;
    a->synonyms = synonyms;
    a->kind = kind;

    return SUCCESS;
}


// See actionmanagement.h
int action_free(action_t *a)
{
    assert(a);
    assert(a->c_name);
    assert(a->synonyms);
    free(a->c_name);
    free(a->synonyms);
    free(a);
    return SUCCESS;
}


/* See actionmanagement.h
 * These are skeleton functions put in place so the code will compile
 * The actual implementation will be executed in a later sprint,
 * along with the implementation/inclusion of a list_t struct */
list_t *get_actions_kind1()
{
    return NULL;
}


list_t *get_actions_kind2()
{
    return NULL;
}


list_t *get_actions_kind3()
{
    return NULL;
}


list_t *get_actions_kind4()
{
    return NULL;
}


list_t *get_actions_kind5()
{
    return NULL;
}


// See actionmanagement.h
list_t *get_supported_actions(enum action_kind kind)
{
    list_t *actions = NULL;
    switch (kind) {
    case ITEM:
        actions = get_actions_kind1();
        return actions;
    case DIRECTION:
        actions = get_actions_kind2();
        return actions;
    case NPC:
        actions = get_actions_kind3();
        return actions;
    case ITEM_NPC:
        actions = get_actions_kind4();
        return actions;
    case ITEM_ITEM:
        actions = get_actions_kind5();
        return actions;
    }
}


// =============================================================================


/* KIND 1
 * See actionmanagement.h */
int action_item(game_t *g, action_t *a, item_t *i)
{
    assert(g);
    assert(g->current_player); // assumes game_t has a field for current player
    assert(a);
    assert(i);
    if (a->kind != ITEM) {
        fprintf(stderr, "The action provided is not of the correct type.\n");
        return FAILURE;
    }
    int allowed = FAILURE;
    for (int action = 0; action < i->num_allowed_actions; action++)
        if (a->act == i->allowed_actions[action])
            allowed = SUCCESS;
    if (allowed != SUCCESS) {
        fprintf(stderr, "The action can not be done with this item.\n");
        return FAILURE;
    }
    switch (a->act) {
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
    default: {
        fprintf(stderr, "Action is not of the correct type.\n");
        return FAILURE;
    }
    }
    return SUCCESS;
}


/* KIND 2
 * See actionmanagement.h */
int action_direction(game_t *g, action_t *a, direction_t *d)
{
    assert(g);
    assert(a);
    if (a->kind != DIRECTION) {
        fprintf(stderr, "The action provided is not of the correct type.\n");
        return FAILURE;
    }
    // See game.h
    int moved = player_move(g, d);
    if (moved == SUCCESS) {
        return SUCCESS;
    } else {
        fprintf(stderr, "Player was unable to move.\n");
        return FAILURE;
    }
}


/* KIND 3
 * See actionmanagement.h */
int action_npc(game_t *g, action_t *a, npc_t *n)
{
    assert(g);
    assert(g->current_player);
    assert(a);
    assert(n);
    if (a->kind != NPC) {
        fprintf(stderr, "The action provided is not of the correct type.\n");
        return FAILURE;
    }
    // See game.h
    int available = found_in_room(g, n);
    if (available == FAILURE) {
        fprintf(stderr, "NPC is not in room.\n");
        return FAILURE;
    }
    // See game.h
    int talked = npc_talk(g->current_player, n);
    if (talked == SUCCESS) {
        return SUCCESS;
    } else {
        fprintf(stderr, "Player was unable to talk to NPC.\n");
        return FAILURE;
    }
}



/* KIND 4
 * See actionmanagement.h */
int action_item_npc(game_t *g, action_t *a, item_t *i, npc_t *n)
{
    assert(g);
    assert(g->current_player); // assumes game_t has a field for current player
    assert(a);
    assert(i);
    assert(n);
    if (a->kind != ITEM_NPC) {
        fprintf(stderr, "The action provided is not of the correct type.\n");
        return FAILURE;
    }
    int allowed = FAILURE;
    for (int action = 0; action < i->num_allowed_actions; action++)
        if (a->act == i->allowed_actions[action])
            allowed = SUCCESS;
    if (allowed != SUCCESS) {
        fprintf(stderr, "The action can not be done with this item.\n");
        return FAILURE;
    }
    // See game.h
    int given = remove_inventory_item(g->current_player, i);
    if (given != SUCCESS) {
        fprintf(stderr, "Object could not be moved from inventory.\n");
        return FAILURE;
    }
    fprintf(stderr, "%s", n->dialogue);
    return SUCCESS;
}



/* KIND 5
 * See actionmanagement.h */
int action_item_item(game_t *g, action_t *a,
                     item_t *direct, item_t *indirect)
{
    assert(g);
    assert(g->current_player);
    assert(a);
    assert(direct);
    assert(indirect);
    if (a->kind != ITEM_ITEM) {
        fprintf(stderr, "The action provided is not of the correct type.\n");
        return FAILURE;
    }
    int allowed = FAILURE;
    for (int action = 0; action < direct->num_allowed_actions; action++)
        if (a->act == direct->allowed_actions[action])
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


