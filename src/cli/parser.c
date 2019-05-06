#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

/* 
 * This size is the number of words possible in a single command.
 * For now this size is 4, which includes an action, an object,
 * a preposition, and an indirect object
 */
#define TOKEN_LIST_SIZE 4

//See parser.h
char **parse(char *input) {
    char **words;
    words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);

    //Initializes all words to NULL
    for(int i = 0; i < TOKEN_LIST_SIZE; i++) {
        words[i] = NULL;
    }

    char *token = strtok(input, " ");

    for(int i = 0; i < TOKEN_LIST_SIZE; i++) {
        words[i] = token;
        token = strtok(NULL, " ");
    }

    return words;
}
// A test function
/*int main() {
    char str[] = "GIVE talisman";
    char **words = parse(str);

    for(int i = 0; i < TOKEN_LIST_SIZE; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}
*/
