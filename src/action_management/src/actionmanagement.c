#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "actionmanagement.h"
#include "common.h"


#define BUFFER_SIZE (100)


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
char *do_item_action(game_t *g, action_type_t *a, item_t *i)
{
    // a couple confirmation checks
    assert(g);
    assert(g->curr_player); // needed for sprint 4
    assert(a);
    assert(i);
    char *ret_string = malloc(BUFFER_SIZE); // buffer
    // checks if the action type is the correct kind
    if (a->kind != ITEM) {
        sprintf(ret_string, "The action type provided is not of the correct kind");
        return ret_string;
    }
    // checks if the action can be used on the item
    int allowed = allowed_action(i, a->c_name);
    if (allowed != SUCCESS) {
        sprintf(ret_string, "Action %s can't be requested on item %s",
                a->c_name, i->item_id);
        return ret_string;
    }
    /* TODO: implement the rest of this function, using game_state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    sprintf(ret_string, "Requested action %s on item %s",
            a->c_name, i->item_id);
    return ret_string;
}


/* KIND 2
 * See actionmanagement.h */
char *do_path_action(game_t *g, action_type_t *a, path_t *p)
{
    assert(g);
    assert(g->curr_player);
    assert(a);
    char *ret_string = malloc(BUFFER_SIZE); // buffer
    // checks if the action type is the correct kind
    if (a->kind != PATH) {
        sprintf(ret_string, "The action type provided is not of the correct kind");
        return ret_string;
    }
    /* TODO: implement the rest of this function, using game state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    sprintf(ret_string, "Requested action %s in direction %s into room %s",
            a->c_name, p->direction, p->dest->room_id);
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
    char *ret_string = malloc(BUFFER_SIZE); // buffer
    // checks if the action type is the correct kind
    if (a->kind != ITEM_ITEM) {
        sprintf(ret_string, "The action type provided is not of the correct kind");
        return ret_string;
    }
    // checks if the action can be used on the direct item
    int allowed = allowed_action(direct, a->c_name);
    if (allowed != SUCCESS)
    {
        sprintf(ret_string, "Action %s can't be requested on item %s",
                a->c_name, direct->item_id);
        return ret_string;
    }
    // checks if the action can be used on the indirect item
    allowed = allowed_action(indirect, a->c_name);
    if (allowed != SUCCESS) {
        sprintf(ret_string, "Action %s can't be requested on item %s",
                a->c_name, indirect->item_id);
        return ret_string;
    }
    /* TODO: implement the rest of this function, using game state funcs
     * Will perform the action if all checks pass (Sprint 4)
     */
    
    /* initialize all the game-state structs */
    attribute_list_t *attributes_direct = get_all_attributes(direct);
    attribute_list_t *attributes_indirect = get_all_attributes(direct);
    game_action_t *action_direct = get_action(direct, a->c_name);
    game_action_t *action_indirect = get_action(indirect, a->c-name);

    // this is to count how many elements are in each list
    attribute_list_t *temp_att;
    int count_attributes_direct, count_attributes_indirect;
    LL_COUNT(attributes_direct, temp_att, count_attributes_direct);
    LL_COUNT(attributes_indirect, temp_att, count_attributes_indirect);

    action_effect_list_t *temp_eff;
    int count_effects_direct, count_effects_indirect;
    LL_COUNT(action_direct->effects, temp_eff, count_effects_direct);
    LL_COUNT(action_indirect->effects, temp_eff, count_effects_indirect);

    action_condition_list_t *temp_cond;
    int count_conditions_direct, count_conditions_indirect;
    LL_COUNT(action_indirect->conditions, temp_cond, count_conditions_direct);
    LL_COUNT(action_indirect->conditions, temp_cond, count_conditions_direct);

    /* alter the game-state structs via action management */
    

    sprintf(ret_string, "Requested action %s with %s on %s",
            a->c_name, direct->item_id, indirect->item_id);
    return ret_string;
}
