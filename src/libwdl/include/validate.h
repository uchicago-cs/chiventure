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

/*
 * These functions print out the short description and long description of an
 * object given the "document" object and string of the specified object e.g.
 * "OBJECTS.0" for the first object specified within the YAML file
 * Parameters:
 * - obj: The document object
 * - str: The string of the specified object
 * Side-effects:
 * - Prints out information of the inputted object string, specifically the
 *   short and long descriptions of rooms and items and the introduction and
 *   start of the game
 */
void print_item(obj_t *obj, char *str);

void print_room(obj_t *obj, char *str);

void print_game(obj_t *obj, char *str1, char *str2);

// ORIGINAL FUNCTIONS
/*
 * These functions verify that the object fields are of the right type.
 *
 * Parameters:
 *  - obj: The document object
 *  - str: The id of the specific object in dot
notation
 *  - for verify game, str1 is starting room and str2 is intro
 *
 * Returns:
 *  - true if object is valid
 *  - false if object is invalid
 */

// bool verify_item(obj_t *obj, char *str);

// bool verify_room(obj_t *obj, char *str);

// bool verify_game(obj_t *obj, char *str1, char *str2);

// NEW VERIFY FUNCTIONS
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
void list_print(attr_list_t *ls, bool(*print)(obj_t*));


/*
 * verify
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
 * We will want to then validate each of the attributes
 */
 bool verify_item(obj_t *obj);

 bool verify_room(obj_t *obj);

 bool verify_game(obj_t *obj);

 bool verify_player(obj_t *obj);

#endif /* INCLUDE_VALIDATE_H */