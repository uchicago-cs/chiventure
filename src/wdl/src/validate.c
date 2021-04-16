#include <stdio.h>
#include <string.h>

#include "wdl/validate.h"

// The following functions assist with iterating through lists of objects

/* see validate.h */
int list_type_check(obj_t *ls, int(*validate)(obj_t*))
{
    if (ls == NULL)
    {
        return FAILURE; // if the function returns FAILURE, it will halt parsing
    }

    int result = SUCCESS;

    obj_t *curr, *tmp;
    HASH_ITER(hh, ls, curr, tmp)
    {
        result = (result && (*validate)(curr));
    }

    return result;
}

/* see validate.h */
void list_print(obj_t *ls, void (*print)(obj_t*))
{
    if (ls == NULL)
    {
        fprintf(stderr, "list_print failed, list empty\n");
        return;
    }

    obj_t *curr, *tmp;
    HASH_ITER(hh, ls, curr, tmp)
    {
        (*print)(curr);
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
obj_t *conditions_get_list(obj_t *obj)
{
    obj_t *conditions = obj_get_attr(obj, "conditions", false);

    return conditions;
}

/* check_condition_attr()
 * a helper function for check_conditions() that checks the attributes of  a
 * condition associated with a connection object
 *
 * parameters:
 * - obj: a condition object
 *
 * returns:
 * - SUCCESS if condition types match, else return FAILURE
 */
int check_condition_attr(obj_t *obj)
{
    // verify types of fields
    int id = (obj_get_type(obj, "id") == TYPE_STR);
    int state = (obj_get_type(obj, "state") == TYPE_STR);
    int value = (obj_get_type(obj, "value") == TYPE_STR);

    return !(id && state && value);
}

/* condition_type_check()
 * a helper function for connection_type_check that checks all conditions and its
 * attributes associated with a connection object
 *
 * parameters:
 * - obj: a connection object
 *
 * returns:
 * - SUCCESS if attributes of all conditions match, else return FAILURE
 */
int condition_type_check(obj_t *obj)
{
    obj_t *ls = conditions_get_list(obj);

    // call connection_type_check on each connection
    int check = list_type_check(ls, check_condition_attr);

    return check;
}

/* see validate.h */
obj_t *connections_get_list(obj_t *obj)
{
    obj_t *connections = obj_get_attr(obj, "connections", false);

    if (connections == NULL)
    {
        return NULL;
    }
    else
    {
        return connections;
    }
}

/* See validate.h */
int check_connection_attr(obj_t *obj)
{
    // verify types of fields
    int id = (obj_get_type(obj, "to") == TYPE_STR);
    int direction = (obj_get_type(obj, "direction") == TYPE_STR);

    return !(id && direction);
}

/* connection_type_check()
 * a helper function for room_type_check that checks all connections and its
 * attributes associated with a room object
 *
 * parameters:
 * - obj: a room object
 *
 * returns:
 * - SUCCESS if attributes of all connections match, else return FAILURE
 */
int connection_type_check(obj_t *obj)
{
    obj_t *ls = connections_get_list(obj);

    // call connection_type_check on each connection
    int check = list_type_check(ls, check_connection_attr);

    return check;
}

/* See validate.h */
int room_type_check(obj_t *obj)
{
    // fields to verify
    int id_ver = (obj_get_type(obj, "id") == TYPE_STR);
    int short_ver = (obj_get_type(obj, "short_desc") == TYPE_STR);
    int long_ver = (obj_get_type(obj, "long_desc") == TYPE_STR);

    // verify each attribute
    int connections_ver = connection_type_check(obj);

    if (id_ver == false)
    {
        fprintf(stderr, "id verification failed\n");
    }

    return !(id_ver && short_ver && long_ver && connections_ver);
}

// The following functions regard item type checking

/* See validate.h */
int item_type_check(obj_t *obj)
{
    // fields to verify
    int id_ver = (obj_get_type(obj, "id") == TYPE_STR);
    int short_ver = (obj_get_type(obj, "short_desc") == TYPE_STR);
    int long_ver = (obj_get_type(obj, "long_desc") == TYPE_STR);
    int in = (obj_get_type(obj, "in") == TYPE_STR);

    return !(id_ver && short_ver && long_ver && in);
}

// The following functions regard game type checking

/* See validate.h */
int game_type_check(obj_t *obj)
{
    // fields to verify
    int start_ver = (obj_get_type(obj, "start") == TYPE_STR);
    int intro_ver = (obj_get_type(obj, "intro") == TYPE_STR);
    int end_ver = (obj_get_type(obj, "end.in_room") == TYPE_STR);

    return !(start_ver && intro_ver);
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
 *  - SUCCESS if the action is valid
 *  - FAILURE if else
 */
int action_validate(char *str)
{
    // getting a list of valid actions;
    // note that in the future we may wish to use a hasth table
    list_action_type_t *valid_actions = get_supported_actions();
    list_action_type_t *curr = valid_actions;

    while (curr != NULL)
    {
        if (strcmp(curr->act->c_name, str) == 0)
        {
            return SUCCESS;
        }
        curr = curr->next;
    }

    return FAILURE;
}

void print_list(list_action_type_t *ls)
{
    int i;
    for (i = 0; i < 14; i++)
    {
        printf("%s\n", ls->act->c_name);
        ls = ls->next;
    }
    return;
}

/* see validate.h */
/* INPUTS AN ITEM OBJ */
int action_type_check(obj_t *obj)
{
    // fields to verify
    int action_type = (obj_get_type(obj, "action") == TYPE_STR);
    int action_valid = action_validate(obj_get_str(obj, "action"));

    return !(action_type && action_valid);
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
    obj_t *ls = conditions_get_list(obj);

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
    obj_t *ls = connections_get_list(obj);

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

    // Print game
    printf("printing game attributes:\n");
    print_game(game_obj);

    // Print rooms
    printf("printing all rooms and their attributes:\n");
    list_print(room_obj, print_room);

    // Print items
    printf("printing all items and their attributes\n");
    list_print(item_obj, print_item);

    return;
}
