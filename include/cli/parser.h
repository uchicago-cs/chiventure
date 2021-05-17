#ifndef _CLI_INCLUDE_PARSER_H
#define _CLI_INCLUDE_PARSER_H

typedef struct tokenized_cmds {
    char *cmds;
    struct tokenized_cmds *next; /* needed for singly- or doubly-linked lists */
} tokenized_cmds;

/*
 * This size is the number of words possible in a single command.
 * For now this size is 4, which includes an action, an object,
 * a preposition, and an indirect object
 */
#define TOKEN_LIST_SIZE 4

/*
 * Parses a string into a list of words, breaking on spaces
 *
 * Parameters:
 * - input: string to be parsed
 *
 * Returns:
 * - A list of individual words from the input string. This list is a fixed
 *   size, the words possible in a command. If the input string is has less
 *   words than this fixed size, the rest of the list will be null.
 *
 */
char **parse(char *input);


#endif /* _CLI_INCLUDE_PARSER_H */
