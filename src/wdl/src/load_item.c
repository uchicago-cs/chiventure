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


/* See load_item.h */
int load_items(obj_t *doc, game_t *g)
{
    // we use extract_objects() instead of obj_list_attr() because the former does type checking
    attr_list_t *items_obj = extract_objects(doc, "ITEMS");
    if (items_obj == NULL) {
        fprintf(stderr, "items fail type checking\n");
    }

    // set current item
    attr_list_t *curr = items_obj;

    // if items list is empty then return -1
    if (curr == NULL) {
        fprintf(stderr, "items list is empty\n");
        return -1;
    }

    // while list of items exists, create new game_struct item, add item to room
    while (curr != NULL) {
        // get id, short_desc, and long_desc
        char *id = obj_get_str(curr->obj, "id");
        char *short_desc = obj_get_str(curr->obj, "short_desc");
        char *long_desc = obj_get_str(curr->obj, "long_desc");
        char *in = obj_get_str(curr->obj, "in");

        // create new game_state item
        item_t *item = item_new(id, short_desc, long_desc);
        /* in parameter yet to implemented by game-state
        item_t *item = item_new(id, short_desc, long_desc, in); */

        //load actions into item
        if(load_actions(curr->obj, item) == -1)
	      {
	          fprintf(stderr, "actions have not been loaded properly");
	          return -1;
	      }

        //retrieve the pointer for the room that the item is located in
        room_t *item_room = find_room_from_game(g, in);

        // add item to room
        add_item_to_room(item_room, item);
        curr = curr->next;
    }
    return 0;
}

/* see load_items.h */
int add_cond_and_eff_to_actions(obj_t *doc, game_t *g)
{
  // extract item object
  obj_t *items_obj = obj_get_attr(doc, "ITEMS", false);

  // extract list of items
  attr_list_t *curr = obj_list_attr(items_obj);

  // if items list is empty then return 1
  if (curr == NULL) {
    fprintf(stderr, "Items list is empty\n");
    return 1;
  }

  // while list of items exists, create new game_struct item, add item to game
  while (curr != NULL) {
    // obtain item id
    char *id = obj_get_str(curr->obj, "id");

    // get list of actions for the item

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

      //get list of conditions for the action
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
      // iterate through conditions list
      while (cond_curr != NULL) {
	// get id of item specified in the condition, its attribute,
	// and value
	char *cond_id = obj_get_str(cond_curr->obj, "id");
	char *attribute = obj_get_str(cond_curr->obj, "attribute");
	char *value = obj_get_str(cond_curr->obj, "value");

	// add condition to action for the item in game
	int result = add_condition(g, action_name, id, cond_id, attribute, value);

	if (result == 1) {
	  fprintf(stderr, "Source item with id %s does not exist\n", id);
	  return 1;
	}
	else if (result == 2) {
	  fprintf(stderr, "Item with id %s to check condition of does"
		  " not exist\n",  cond_id);
	  return 1;
	}
	else if (result == 3) {
	  fprintf(stderr, "Item action %s does not exist\n",
		  action_name);
	  return 1;
	}
	else if (result == 4) {
	  fprintf(stderr, "Attribute %s to be checked for item %s does "
                  "not exist\n", attribute, cond_id);
	  return 1;
	}
	else {
	  fprintf(stderr, "The condition for action %s of item %s"
		  " was added successfully\n", action_name, id);
	}

	cond_curr = cond_curr->next;

      }

      //EFFECTS
      //get list of effects for the action
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
      // iterate through effects list
      while (set_curr != NULL) {
	// get id of item specified in the effect, its attribute, and value
	char *set_id = obj_get_str(cond_curr->obj, "id");
	char *attribute = obj_get_str(cond_curr->obj, "attribute");
	char *value = obj_get_str(cond_curr->obj, "value");

	// add effect to action for the item in game
	int result = add_effect(g, action_name, id, set_id, attribute, value);

	if (result == 1) {
	  fprintf(stderr, "Source item with id %s does not exist\n", id);
	  return 1;
	}
	else if (result == 2) {
	  fprintf(stderr, "Item to modify with id %s does not exist\n",
		  set_id);
	  return 1;
	}
	else if (result == 3) {
	  fprintf(stderr, "Item action %s does not exist\n",
		  action_name);
	  return 1;
	}
	else if (result == 4) {
	  fprintf(stderr, "Attribute %s to be modified for item %s "
		  "does not exist\n", attribute, set_id);
	  return 1;
	}
	else {
	  fprintf(stderr, "The effect for action %s of item %s"
		  " was added successfully\n", action_name, id);
	}

	set_curr = set_curr->next;
      }

      action_curr = action_curr->next;
    }

    curr = curr->next;
  }
  return 0;
}
