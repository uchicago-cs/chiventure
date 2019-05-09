#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

/*
 * Header for parsing functions and other utilities for the proof of concept
 */

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
/*
 * extract_object
 * extracts the specific object given the document object and associated
 * string of the extracted object
 *
 * Parameters:
 * - obj: The document object
 * - str: The id of the specific object within document object
 *
 * Returns:
 * - pointer to object associated with inputted string
 */
 object_t *extract_object(obj_t *obj, char *str);

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
