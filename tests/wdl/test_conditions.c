#include <criterion/logging.h>
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
    obj_t *doc = __get_doc_obj("DEFAULT.json", FILE_PATH_2);
    cr_assert_not_null(doc, "Document obj failed to load correctly.");

    game_t *g = load_game(doc);
    cr_assert_not_null(g, "Game failed to load correctly.");


    /* get list of conditions from game action (1) */
    item_t *i = get_item_from_game(g, item);
    cr_assert_not_null(i, "Issue grabbing item %s from game.", item);
    
    agent_t *item_agent;
    item_agent->item = i;
    game_action_t *a = get_action(item_agent, action);
    cr_assert_not_null(a, "Issue grabbing action %s from item %s.", action, item);
    condition_list_t *conditions_ls = a->conditions;


    /* get conditions object from wdl (2) */
    obj_t *item_obj = obj_get_attr(doc, "ITEMS", false);
    cr_assert_not_null(item_obj, "Issue grabbing all items from wdl.");
    item_obj = obj_get_attr(item_obj, item, false);
    cr_assert_not_null(item_obj, "Issue grabbing item obj %s from wdl.", item);

    obj_t *actions_ls = obj_get_attr(item_obj, "actions", false);
    cr_assert_not_null(actions_ls, 
                       "Issue grabbing actions obj from item %s in wdl.", item);
    obj_t *action_obj;
    DL_FOREACH(actions_ls->data.lst, action_obj)
    {
        char* curr_name = obj_get_str(action_obj, "action");
        if (!strcmp(curr_name, action))
        {
            break;
        }
    }  
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
                    char *cond_type = case_insensitized_string(obj_get_str(curr, "type"));
                    cr_assert_not_null(cond_type, "type for condition %d is NULL",
                                       cond_index);
                    cr_assert_str_eq(cond_type, "inventory", 
                                 "Condition %d type (%s) in wdl does not match "
                                 "condition %d type in condition list for %s %s",
                                 cond_index, cond_type, cond_index, action, item); 
                    
                    /* Check correct item required */
                    char *n1 = conditions_ls->condition.inventory_type->expected_item->item_id;
                    char *n2 = case_insensitized_string(obj_get_str(curr, "item_id"));
                    cr_assert_not_null(n2, "item_id for condition %d is NULL",
                                       cond_index);
                    cr_assert_str_eq(n1, n2, 
                                 "Condition %d item_id (%s) in wdl does not match "
                                 "condition %d item_id (%s) in condition list for %s %s",
                                 cond_index, n2, cond_index, n1, action, item);
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