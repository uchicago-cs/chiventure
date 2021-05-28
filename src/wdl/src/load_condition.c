#include "wdl/load_condition.h"

/* build_item_condition
 * converts a item condition object into an item-specific condition struct,
 * which it returns
 * 
 * parameters:
 * - item_cond_obj: the item condition object
 * - g: the game
 *
 * returns:
 * - the item condition
 * - NULL if unsuccessful
 */
condition_t *build_item_condition(obj_t *item_cond_obj, game_t *g)
{
    if (obj_get_type(item_cond_obj, "item_id") != TYPE_STR) {
        fprintf(stderr, "Attribute \"item_id\" is either missing or has the "
                "incorrect value type.\n");
        return NULL;
    }

    item_t *i = get_item_from_game(g, obj_get_str(item_cond_obj, "item_id"));

    return inventory_condition_new(g->curr_player, i);
}

/* See load_condition.h */
condition_t *build_conditions(obj_t *conditions_obj, game_t *g)
{
    // verify the condition list's attributes
    if (list_type_check(conditions_obj, conditions_type_check) != SUCCESS) {
        fprintf(stderr, "Conditions list fails type checking.\n");
        return NULL;
    }

    condition_t *conditions = NULL;
    condition_t *cond;
    char *type;
    obj_t *curr;

    DL_FOREACH(conditions_obj->data.lst, curr)
    {
        type = obj_get_str(curr, "type");

        if (strcmp(type, "INVENTORY") == 0) {
            if ((cond = build_item_condition(curr, g)) == NULL) {
                fprintf(stderr, "Could not create item condition.\n");
                return NULL;
            }
            LL_APPEND(conditions, cond);
        }
        else {
            fprintf(stderr, "Specified condition type (%s) not currently "
                    "supported.\n", type);
            return NULL;
        }
    }

    return conditions;
}
