#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"


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
