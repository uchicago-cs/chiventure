/*
 * Header file for object validation and object printing functions and
 * related utilities
 */

#ifndef INCLUDE_VALIDATE_H
#define INCLUDE_VALIDATE_H

#include "action_management/actionmanagement.h"
#include "wdl_common.h"

/* a doubly linked list of strings used to store approved actions
 * used when type-checking actions
 */
typedef struct action_list
{
    char *action;
    struct action_list *next;
} action_list_t;

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
obj_t *connections_get_list(obj_t *obj);

/* check_connection_attr()
 * a helper function for connection_type_check() that checks the attributes of
 * connections associated with a room object
 *
 * parameters:
 * - obj: a connection object
 *
 * returns:
 * - SUCCESS if connection types match, else return FAILURE
 */
int check_connection_attr(obj_t *obj);

/* print_item
 * prints the attributes associated with the item: id, short_desc, long_desc,
 * in, and state
 *
 * parameters:
 * - item object
 *
 * side effects:
 * - prints out associated attributes of item object
 */
void print_item(obj_t *obj);

/* print_room
 * prints the attributes associated with the room: id, short_desc, long_desc,
 * and connections
 *
 * parameters:
 * - room object
 *
 * side effects:
 * - prints out associated attributes of room object
 */
void print_room(obj_t *obj);

/* print_game
 * prints the attributes associated with the game: start, intro
 *
 * parameters:
 * - game object
 *
 * side effects:
 * - prints out associated attributes of game object
 */
void print_game(obj_t *obj);

/* print_document
 * essentially prints out the attributes of the entire game in this order:
 * game, room, item
 *
 * parameters:
 * - document object
 *
 * side effects:
 * - prints out associated attributes of document object
 */
 void print_document(obj_t *obj);

/* list_type_check()
 * a function to automate type checking,
 * used before running extract_id() from parse.h
 *
 * parameters:
 *  - ls: a list of objects
 *  - a function pointer to a type checking function
 *
 * returns:
 *  - SUCCESS if all objects in the list pass the type checker
 *  - FAILURE if else
 *
 * note: behaviour is undefined if object and validation function do not match
 */
int list_type_check(obj_t *ls, int(*validate)(obj_t*));

/* list_print()
 * a function to automate printing objects;
 * used primarily for testing
 *
 * parameters:
 *  - ls: a list of objects
 *  - a function pointer to a object printing function
 *
 * returns:
 *  - nothing
 *
 * side effects:
 *  - printing the contents of the given objects according to the given function
 *
 * note: behaviour is undefined if object and validation function do not match
 */
void list_print(obj_t *ls, void(*print)(obj_t*));

/*
 * type_check
 * Verifies whether the given object has the correct return types for all of
 * its attributes
 *
 * Parameters:
 * - obj: object to verify (e.g. ROOMS)
 *
 * Returns:
 * - SUCCESS or FAILURE based on whether the object has correct attributes
 *
 * Notes:
 * What we plan to do is first extract an object, such as the room object,
 * which would include each of the rooms and their attributes.
 * We will want to then validate each of the attributes by running type_check
 * with list_type_check
 */
int game_type_check(obj_t *obj);

int class_type_check(obj_t *obj);

int room_type_check(obj_t *obj);

int item_type_check(obj_t *obj);

int player_type_check(obj_t *obj);

int action_type_check(obj_t *obj);

int npc_type_check(obj_t *obj);

int inventory_type_check(obj_t *obj);

int dialogue_type_check(obj_t *obj);

int node_action_type_check(obj_t *obj);

int conditions_type_check(obj_t *obj);

int quest_type_check(obj_t *obj);

int task_type_check(obj_t *obj);

int prereq_type_check(obj_t *obj);

int rewards_type_check(obj_t *obj);

int mission_type_check(obj_t *obj);

#endif /* INCLUDE_VALIDATE_H */
