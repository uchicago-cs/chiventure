#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli/parser.h"
#include "common/utlist.h"
#include "cli/util.h"

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
/* See parser.h */
char **parse(char *input)
{

    if(strcmp(input, "") == 0)
    {
        return NULL;
    }

    case_insensitize(input);

    char **words;
    words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);
    char **temp;
    temp = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);
    char **temp2;
    temp2 = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);

    //Initializes all words to NULL
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = NULL;
        temp[i] = NULL;
        temp2[i] = NULL;
    }

    char *token2 = strtok(input, "\"");
    int pos = 0;

    //Populates temp array with tokens separated by " character
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {

        temp[i] = token2;
        token2 = strtok(NULL, "\"");

    }

    //If the first character of the input is not "
    if (input[0] != '\"')
    {
        char *token = strtok(input, " ");

        //Populates words array with tokens separated by space (" ") character
        for(int i = 0; i < 4; i++)
        {

            words[i] = token;
            token = strtok(NULL, " ");


        }

        // iterates through words array until it finds a null, inserts the temp value
        // corresponding to words in between the two quotes ("example"). This assumes
        // only one pair of double quotes is used
        for (int j = 0; j < TOKEN_LIST_SIZE; j++) 
        {
            if (!(words[j])) 
            {
                words[j] = temp[1];
                break;
            }
        }

        //If there are more than 4 words, parser returns NULL and does not attempt
        //to pass the first four words as tokens

        if(token != NULL)
        {
        return NULL;
        }

        return words;

    //If the first character of the input is "
    }else{

        // tokenises using spaces the contents between the two airquotes
        // which have already been tokenized into temp array.
        char* token3 = strtok(temp[0], " ");

        //Populates temp2 array with tokens separated by space (" ") character
        for(int i = 0; i < TOKEN_LIST_SIZE; i++)
        {

            temp2[i] = token3;
            token3 = strtok(NULL, " ");

        }

        //If there are more than 4 words, parser returns NULL and does not attempt
        //to pass the first four words as tokens

        if(token3 != NULL)
        {
        return NULL;
        }

        return temp2;
    }

}