/*
 * Header file for wdl/yaml parsing functions and related utilities
 */

#ifndef INCLUDE_PARSE_H
#define INCLUDE_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

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



#endif /* INCLUDE_PARSE_H */