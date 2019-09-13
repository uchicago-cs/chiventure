#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H

#include "stack.h"

//Personalized token type to keep track of what last happened
typedef enum token_type{KEY, VALUE, BLOCK_START} tok_type;


/*
 * Creates a sequence (list) stack frame object
 *
 * Parameters:
 *  - stack: stack to push to
 *  - key: string to add to attr_string of the current stack top
 *
 * Returns:
 *  - existing stack with the new sequence/list-style element on top
 */
stack_t *begin_sequence(stack_t *stack, char *key);

/*
 * Creates a non-sequence stack frame object
 *
 * Parameters:
 *  - stack: stack to push to
 *  - key: string to add to attr_string of the current stack top
 *
 * Returns:
 *  - existing stack with the new element  on top
 */
stack_t *begin_obj(stack_t *stack, char *key);


/*
 * Adds a piece to an attribute string prefix
 * 
 * Parameters:
 *  - orig_prefix: existing prefix
 *  - to_add: extension to tack on
 * 
 * Returns:
 *  - New prefix string of the form orig_prefix.to_add, assuming both exist
 *  - Orig_prefix if to_add is null
 *  - To_add if orig_prefix is also null
 *  - Empty string of size MAXLEN_SEARCH if both are null
 */
char *extend_prefix(char *orig_prefix, char *to_add);

/*
 * Parses a "game" given as a YAML file into object structures
 *
 * Parameters:
 *  - filename: name of file to parse (MUST HAVE .yaml EXTENSION)
 *  - docobj: pointer to an empty, malloced object to be filled in with results from parsing
 *
 * Returns:
 * - 0 on success
 */
int parse_game(char *filename, obj_t *docobj);

#endif /* INCLUDE_PARSER_H */