#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli/parser.h"

char *strtokstr_r(char *s, char *delim, char **save_ptr)
{
    char *end;
    if (s == NULL)
    {
        s = *save_ptr;
    }
    else if (s == NULL || *s == '\0')
    {
        *save_ptr = s;
        return NULL;
    }
    while (strstr(s,delim)==s)
    {
        s+=strlen(delim);
        if (*s == '\0')
        {
            *save_ptr = s;
            return NULL;
            }
    }
    // Find the end of the token.
    end = strstr (s, delim);
    if (end == NULL)
    {
        *save_ptr = s + strlen(s);
        return s;
    }

        // Terminate the token and make *SAVE_PTR point past it.
        memset(end, 0, strlen(delim));
        *save_ptr = end + strlen(delim);
        return s;
}

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

    char **save_ptr = &input;
    char **big_words;
    big_words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);
    for(int i = 0; i < 4; i++)
    {
        big_words[i] = NULL;
    }

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

    //If there are more than 4 words, parser returns NULL and does not attempt
    //to pass the first four words as tokens
    if(token != NULL)
    {
        return NULL;
    }

    return words;
}
