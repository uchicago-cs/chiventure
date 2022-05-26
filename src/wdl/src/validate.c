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
    HASH_ITER(hh, ls->data.obj.attr, curr, tmp)
    {
        // This is an OR because SUCCESS == 0
        result = (result || (*validate)(curr));
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

// The following are helper functions.

/*
 * A helper function for checking that objects don't have illegal (or mispelled) 
 * attributes.
 * 
 * Parameters:
 *  - obj: The object
 *  - legal_attributes: An array of legal attribute names.
 *  - attribute_count: The number of attributes in legal_attributes
 * 
 * Returns:
 *  - true if the object only contains legal attributes.
 *  - false otherwise, and an error message is sent about the offending attribute.
 * 
 *  - Note that attributes may be optional; this function does not care if a 
 *    legal attribute is missing.
 */
bool check_attributes(obj_t* obj, const char* const* legal_attributes, int attribute_count) {
    obj_t *attr, *tmp;
    HASH_ITER(hh, obj->data.obj.attr, attr, tmp) {
        bool found_match = false;
        for (int i = 0; i < attribute_count; i++) {
            if (strncmp(legal_attributes[i], attr->id, MAXLEN_ID) == 0) {
                found_match = true;
                break;
            }
        }
        if (!found_match) {
            fprintf(stderr, "Object %s has illegal attribute named \"%s\".\n",
                    obj->id, attr->id);
            return false;
        }
    }

    return true;
}

/*
 * A helper function for checking types.
 * 
 * Parameters:
 *  - obj: The object
 *  - attribute_name: The attribute in question
 *  - expected_type: The type expected from the attribute
 * 
 * Returns:
 *  - true if the attribute has the right type, or if it does not exist, or if
 *    it exists but has NULL.
 *  - false otherwise.
 */
bool is_type_or_nonexistent(obj_t* obj, char* attribute_name, type_t expected_type) {
    type_t attr_type = obj_get_type(obj, attribute_name);
    return attr_type == expected_type || attr_type == TYPE_ERROR || attr_type == TYPE_NONE;
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
    int short_ver = (obj_get_type(obj, "short_desc") == TYPE_STR);
    int long_ver = (obj_get_type(obj, "long_desc") == TYPE_STR);

    // verify each attribute
    int connections_ver = (connection_type_check(obj) == SUCCESS);

    return !(short_ver && long_ver && connections_ver);
}

// The following functions regard item type checking

/* See validate.h */
int item_type_check(obj_t *obj)
{
    // fields to verify
    int short_ver = (obj_get_type(obj, "short_desc") == TYPE_STR);
    int long_ver = (obj_get_type(obj, "long_desc") == TYPE_STR);
    int in = (obj_get_type(obj, "in") == TYPE_STR);

    return !(short_ver && long_ver && in);
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

// the following functions regard class type checking

const int CLASS_ATTRIBUTES_N = 8;
const char* const CLASS_ATTRIBUTES[8] = {
    "prefab", 
    "short_desc", 
    "long_desc", 
    "attributes", 
    "base_stats", 
    "effects", 
    "skill_tree", 
    "starting_skills"
};

/* See validate.h */
int class_type_check(obj_t *obj)
{
    if (!check_attributes(obj, CLASS_ATTRIBUTES, CLASS_ATTRIBUTES_N)) {
        fprintf(stderr, "Class object had invalid attribute.\n");
        return FAILURE;
    }

    /* Missing fields (TYPE_ERROR or TYPE_NONE) are fine, we fill them in later */
    if (!is_type_or_nonexistent(obj, "prefab", TYPE_BOOL)) {
        fprintf(stderr, "Class's prefab field was wrong type.\n");
        return FAILURE;
    }

    if (!is_type_or_nonexistent(obj, "short_desc", TYPE_STR)) {
        fprintf(stderr, "Class's short_desc field was wrong type.\n");
        return FAILURE;
    }

    if (!is_type_or_nonexistent(obj, "long_desc", TYPE_STR)) {
        fprintf(stderr, "Class's long_desc field was wrong type.\n");
        return FAILURE;
    }

    if (!is_type_or_nonexistent(obj, "attributes", TYPE_OBJ)) {
        fprintf(stderr, "Class's attributes field was wrong type.\n");
        return FAILURE;
    }

    if (!is_type_or_nonexistent(obj, "base_stats", TYPE_OBJ)) {
        fprintf(stderr, "Class's base_stats field was wrong type.\n");
        return FAILURE;
    }

    if (!is_type_or_nonexistent(obj, "effects", TYPE_OBJ)) {
        fprintf(stderr, "Class's effects field was wrong type.\n");
        return FAILURE;
    }

    if (!is_type_or_nonexistent(obj, "skilltree", TYPE_OBJ)) {
        fprintf(stderr, "Class's skilltree field was wrong type.\n");
        return FAILURE;
    }

    if (!is_type_or_nonexistent(obj, "starting_skills", TYPE_OBJ)) {
        fprintf(stderr, "Class's starting_skills field was wrong type.\n");
        return FAILURE;
    }

    return SUCCESS;
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
        if (strcasecmp(curr->act->c_name, str) == 0)
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
    int action_valid = (action_validate(obj_get_str(obj, "action")) == SUCCESS);

    return !(action_type && action_valid);
}

// The following functions regard NPC type checking

/* See validate.h */
int npc_type_check(obj_t *obj)
{
    // fields to verify
    int short_ver = (obj_get_type(obj, "short_desc") == TYPE_STR);
    int long_ver = (obj_get_type(obj, "long_desc") == TYPE_STR);

    return !(short_ver && long_ver);
}

/* See validate.h */
int inventory_type_check(obj_t *obj)
{
    // fields to verify
    int item_id = (obj_get_type(obj, "item_id") == TYPE_STR);

    return !(item_id);
}

/* See validate.h */
int dialogue_type_check(obj_t *obj)
{   
    // verify that the nodes and edges attributes exist
    obj_t *nodes_obj = obj_get_attr(obj, "nodes", false);
    obj_t *edges_obj = obj_get_attr(obj, "edges", false);

    if (nodes_obj == NULL || edges_obj == NULL) return FAILURE;
    
    obj_t *curr;
    int id = 1, npc_dialogue = 1;
    int quip = 1, from_id = 1, to_id = 1;

    // verify the node fields
    DL_FOREACH(nodes_obj->data.lst, curr)
    {
        id = id && (obj_get_type(curr, "id") == TYPE_STR);
        npc_dialogue = npc_dialogue &&
            (obj_get_type(curr, "npc_dialogue") == TYPE_STR);
    }

    // verify the edge fields
    DL_FOREACH(edges_obj->data.lst, curr)
    {
        quip = quip && (obj_get_type(curr, "quip") == TYPE_STR);
        from_id = from_id && (obj_get_type(curr, "from_id") == TYPE_STR);
        to_id = to_id && (obj_get_type(curr, "to_id") == TYPE_STR);
    }

    return !(id && npc_dialogue && quip && from_id && to_id);
}

int node_action_type_check(obj_t *obj)
{
    // fields to verify
    int action = (obj_get_type(obj, "action") == TYPE_STR);
    int action_id = (obj_get_type(obj, "action_id") == TYPE_STR);

    return !(action && action_id);
}

// The following functions regard condition type checking

int conditions_type_check(obj_t *obj)
{
    int type = (obj_get_type(obj, "type") == TYPE_STR);

    return !type;
}

// The following functions regard quest type checking

const int QUEST_ATTRIBUTES_N = 5;
const char* const QUEST_ATTRIBUTES[5] = {
    "Quest Name",
    "Rewards",
    "Task Tree",
    "Task List",
    "Prerequisites"
};
int quest_type_check(obj_t *obj)
{
    if(!check_attributes(obj, QUEST_ATTRIBUTES, QUEST_ATTRIBUTES_N)) {
        fprintf(stderr, "Quest has invalid attributes!");
        return FAILURE;
    }

    int name = (obj_get_type(obj, "Quest Name") == TYPE_STR);
    return !name;
}


const int TASK_ATTRIBUTES_N = 4;
const char* const TASK_ATTRIBUTES[4] = {
    "Task Name",
    "Mission",
    "Prerequisites",
    "Rewards"
};
int task_type_check(obj_t *obj)
{
    if(!check_attributes(obj, TASK_ATTRIBUTES, TASK_ATTRIBUTES_N)) {
        fprintf(stderr, "Task has invalid attributes!");
        return FAILURE;
    }

    int name = (obj_get_type(obj, "Task Name") == TYPE_STR);
    return !name;
}


const int PREREQ_ATTRIBUTES_N = 4;
const char* const PREREQ_ATTRIBUTES[4] = {
    "Health",
    "Level",
    "Tasks",
    "Quests"
};
int prereq_type_check(obj_t *obj)
{
    if(!check_attributes(obj, PREREQ_ATTRIBUTES, PREREQ_ATTRIBUTES_N)) {
        fprintf(stderr, "Prereq has invalid attributes!");
        return FAILURE;
    }
    return SUCCESS;
}


const int REWARDS_ATTRIBUTES_N = 2;
const char* const REWARDS_ATTRIBUTES[2] = {
    "XP",
    "Item"
};
int rewards_type_check(obj_t *obj)
{
    if(!check_attributes(obj, REWARDS_ATTRIBUTES, REWARDS_ATTRIBUTES_N)) {
        fprintf(stderr, "Reward has invalid attributes!");
        return FAILURE;
    }
    return SUCCESS;
}


int mission_type_check(obj_t *obj)
{
    int target_name = (obj_get_type(obj, "Target Name") == TYPE_STR);
    int type = (obj_get_type(obj, "Type") == TYPE_STR);

    return !(target_name && type);
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
    printf("id: %s\n", obj->id);
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
    printf("ROOM: %s\n", obj->id);
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
    printf("ITEM: %s\n", obj->id);
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
