#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validate.h"

// The following functions assist with iterating through lists of objects
/* see validate.h */
bool list_type_check(attr_list_t *ls, bool(*validate)(obj_t*))
{
    if (ls == NULL)
        return false; // if the function returns false, it will halt parsing

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
    if (ls == NULL)
    {
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
/* connections_get_list()
 * a helper function for check_connections that gets a list of connections
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

    if (connections == NULL)
        return NULL;
    else
        return obj_list_attr(connections);
}

/* check_connection_attr()
 * a helper function for check_connections() that checks the attributes of connections
 * associated with a room object
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
    bool id = true, direction = true, through = true;

    if (obj_get_type(obj, "to") != TYPE_STR)
        id = false;
    if (obj_get_type(obj, "direction") != TYPE_STR)
        direction = false;
    if (obj_get_type(obj, "through") != TYPE_STR)
        through = false;

    return (id && direction && through);
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
    bool id_ver = true, short_ver = true, long_ver = true;

    // verify each field
    if (obj_get_type(obj, "id") != TYPE_STR)
        id_ver = false;
    if (obj_get_type(obj, "short_desc") != TYPE_STR)
        short_ver = false;
    if (obj_get_type(obj, "long_desc") != TYPE_STR)
        long_ver = false;

    // verify each attribute
    bool connections_ver = connection_type_check(obj);

    return (id_ver && short_ver && long_ver && connections_ver);
}

// The following functions regard item type checking
/* See validate.h */
bool item_type_check(obj_t *obj)
{
    // fields to verify
    bool id_ver = true, short_ver = true, long_ver = true, in_ver = true,
    state_ver = true;

    // verify each attribute
    if (obj_get_type(obj, "id") != TYPE_STR)
        id_ver = false;
    if (obj_get_type(obj, "short_desc") != TYPE_STR)
        short_ver = false;
    if (obj_get_type(obj, "long_desc") != TYPE_STR)
        long_ver = false;
    if (obj_get_type(obj, "in") != TYPE_STR)
        in_ver = false;
    if (obj_get_type(obj, "state") != TYPE_STR)
        state_ver = false;

    return (id_ver && short_ver && long_ver && in_ver && state_ver);
}

// The following functions regard game type checking
/* See validate.h */
bool game_type_check(obj_t *obj)
{
    attr_list_t *temp = obj_list_attr(obj);
    obj_t *game = temp->obj;

    // fields to verify
    bool start_ver = true, intro_ver = true;

    // verify each attribute
    if (obj_get_type(game, "start") != TYPE_STR)
        start_ver = false;
    if (obj_get_type(game, "intro") != TYPE_STR)
        intro_ver = false;

    return (start_ver && intro_ver);
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
