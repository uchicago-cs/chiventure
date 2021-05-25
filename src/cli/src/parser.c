#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli/parser.h"
#include "common/utlist.h"

/*
 * - input: 
 *   s: a string from the command line, 
 *   delim: the delimiter string used to tokenize, 
 *   save_ptr: pointer to s
 * 
 * - returns: 
 *   the first tokenized string
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
    while (strstr(s,delim) == s)
    {
        s += strlen(delim);
        if (*s == '\0')
        {
            *save_ptr = s;
            return NULL;
        }
    }
    // Find the end of the token.
    end = strstr(s, delim);
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
tokenized_cmds *parse_r(char *input)
{
    if (strcmp(input, "") == 0)
    {
        return NULL;
    }

    //Changes the input to be all caps, for compatibility with commands/objects/directions
    int i = 0;
    char ch;

    while (input[i])
    {
        ch = toupper(input[i]);
        input[i] = ch;
        i++;
    }

    tokenized_cmds *head = NULL;
    char **save_ptr = &input;
    
    //puts tokenized segments of the inputted string in 
    //the command line with a delimiter "AND" into a 
    //utlist until the end of the string
    char *token = strtokstr_r(input, "AND", save_ptr);
    while (token != NULL)
    {
        tokenized_cmds *added_cmd = malloc(sizeof(tokenized_cmds));
        added_cmd->cmds = token;
        added_cmd->next = NULL;
        LL_APPEND(head, added_cmd);
        token = strtokstr_r(input, "AND", save_ptr);
    }
   
    //If there are more than 4 words, parser returns NULL and does not attempt
    //to pass the first four words as tokens
    if (token != NULL)
    {
        return NULL;
    }
    return head;
}

/* the parser function in this branch attempts to make the token list size flexible 
 * by putting the cmds tokenized by strtok(which delimites by " ") in a utlist 
 * similar to the parse_r function. Instead of returning an array of limited size as the 
 * version in the dev branch does, the function return a tokenized_cmds struct
 */
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
    //creates an additional node on the list until strtok yields NULL when 
    //it has tokenized the entire string
    tokenized_cmds *sub_head = NULL;
    char *sub_token = strtok(token, " ");
    while(sub_token != NULL) 
    {
        tokenized_cmds *sub_new_thing = malloc(sizeof(tokenized_cmds));
        sub_new_thing->cmds = sub_token;
        sub_new_thing->next = NULL;
        LL_APPEND(sub_head, sub_new_thing);
        sub_token = strtok(NULL, " ");

    }  
    
}
