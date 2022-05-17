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
char **remove_fillers(char **parsed_input){
    //loooping through the four words in the parsed input
    for (size_t i = 0; i < 3; i++)
    {
        // determine if this word is a filler
        if(strcmp("to",parsed_input[i]) == 0 || strcmp("to ",parsed_input[i]) == 0 || strcmp(" to",parsed_input[i]) == 0){
            //if so, remove it and push every word to the left in the 
            // array
            for (size_t j = 1; j < 3; j++)
            {
                parsed_input[j] = parsed_input[j + 1];
            }
            parsed_input[3] = NULL;
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
    char **quote_word;
    quote_word = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);


    //Initializes all words to NULL
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = NULL;
        quote_word[i] = NULL;
    }

    char *token_quotes = strtok(input, "\"");

    //Populates quote_word array with tokens separated by " character
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {

        quote_word[i] = token_quotes;
        token_quotes = strtok(NULL, "\"");
    }

    //If the first character of the input is not "
    if (input[0] != '\"')
    {
        char *token = strtok(input, " ");

        //Populates words array with tokens separated by space (" ") character
        for(int i = 0; i < TOKEN_LIST_SIZE; i++)
        {

            words[i] = token;
            token = strtok(NULL, " ");
 
        }

        // iterates through words array until it finds a null, inserts the quote_word value
        // corresponding to words in between the two quotes ("example"). This assumes
        // only one pair of double quotes is used
        for (int j = 0; j < TOKEN_LIST_SIZE; j++) 
        {
            if (!(words[j])) 
            {
                words[j] = quote_word[1];
                break;
            }
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
        //remove_fillers(words);

        //return words;

    //If the first character of the input is "
    }else{
        
        char* token;
        // tokenises using spaces the contents between the two airquotes
        // which have already been tokenized into quote_word array.
        words[0] = quote_word[0];


        if (quote_word[1]) 
        {
            
            token = strtok(quote_word[1], " ");

            //Populates words array with tokens separated by space (" ") character
            for(int i = 1; i < TOKEN_LIST_SIZE; i++)
            {

                words[i] = token;
                token = strtok(NULL, " ");

            }
        
        }

        //If there are more than 4 words, parser returns NULL and does not attempt
        //to pass the first four words as tokens

        if(token != NULL)
        {
        return NULL;
        }


        //return words;
    }

    return words;

}