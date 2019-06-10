#include "load_item.h"

/*
 * get_game_action()
 * A helper fuction to get the pointer to the game_action struct corresponding to
 * the action in the attribute list in the actions field of an item.
 *
 * parameters
 *  - action: a string corresponding to the action ID
 *  - val: a list of valid actions
 *
 * returns:
 *  - a pointer to an game_action struct
 *  - NULL if an error occurs
 */
action_type_t *get_game_action(char *action, list_action_type_t *valid)
{
    list_action_type_t *curr = valid;

    // finding matching action_type_t
    while (curr != NULL) {
        if (strcmp(curr->act->c_name, action) == 0) {
            break;
        }
        curr = curr->next;
    }

    return curr->act;
}

/* See load_item.h */
int load_actions(obj_t *doc, item_t *i)
{
    // getting a list of actions from item
    attr_list_t *action_ls = get_item_actions(doc);
    if (action_ls == NULL) {
        fprintf(stderr, "action fails type checking, or action list is empty\n");
        return -1;
    }

    attr_list_t *curr = action_ls;
    // setting action attributes; might need to change this in the future

    action_type_t *temp;
    list_action_type_t *val_actions = get_supported_actions();

    while (curr != NULL) {
        temp = get_game_action(obj_get_str(curr->obj, "action"), val_actions);
        set_act_attr(i, obj_get_str(curr->obj, "action"), temp);

        curr = curr->next;
    }

    return 0;
}

/* see load_items.h */
int add_single_condition(game_t *game, char* action, char* item_id, obj_t *cond)
{
  // get id of item specified in the condition, its attribute, and value
  char *cond_id = obj_get_str(cond, "id");
  char *attribute = obj_get_str(cond, "attribute");
  char *value = obj_get_str(cond, "value");

  // add condition to action for the specified item
  int result = add_condition(game, action, item_id, cond_id, attribute, value);

  if (result == 1) {
      fprintf(stderr, "Source item with id %s does not exist\n", item_id);
      return 1;
  }
  else if (result == 2) {
      fprintf(stderr, "Item with id %s to check condition of does"
      " not exist\n",  cond_id);
      return 1;
  }
  else if (result == 3) {
      fprintf(stderr, "Item action %s does not exist\n",
              action);
      return 1;
  }
  else if (result == 4) {
    fprintf(stderr, "Attribute %s to be checked for item %s does "
    "not exist\n", attribute, cond_id);
    return 1;
  }
  else {
    return 0;
  }
}

/* see load_items.h */
int add_single_effect(game_t *game, char* action, char* item_id, obj_t *effect)
{
  // get id of item specified in the effect, its attribute, and value
  char *set_id = obj_get_str(effect, "id");
  char *attribute = obj_get_str(effect, "attribute");
  char *value = obj_get_str(effect, "value");

  // add effect to action for the specified item
  int result = add_effect(g, action, id, set_id, attribute, value);

  if (result == 1) {
      fprintf(stderr, "Source item with id %s does not exist\n", item_id);
      return 1;
  }
  else if (result == 2) {
      fprintf(stderr, "Item to modify with id %s does not exist\n",
              set_id);
      return 1;
  }
  else if (result == 3) {
      fprintf(stderr, "Item action %s does not exist\n",
              action);
      return 1;
  }
  else if (result == 4) {
     fprintf(stderr, "Attribute %s to be modified for item %s "
                    "does not exist\n", attribute, set_id);
    return 1;
  }
  else {
    return 0;
  }
}

/* see load_items.h */
int add_cond_and_eff_to_actions(obj_t *doc, game_t *g)
{
    obj_t *items_obj = obj_get_attr(doc, "ITEMS", false); // extract item object
    attr_list_t *curr = obj_list_attr(items_obj); // extract list of items
    if (curr == NULL) { // if items list is empty then return 1
        fprintf(stderr, "Items list is empty\n");
        return 1;
    }
    // while list of items exists, create new game_struct item, add item to game
    while (curr != NULL) {
        char *id = obj_get_str(curr->obj, "id"); // obtain item id
        // extract actions object
        obj_t *actions_obj = obj_get_attr(items_obj, "actions", false);
        // extract list of actions
        attr_list_t *action_curr = obj_list_attr(actions_obj);
        // if actions list is empty then return 1
        if (action_curr == NULL) {
            fprintf(stderr, "Actions list is empty\n");
            return 1;
        }
        // iterate through actions list
        while (action_curr != NULL) {
          // obtain action name
          char *action_name = obj_get_str(action_curr->obj, "action");
          // extract conditions object
          obj_t *cond_obj = obj_get_attr(actions_obj, "conditions", false);
          // extract list of conditions
          attr_list_t *cond_curr = obj_list_attr(cond_obj);

          // if conditions list is empty then print message but do not return
          // as it is possible for an action to not have any conditions
          if (cond_curr == NULL) {
              fprintf(stderr, "Conditions list is empty for action %s\n",
                    action_name);
          }
          //CONDITIONS
            while (cond_curr != NULL) {  // iterate through conditions list
              single_cond = cond_curr->obj;
              //call add_single_condition function
              int cond_info = add_single_condition(g, action_name, id, single_cond);

              if (cond_info == 0) {
                fprintf(stderr, "The condition for action %s of item %s"
                " was added successfully\n", action_name, id);
              } else {
                fprintf(stderr, "The condition for action %s of item %s"
                " could not be added\n", action_name, id);
                return 1;
              }

              cond_curr = cond_curr->next;
            }

          //EFFECTS
          // extract effects (set) object
          obj_t *set_obj = obj_get_attr(actions_obj, "set", false);
          // extract list of set effects
          attr_list_t *set_curr = obj_list_attr(set_obj);
          // if effects list is empty then print message but do not return,
          // as it is possible for an action to have no effects
          if (set_curr == NULL) {
              fprintf(stderr, "Effects list is empty for action %s\n",
            action_name);
          }

            while (set_curr != NULL) { // iterate through effects list
              int set_info = add_single_effect(g, action_name, id, single);

              if (set_info == 0) {
                fprintf(stderr, "The effect for action %s of item %s"
                " was added successfully\n", action_name, id);
              } else {
                fprintf(stderr, "The effect for action %s of item %s"
                " could not be added\n", action_name, id);
                return 1;
              }
                set_curr = set_curr->next;
            }

          action_curr = action_curr->next;
        }

        curr = curr->next;
      }
return 0;
}
