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
// DO NOT #include "parse.h" AS IT WILL CREATE CIRCULAR DEPENDENCIES


/* a doubly linked list of strings used to store the ids of objects;
 * used to check that room passages lead to valid rooms and the such
 */
typedef struct id_list
{
    char *id;
    struct id_list *prev;
    struct id_list *next;
} id_list_t;


/* id_list_add()
 * a function that adds an item to the id_list in the `next` position
 *
 * parameters:
 *  - id: a string indicating the id to add to the list
 *  - ls: the list to which to add the id; if null, the function will start a new list
 *
 * returns
 *  - a list of ids
 *
 * side effects:
 *  - prints to stderr if an error occurs
 */
id_list_t *id_list_add(char *id, id_list_t *ls);


/* id_list_dup_check()
 * a function that checks a list of items for duplicate ids
 *
 * parameters:
 *  - ls: the list which to check for duplicates
 *
 * returns:
 *  - true if duplicates are detected
 *  - false if no duplicates are detected
// note to self: use a helper function to count for instances
 */
bool id_list_dup_check(id_list_t *ls);


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


/* list_valid_id_ref()
 * a function to automate the checking of valid id references in objects
 * note that the behaviour is undefined if the object and the validation functions
 * do not match
 *
 * parameters:
 *  - ls_obj: a list of objects
 *  - ls_id: a list of ids extracted from those objects
 *
 * returns:
 *  - true is all objects pass the given validation test
 *  - false if else
 */
bool list_valid_id_ref(attr_list_t *ls_obj, id_list_t *ls_id, 
                       bool(*validate)(obj_t *obj, id_list_t *ls));


/* list_print()
 * a function to automate printing objects;
 * used primarily for testing
 *
 * parameters:
 *  - ls: a list of objects
 *  - a function pointer to a type checking function
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

 /* raise_error()
  * an utility used to print errors to stderrs
  *
  * parameters:
  * - str: the error message to print out
  *
  * side effects:
  * - prints a string to sdterr
  */
void raise_error(char *str);

#endif /* INCLUDE_VALIDATE_H */
