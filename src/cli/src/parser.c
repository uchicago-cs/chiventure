#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli/parser.h"
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

    char **save_ptr = &input;
    char **big_words;
    big_words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);
    char **words;
    words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);
    char **and_words;
    and_words = (char**)malloc(sizeof(char*)*4);
    
    for(int i = 0; i < 4; i++)
    {
        big_words[i] = NULL;
    }
    for(int l = 0; l < 4; l++)
    {
        words[l] = NULL;
    }
    for(int l = 0; l < 4; l++)
    {
        and_words[l] = NULL;
    }
   
   
   
    char *token = strtokstr_r(input, "and", save_ptr);
    int j = 0;
    while(token != NULL && j < 2){
        big_words[j] = token;
        token = strtokstr_r(input, "and", save_ptr);
        j++;
    }
    if (big_words[1] != NULL)
    {
        for(int i = 0; i < 2; i++)
        {
            char *token = strtok(big_words[i], " ");
            for(int k = 0; k < 4; k++)
            {
                if (i == 0)
                {
                  words[k] = token;
                  token = strtok(NULL, " ");
                }
                else 
                {
                    and_words[k] = token;
                    token = strtok(NULL, " ");
                }
            }
    }
    }
    else 
    {
       char *token = strtok(big_words[0], " ");
            for(int k = 0; k < 4; k++)
            {
                  words[k] = token;
                  token = strtok(NULL, " ");
    }
    }

    //If there are more than 4 words, parser returns NULL and does not attempt
    //to pass the first four words as tokens
    if(token != NULL)
    {
        return NULL;
    }
    return words;
}
