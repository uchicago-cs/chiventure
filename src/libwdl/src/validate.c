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
bool list_print(attr_list_t *ls, bool(*print)(obj_t*))
{
    if (ls == NULL)
        return;

    attr_list_t *curr = ls;

    while(curr != NULL) {
        (*print)(curr->obj);
        curr = curr->next;
    }
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

    if (obj_get_type(obj, "to") != TYPE_STR && obj_get_type(obj, "to") != TYPE_CHAR)
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
    if (obj_get_type(obj, "id") != TYPE_STR && obj_get_type(obj, "id") != TYPE_CHAR)
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
    if (obj_get_type(obj, "id") != TYPE_STR && obj_get_type(obj, "id") != TYPE_CHAR)
        id_ver = false;
    if (obj_get_type(obj, "short_desc") != TYPE_STR)
        short_ver = false;
    if (obj_get_type(obj, "long_desc") != TYPE_STR)
        long_ver = false;
    if (obj_get_type(obj, "in") != TYPE_STR && obj_get_type(obj, "in") != TYPE_CHAR)
        in_ver = false;
    if (obj_get_type(obj, "state") != TYPE_STR)
        state_ver = false;

    return (id_ver && short_ver && long_ver && in_ver && state_ver)
}

// The following functions regard game type checking
/* See validate.h */
bool game_type_check(obj_t *obj)
{
    // fields to verify
    bool start_ver = true, intro_ver = true;

    // verify each attribute
    if (obj_get_type(obj, "start") != TYPE_STR && obj_get_type(obj, "start") !=
        TYPE_CHAR)
        start_ver = false;
    if (obj_get_type(obj, "intro") != TYPE_STR)
        intro_ver = false;

    return (start_ver && intro_ver)
}
