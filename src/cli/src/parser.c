#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/parser.h"

/* See parser.h */
char **parse(char *input)
{
    char **words;
    words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);

    //Initializes all words to NULL
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = NULL;
    }

    char *token = strtok(input, " ");

    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = token;
        token = strtok(NULL, " ");
    }

    if(token != NULL)
    {
        printf("ERROR: too many words!\n");
        return NULL;
    }

    char *command = words[0];
    int i = 0;
    char ch;

    while(command[i])
    {
        ch = toupper(command[i]);
        command[i] = ch;
        i++;
    }

    return words;
}

//A test function
// int main() {
//     char str[] = "give talisman to wizard";
//     char **words = parse(str);

//     if(words == NULL) {
//         return 1;
//     }

//      for(int i = 0; i < TOKEN_LIST_SIZE; i++) {
//         printf("%s\n", words[i]);
//     }

//      return 0;
// }
