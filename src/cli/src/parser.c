#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli/parser.h"

char *strtokstr_r(char *s, char *delim, char **save_ptr){
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

        while (strstr(s,delim) == s)
        {
            s+=strlen(delim);
            if (*s == '\0')
            {
                *save_ptr = s;
                return NULL;
            }
        }

        end = strstr (s, delim);
        if (end == NULL)
        {
            *save_ptr = s + strlen(s);
            return s;
        }

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
    big_words = (char**)malloc(sizeof(char*) * TOKEN_LIST_SIZE);
    char **words;
    words = (char**)malloc(sizeof(char*) * TOKEN_LIST_SIZE);

    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        big_words[i] = NULL;
    }
    for(int l = 0; l < TOKEN_LIST_SIZE; l++)
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
        return NULL;
    }

    return words;
}
