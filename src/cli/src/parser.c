#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "cli/parser.h"
#include "common/utlist.h"
/*
 * INPUT: a string from the command line, the delimiter string used to tokenize, 
 * and pointer to the string from the command line
 * 
 * returns: the first tokenized string
 * 
 */
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
tokenized_cmds *parse(char *input)
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

    tokenized_cmds *head = NULL;
    char **save_ptr = &input;
   
    char *token = strtokstr_r(input, "and", save_ptr);
    while(token != NULL)
    {
        tokenized_cmds *new_thing = malloc(sizeof(tokenized_cmds));
        new_thing->cmds = token;
        new_thing->next = NULL;
        LL_APPEND(head, new_thing);
        token = strtokstr_r(input, "and", save_ptr);
    }
   
    //If there are more than 4 words, parser returns NULL and does not attempt
    //to pass the first four words as tokens
    if(token != NULL)
    {
        return NULL;
    }
    return head;
}

char **parse_addition(char *input)
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
