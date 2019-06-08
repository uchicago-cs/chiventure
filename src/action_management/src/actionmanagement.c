#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "actionmanagement.h"
#include "common.h"


#define BUFFER_SIZE (100)
#define WRONG_KIND (1)
#define NOT_ALLOWED_DIRECT (2)
#define NOT_ALLOWED_INDIRECT (3)


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
int do_item_action(action_type_t *a, item_t *direct, char **ret_string)
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

    // isolate the direct action (i.e. put, use)
    char *temp = strdup(a->c_name);
    char *direct_action = strtok(a->c_name, "_");

    // checks if the direct action is possible with the direct item
    bool possible = possible_action(direct, direct_action);
    if (possible == false) {
        sprintf(string, "Action %s can't be requested with item %s",
                a->c_name, direct->item_id);
        free(temp);
        *ret_string = string;
        return NOT_ALLOWED_DIRECT;
    }

    // get the direct action struct
    game_action_t *dir_game_act = get_action(direct, direct_action);

    // check if all conditions of the direct action are met
    bool all_clear = all_conditions_met(direct, direct_action);
    if (all_clear == false) {
        sprintf(string, "%s", dir_game_act->fail_str);
        free(temp);
        *ret_string = string;
        return CONDITIONS_NOT_MET;
    }

    // implement the action (i.e. dole out the effects)
    // assume that the item_id field has been changed to an item_t struct
    // the item_t struct is tentatively called affected
    else {
        action_effect_list_t *act_effects = dir_game_act->effects;
        int attr_set = FAILURE;
        while (act_effects) {
            // apply the effects of the direct item action (use, put) on the indirect item
            if (strcmp(act_effects->affected->item_id) == 0) {
                int attr_set;
                switch(act_effects->changed_attribute->attribute_tag) {
                case DOUBLE:
                    attr_set = set_double_attr(act_effects->affected,
                                               act_effects->changed_attribute->attribute_key,
                                               act_effects->changed_attribute->attribute_value);
                    break;
                case BOOLE:
                    attr_set = set_bool_attr(act_effects->affected,
                                             act_effects->changed_attribute->attribute_key,
                                             act_effects->changed_attribute->attribute_value);
                    break;
                case CHARACTER:
                    attr_set = set_char_attr(act_effects->affected,
                                             act_effects->changed_attribute->attribute_key,
                                             act_effects->changed_attribute->attribute_value);
                    break;
                case STRING:
                    attr_set = set_str_attr(act_effects->affected,
                                            act_effects->changed_attribute->attribute_key,
                                            act_effects->changed_attribute->attribute_value);
                    break;
                case INTEGER:
                    attr_set = set_int_attr(act_effects->affected,
                                            act_effects->changed_attribute->attribute_key,
                                            act_effects->changed_attribute->attribute_value);
                    break;
                case ACTIONS:
                    attr_set = set_actions_attr(act_effects->affected,
                                                act_effects->changed_attribute->attribute_key,
                                                act_effects->changed_attribute->attribute_value);
                    break;
                default:
                    sprintf(string, "Attribute Type does not exist");
                    free(temp);
                    *ret_string = string;
                    return ATTRIBUTE_TYPE_DNE;
                }
            }
            act_effects = act_effects->next;
        }
        if (attr_set == FAILURE) {
            sprintf(string, "Effect of Action %s was not applied to Item %s",
                    a->c_name, direct->item_id);
            free(temp);
            *ret_string = string;
            return ATTRIBUTE_NOT_SET;
        }
        // successfully carried out action
        sprintf(string, "%s", dir_game_act->success_str);
        free(temp);
        *ret_string = string;
        return SUCCESS;
    }
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
