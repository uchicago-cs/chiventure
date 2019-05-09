#ifndef _PARSER_H
#define _PARSER_H

/*
 * Parses a string into a list of words, breaking on spaces
 *
 * Parameters:
 * -input: string to be parsed
 *
 * Returns:
 * -A list of individual words from the input string. This list is a fixed
 * size, the words possible in a command. If the input string is has less
 * words than this fixed size, the rest of the list will be null.
 *
 */
char **parse(char *input);

#endif /* _PARSER_H */
