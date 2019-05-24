/*
 * Header file for object validation and object printing functions and
 * related utilities
 */

#ifndef INCLUDE_VALIDATE_H
#define INCLUDE_VALIDATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"


/* a doubly linked list of strings used to store approved actions
 * used when type-checking actions
 */
typedef struct action_list
{
    char *action;
    struct action_list *next;
} action_list_t;


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
 *  - true if all objects in the list pass the type checker
 *  - false if else
 *
 * note: behaviour is undefined if object and validation function do not match
 */
bool list_type_check(attr_list_t *ls, bool(*validate)(obj_t*));

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
void list_print(attr_list_t *ls, void(*print)(obj_t*));

/*
 * type_check
 * Verifies whether the given object has the correct return types for all of
 * its attributes
 *
 * Parameters:
 * - obj: object to verify (e.g. ROOMS)
 *
 * Returns:
 * - boolean indicating whether the object has correct attributes
 *
 * Notes:
 * What we plan to do is first extract an object, such as the room object,
 * which would include each of the rooms and their attributes.
 * We will want to then validate each of the attributes by running type_check
 * with list_type_check
 */
bool game_type_check(obj_t *obj);

bool room_type_check(obj_t *obj);

bool item_type_check(obj_t *obj);

bool player_type_check(obj_t *obj);

bool action_type_check(obj_t *obj);

#endif /* INCLUDE_VALIDATE_H */
