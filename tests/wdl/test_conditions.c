#include "wdl/load_item.h"
#include "wdl/load_game.h"
#include "test_wdl.h"

/* conditions_check() 
 * Verifies that the list of conditions (or lacktherof) added to an item action 
 * matches what is specified in the wdl. Assumes that both condition lists are 
 * sorted in the same order.
 * 
 * Parameters:
 * - item: the item to be checked
 * - action: the action whose conditions are being checked 
 */
void conditions_check(char* item, char* action)
{
    obj_t *doc = load_obj_store(FILE_PATH_2);
    cr_assert_not_null(doc, "Document obj failed to load correctly.");

    game_t *g = load_game(doc);
    cr_assert_not_null(g, "Game failed to load correctly.");

    /* get list of conditions from game action (1) */
    item_t *i = get_item_from_game(g, item);
    cr_assert_not_null(i, "Issue grabbing item %s from game.", item);
    
    game_action_t *a = get_action(i, action);
    cr_assert_not_null(a, "Issue grabbing action %s from item %s.", action, item);
    condition_list_t *conditions_ls = a->conditions;

    /* get conditions object from wdl (2) */
    obj_t *item_obj = obj_get_attr(doc, "ITEMS", false);
    item_obj = obj_get_attr(item_obj, i->item_id, false);
    cr_assert_not_null(item_obj, "Issue grabbing item obj %s from wdl.", item);

    obj_t *action_obj = obj_get_attr(item_obj, action, false);
    cr_assert_not_null(action_obj, 
                       "Issue grabbing action obj %s from item %s in wdl.", 
                       action, item);
    obj_t *conditions_obj = obj_get_attr(action_obj, "conditions", false);

    /* compare (1) and (2) */
    if (conditions_obj != NULL)
    {
        obj_t *curr;
        int cond_index = 1;
        DL_FOREACH(conditions_obj->data.lst, curr)
        {
            cr_assert_not_null(conditions_ls, 
                                "Action %s for item %s has fewer conditions "
                                "allocated than what was specified in wdl",
                                action, item);
            
            switch(conditions_ls->condition_tag) 
            {
                case (ATTRIBUTE):
                    /* TODO when attribute conditions are fully implemented */
                    break;
                case (INVENTORY): ;
                    /* Check correct condition type */
                    char *cond_type = obj_get_str(curr, "type");
                    cr_assert_eq(cond_type, "INVENTORY", 
                                 "Condition %d type in wdl does not match "
                                 "condition %d type in condition list for %s",
                                 cond_index, cond_index, action);
                    
                    /* Check correct item required */
                    char *n1 = conditions_ls->condition.inventory_type->expected_item->item_id;
                    char *n2 = obj_get_str(curr, "item_id");
                    cr_assert_eq(n1, n2, 
                                 "Condition %d item_id in wdl does not match "
                                 "condition %d item_id in condition list for %s",
                                 cond_index, cond_index, action);
                    break;
                case (LEVEL):
                    /* TODO when level conditions are fully implemented */
                    break;
            }
            conditions_ls = conditions_ls->next;
            cond_index++;
        }

        cr_assert_null(conditions_ls, 
                       "Action %s for item %s more conditions allocated than "
                       "what is specified in wdl", action, item);   
    } 
    else 
    {
        cr_assert_null(conditions_ls, 
                       "Action %s for item %s has no conditions "
                       "specified in wdl, but action condition list is not NULL",
                       action, item);
    }

}

Test(conditions, chair_pull) {
    conditions_check("CHAIR", "PULL");
}

Test(conditions, chair_take) {
    conditions_check("CHAIR", "TAKE");
}

Test(conditions, table_pull) {
    conditions_check("TABLE", "PULL");
}

Test(conditions, table_take) {
    conditions_check("TABLE", "TAKE");
}