#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>



/* ========================================================== */
/* ======== Functions for Normalizing the Game State ======== */
/* ========================================================== */


/*
 * Function used to make struct IDs and other identifiers
 *      case insensitive
 * Parameters:
 *   -  input: the string being lower-cased
 * 
 */
void case_insensitize(char *input);