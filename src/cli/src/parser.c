#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli/parser.h"
#include "common/utlist.h"
#include "cli/util.h"

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

// removes filler words from input, right now "to", "the", and "into"
char **remove_fillers(char **parsed_input)
{
    //first, count the NULL chars
    // this is important, as you want
    // to avoid using strcmp with NULL as an input
    int null_count = 0;
    for (size_t i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        if (parsed_input[i] == NULL)
        {
            null_count++;
        }
    }
    
    //loooping through the four words in the parsed input
    for (int i = 0; i < TOKEN_LIST_SIZE - null_count; i++)
    {
        if(parsed_input[i] == NULL){ break; }
        // determine if this word is a filler
        if(strcmp("to", parsed_input[i]) == 0 || strcmp("the", parsed_input[i]) == 0
            || strcmp("into", parsed_input[i]) == 0){
            //if so, remove it and push every word to the left in the 
            // array
            for (int j = i; j < TOKEN_LIST_SIZE - i; j++)
            {
                parsed_input[j] = parsed_input[j + 1];
            }

            //if you are removing a filler word, everything past it is shifted
            //to the left one.  Thus, the last token must be set to NULL to 
            //maintain either being NULL or a valid token
            //in the output

            //additionally, you must move i back one, as
            // every token is moved to the left and 
            // therefore the same index could contain another
            // filler word
            parsed_input[TOKEN_LIST_SIZE - 1] = NULL;
            i = i - 1;
        }
    }
    return parsed_input;

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
    char **by_quotes;
    by_quotes = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);


    //Initializes all words to NULL
    for (int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = NULL;
        by_quotes[i] = NULL;
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

    // before returning the tokens, we must run through them
    // and remove all "fillers", such as prepositions
    // like "the" and "to"
    remove_fillers(words);

    return words;
    char *token_quotes = strtok(input, "\"");

    //Populates by_quotes array with tokens separated by " character
    for (int i = 0; i < TOKEN_LIST_SIZE; i++)
    {

        by_quotes[i] = token_quotes;
        token_quotes = strtok(NULL, "\"");

    }

    //If the first character of the input is not "
    if (input[0] != '\"')
    {
        char *token = strtok(input, " ");

        //Populates words array with tokens separated by space (" ") character
        for (int i = 0; i < 4; i++)
        {

            words[i] = token;
            token = strtok(NULL, " ");
 
        }

        // iterates through words array until it finds a null, inserts the by_quotes value
        // corresponding to words in between the two quotes ("example"). This assumes
        // only one pair of double quotes is used
        for (int j = 0; j < TOKEN_LIST_SIZE; j++) 
        {
            if (!(words[j])) 
            {
                words[j] = by_quotes[1];
                break;
            }
        }

        //If there are more than 4 words, parser returns NULL and does not attempt
        //to pass the first four words as tokens

        if (token != NULL)
        {
            return NULL;
        }

        return words;

    //If the first character of the input is "
    }
    else
    {
        
        char* token;
        int len = strlen(input) - 1;
        // tokenises using spaces the contents between the two airquotes
        // which have already been tokenized into by_quotes array.
        words[0] = by_quotes[0];


        if (input[len] != '\"') 
        {
            
            token = strtok(by_quotes[1], " ");

            //Populates words array with tokens separated by space (" ") character
            for (int i = 1; i < TOKEN_LIST_SIZE; i++)
            {

                words[i] = token;
                token = strtok(NULL, " ");

            }
        
        }
        else
        {
            words[1] = NULL;
        }

        //If there are more than 4 words, parser returns NULL and does not attempt
        //to pass the first four words as tokens

        if (token != NULL)
        {
            return NULL;
        }

        return words;
    }

}