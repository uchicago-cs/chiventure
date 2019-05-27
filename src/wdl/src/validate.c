#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validate.h"
#include "actionmanagement.h"

// The following functions assist with iterating through lists of objects

/* see validate.h */
bool list_type_check(attr_list_t *ls, bool(*validate)(obj_t*))
{
    if (ls == NULL) {
      return false; // if the function returns false, it will halt parsing
    }

    bool result = true;
    attr_list_t *curr = ls;

    while(curr != NULL) {
        result = (result && (*validate)(curr->obj));
        curr = curr->next;
    }

    return result;
}

/* see validate.h */
void list_print(attr_list_t *ls, void (*print)(obj_t*))
{
    if (ls == NULL) {
        fprintf(stderr, "list_print failed, list empty\n");
        return;
    }

    attr_list_t *curr = ls;

    while(curr != NULL) {
        (*print)(curr->obj);
        curr = curr->next;
    }

    return;
}

// The following functions regard room type checking

/* conditions_get_list()
 * a helper function for connection_type_check that gets a list of conditions
 * associated with a connection for a room object
 *
 * parameters:
 *  - obj: a connection object
 *
 * returns:
 *  - an attribute list of all the conditions for connection
 *  - null if an error occurs or no list can be generated
 */
attr_list_t *conditions_get_list(obj_t *obj)
{
    obj_t *conditions = obj_get_attr(obj, "conditions", false);

    if (conditions == NULL) {
        return NULL;
    }
    else {
        return obj_list_attr(conditions);
    }
}

/* check_condition_attr()
 * a helper function for check_conditions() that checks the attributes of  a
 * condition associated with a connection object
 *
 * parameters:
 * - obj: a condition object
 *
 * returns:
 * - true if condition types match, else return false
 */
bool check_condition_attr(obj_t *obj)
{
    // verify types of fields
    bool id = (obj_get_type(obj, "id") == TYPE_STR);
    bool state = (obj_get_type(obj, "state") == TYPE_STR);
    bool value = (obj_get_type(obj, "value") == TYPE_STR);

    return (id && state && value);
}

/* condition_type_check()
 * a helper function for connection_type_check that checks all conditions and its
 * attributes associated with a connection object
 *
 * parameters:
 * - obj: a connection object
 *
 * returns:
 * - true if attributes of all conditions match, else return false
 */
bool condition_type_check(obj_t *obj)
{
    attr_list_t *ls = conditions_get_list(obj);

    // call connection_type_check on each connection
    bool check = list_type_check(ls, check_condition_attr);

    return check;
}

/* connections_get_list()
 * a helper function for connection_type_check that gets a list of connections
 * associated with a room object
 *
 * parameters:
 *  - obj: a room object
 *
 * returns:
 *  - an attribute list of all the connections
 *  - null if an error occurs or no list can be generated
 */
attr_list_t *connections_get_list(obj_t *obj)
{
    obj_t *connections = obj_get_attr(obj, "connections", false);

    if (connections == NULL) {
        return NULL;
    }
    else {
        return obj_list_attr(connections);
    }
}

/* check_connection_attr()
 * a helper function for connection_type_check() that checks the attributes of
 * connections associated with a room object
 *
 * parameters:
 * - obj: a connection object
 *
 * returns:
 * - true if connection types match, else return false
 */
bool check_connection_attr(obj_t *obj)
{
    // verify types of fields
    bool id = (obj_get_type(obj, "to") == TYPE_STR);
    bool direction = (obj_get_type(obj, "direction") == TYPE_STR);
    bool through = (obj_get_type(obj, "through") == TYPE_STR);
    bool conditions = condition_type_check(obj);

    return (id && direction && through && conditions);
}

/* connection_type_check()
 * a helper function for room_type_check that checks all connections and its
 * attributes associated with a room object
 *
 * parameters:
 * - obj: a room object
 *
 * returns:
 * - true if attributes of all connections match, else return false
 */
bool connection_type_check(obj_t *obj)
{
    attr_list_t *ls = connections_get_list(obj);

    // call connection_type_check on each connection
    bool check = list_type_check(ls, check_connection_attr);

    return check;
}

/* See validate.h */
bool room_type_check(obj_t *obj)
{
    // fields to verify
    bool id_ver = (obj_get_type(obj, "id") == TYPE_STR);
    bool short_ver = (obj_get_type(obj, "short_desc") == TYPE_STR);
    bool long_ver = (obj_get_type(obj, "long_desc") == TYPE_STR);

    // verify each attribute
    bool connections_ver = connection_type_check(obj);

    return (id_ver && short_ver && long_ver && connections_ver);
}

// The following functions regard item type checking

/* See validate.h */
bool item_type_check(obj_t *obj)
{
    // fields to verify
    bool id_ver = (obj_get_type(obj, "id") == TYPE_STR);
    bool short_ver = (obj_get_type(obj, "short_desc") == TYPE_STR);
    bool long_ver = (obj_get_type(obj, "long_desc") == TYPE_STR);
    bool in_ver = (obj_get_type(obj, "in") == TYPE_STR);

    return (id_ver && short_ver && long_ver && in_ver);
}

// The following functions regard game type checking

/* See validate.h */
bool game_type_check(obj_t *obj)
{
    attr_list_t *temp = obj_list_attr(obj);
    obj_t *game = temp->obj;

    // fields to verify
    bool start_ver = (obj_get_type(game, "start") == TYPE_STR);
    bool intro_ver = (obj_get_type(game, "intro") == TYPE_STR);

    return (start_ver && intro_ver);
}


// the following functions regard action type checking

/* action_validate()
 * a helper function for action_type_check() that verifies the given action is on
 * the list of approved actions determined by action-management
 *
 * parameters
 *  - ls: a list of approved actions
 *  - str: the action to check
 *
 * returns
 *  - true if the action is valid
 *  - false if else
 */
bool action_validate(char *str)
{   
    // getting a list of valid actions; 
    // note that in the future we may wish to use a hasth table
    list_action_type_t *valid_actions = get_supported_actions();

    list_action_type_t *curr = valid_actions;

    while (curr != NULL) {
        if (strcmp(curr->act->c_name, str) == 0) {
            return true;
        }
    }

    return false;
}

/* see validate.h */
bool action_type_check(obj_t *obj)
{
    // fields to verify
    bool action_type = (obj_get_type(obj, "action") == TYPE_STR);
    bool action_valid =  action_validate(obj_get_str(obj, "action"));

    return (action_type && action_valid);
}

// The following are print functions to print out specific fields within a
// specified object

/* print_conditions_attr
 * helper function for print_connection that prints out the attributes of a
 * condition
 *
 * parameters:
 * - obj: a condition object
 *
 * side effects:
 * prints out the attributes of a condition
 */
 void print_conditions_attr(obj_t *obj)
 {
    // print each attribute within connection object
    printf("id: %s\n", obj_get_str(obj, "id"));
    printf("state: %s\n", obj_get_str(obj, "state"));
    printf("value: %s\n", obj_get_str(obj, "value"));
    return;
 }

 /* print_conditions
   * helper function for print_connections that prints out the attributes of all
   * conditions within a connection object
   *
   * parameters:
   * - obj: a connection object
   *
   * side effects:
   * prints out all conditions of a room
   */
  void print_conditions(obj_t *obj)
  {
    // obtain list of conditions
    attr_list_t *ls = conditions_get_list(obj);

    // call list_print with print_connection_attr
    list_print(ls, print_conditions_attr);
    return;
  }

/* print_connection_attr
 * helper function for print_connection that prints out the attributes of a
 * connection
 *
 * parameters:
 * - obj: a connection object
 *
 * side effects:
 * prints out the attributes of a connection
 */
 void print_connection_attr(obj_t *obj)
 {
    // print each attribute within connection object
    printf("connected to: %s\n", obj_get_str(obj, "to"));
    printf("direction: %s\n", obj_get_str(obj, "direction"));
    printf("through: %s\n", obj_get_str(obj, "through"));

    // print the conditions
    print_conditions(obj);
    return;
 }

 /* print_connections
  * helper function for print_room that prints out the attributes of all
  * connections within a room object
  *
  * parameters:
  * - obj: a room object
  *
  * side effects:
  * prints out all connections of a room
  */
void print_connections(obj_t *obj)
{
    // obtain list of connections
    attr_list_t *ls = connections_get_list(obj);

    // call list_print with print_connection_attr
    list_print(ls, print_connection_attr);
    return;
}

/* See validate.h */
void print_room(obj_t *obj)
{
    // print room attributes
    printf("ROOM: %s\n", obj_get_str(obj, "id"));
    printf("short desc: %s\n", obj_get_str(obj, "short_desc"));
    printf("long_desc: %s\n", obj_get_str(obj, "long_desc"));
    // print connections
    print_connections(obj);
    return;
}

/* See validate.h */
void print_item(obj_t *obj)
{
    // print item attributes
    printf("ITEM: %s\n", obj_get_str(obj, "id"));
    printf("short_desc: %s\n", obj_get_str(obj, "short_desc"));
    printf("long_desc: %s\n", obj_get_str(obj, "long_desc"));
    printf("in: %s\n", obj_get_str(obj, "in"));
    printf("state: %s \n", obj_get_str(obj, "state"));
    return;
}

/* See validate.h */
void print_game(obj_t *obj)
{
    // print game attributes
    printf("GAME introduction: %s\n", obj_get_str(obj, "intro"));
    printf("starting room: %s\n", obj_get_str(obj, "start"));
    return;
}

/* See validate.h */
void print_document(obj_t *obj)
{
    // Extract individual objects
    obj_t *room_obj = obj_get_attr(obj, "ROOMS", false);
    obj_t *item_obj = obj_get_attr(obj, "ITEMS", false);
    obj_t *game_obj = obj_get_attr(obj, "GAME", false);

    // Extract list of rooms and items
    attr_list_t *rooms_ls = obj_list_attr(room_obj);
    attr_list_t *items_ls = obj_list_attr(item_obj);

    // Print game
    printf("printing game attributes:\n");
    print_game(game_obj);

    // Print rooms
    printf("printing all rooms and their attributes:\n");
    list_print(rooms_ls, print_room);

    // Print items
    printf("printing all items and their attributes\n");
    list_print(items_ls, print_item);
}
