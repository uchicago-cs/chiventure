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
        words[l] = NULL;
    }
   
   
    char *token = strtokstr_r(input, "and", save_ptr);
    int j = 0;
    for (int k = 0; k < 4; k++){
        big_words[k] = token;
        if (big_words[k] != NULL)
        {
            char *token_r = strtok(big_words[k], " ");
            while (k < 1)
            {
                char* action = (char*)malloc(sizeof(char*));
                action = token_r;
            }

            while(token_r != NULL && j < 4)
            {
                words[j] = token_r;
                token_r = strtok(NULL, " ");
                j++;
            }   
        }
        token = strtokstr_r(input, "and", save_ptr);
        
    }
    if(token != NULL)
    {
        return NULL;
    }

    return words;
}
