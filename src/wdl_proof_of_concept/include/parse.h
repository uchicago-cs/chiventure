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

bool verify_item(obj_t *obj, char *str);

bool verify_room(obj_t *obj, char *str);

bool verify_game(obj_t *obj, char *str1, char *str2);