#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli/parser.h"

/* See parser.h */
char **parse(char *input)
{
    if(strcmp(input, "") == 0)
    {
        return NULL;
    }

    //Changes the input to be all caps, for compatibility with commands/objects/directions
    int i = 0;
    char ch;

    while(input[i])
    {
        ch = toupper(input[i]);
        input[i] = ch;
        i++;
    }

    char **words;
    words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);

    //Initializes all words to NULL
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = NULL;
    }
    char* and = strstr(input, "and");
    if (*and != NULL){
        char *token = strtok(input, *and);
    }
    else{
    char *token = strtok(input, " ");
    }
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = token;
        and = strstr(input, "and");
       
            token = strtok(NULL, *and" ");
        
        
    }

    //If there are more than 4 words, parser returns NULL and does not attempt
    //to pass the first four words as tokens
    if(token != NULL)
    {
        return NULL;
    }

    return words;
}
