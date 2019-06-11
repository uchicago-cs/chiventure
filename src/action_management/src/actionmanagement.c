#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "actionmanagement.h"
#include "common.h"

#define BUFFER_SIZE (100)
#define WRONG_KIND (2)
#define NOT_ALLOWED_DIRECT (3)
#define NOT_ALLOWED_INDIRECT (4)
#define NOT_ALLOWED_PATH (5)
#define CONDITIONS_NOT_MET (6)
#define EFFECT_NOT_APPLIED (7)


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
int do_item_action(action_type_t *a, item_t *i, char **ret_string)
{
    assert(a);
    assert(direct);

    char *string = malloc(BUFFER_SIZE); // buffer

    // checks if the action type is the correct kind
    if (a->kind != ITEM) {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }

    // checks if the action is possible
    int possible = possible_action(i, a->c_name);
    if (possible == FAILURE) {
        sprintf(string, "Action %s can't be requested with item %s",
                a->c_name, i->item_id);
        *ret_string = string;
        return NOT_ALLOWED_DIRECT;
    }

    // get the game action struct
    game_action_t *game_act = get_action(i, a->c_name);

    // check if all conditions are met
    int all_clear = all_conditions_met(i, a->c_name);
    if (all_clear == FAILURE) {
        sprintf(string, "%s", dir_game_act->fail_str);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }

    // implement the action (i.e. dole out the effects)
    else {
        int applied_effects;
        applied_effects = do_all_effects(i, a->c_name);
        if (applied_effects == FAILURE) {
            sprintf(string, "Effect(s) of Action %s were not applied", a->c_name);
            *ret_string = string;
            return EFFECT_NOT_APPLIED;
        }
        else {
            // successfully carried out action
            sprintf(string, "%s", dir_game_act->success_str);
            *ret_string = string;
            return SUCCESS;
        }
    }
}


/* KIND 2
 * See actionmanagement.h */
int do_path_action(chiventure_ctx_t *c, action_type_t *a, path_t *p, char **ret_string)
{
    assert(c);
    assert(c->game);
    assert(c->game->curr_room);
    assert(a);
    

    /* INITIALIZATION */
    char *string = malloc(BUFFER_SIZE);
    char *direction = p->direction;
    game_t *g = c->game;
    room_t *room_dest = p->dest;
    room_t *room_curr = g->curr_room;
    path_t *path_found = path_search(room_curr, direction);

    /* VALIDATION */
    // checks if the action type is the correct kind
    if (a->kind != PATH) {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }
    // validate existence of path and destination
    if ((path_found == NULL) || (room_dest == NULL)) {
        sprintf(string, "The path or room provided was invalid.");
        *ret_string = string;
        return NOT_ALLOWED_PATH;
    }

    /* PERFORM ACTION */
    int move = move_room(g, room_dest);

    if (move == SUCCESS) {
        sprintf(string, "Moved into %s. %s", 
                room_dest->room_id, room_dest->long_desc);
        *ret_string = string;
        return SUCCESS;
    }
    else {
        sprintf(string, 
                "Move action %s via %s into %s failed.",
                a->c_name, direction, room_dest->room_id);
        *ret_string = string;
        return NOT_ALLOWED_PATH;
    }
}


/* KIND 3
 * See actionmanagement.h */
int do_item_item_action(action_type_t *a, item_t *direct,
                        item_t *indirect, char **ret_string)
{
    assert(a);
    assert(direct);
    assert(indirect);
    char *string = malloc(BUFFER_SIZE); // buffer
    // checks if the action type is the correct kind
    if (a->kind != ITEM_ITEM) {
        sprintf(string, "The action type provided is not of the correct kind");
        *ret_string = string;
        return WRONG_KIND;
    }
    // checks if the action can be used on the direct item
    int allowed = allowed_action(direct, a->c_name);
    if (allowed != SUCCESS) {
        sprintf(string, "Action %s can't be requested on item %s",
                a->c_name, direct->item_id);
        *ret_string = string;
        return NOT_ALLOWED_DIRECT;
    }
    // checks if the action can be used on the indirect item
    allowed = allowed_action(indirect, a->c_name);
    if (allowed != SUCCESS) {
        sprintf(string, "Action %s can't be requested on item %s",
                a->c_name, indirect->item_id);
        *ret_string = string;
        return NOT_ALLOWED_INDIRECT;
    }
    /* TODO: implement the rest of this function, using game state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    sprintf(string, "Requested action %s with %s on %s",
            a->c_name, direct->item_id, indirect->item_id);
    *ret_string = string;
    return SUCCESS;
}
